#include <string.h>
#include <stdio.h>

#define BYTE unsigned char
#define WORD unsigned short
#define DWORD unsigned int

#define TRUE 1
#define FALSE 0

BYTE bThreshold;  //压缩阈值、长度大于等于2的匹配串才有必要压缩

BYTE bPreBufSizeBits;  //前向缓冲区占用的比特位
BYTE bWindowBufSizeBits;  //滑动窗口占用的比特位

WORD wPreBufSize;  //通过占用的比特位计算缓冲区大小
WORD wWindowBufSize;  //通过占用的比特位计算滑动窗口大小

BYTE bPreBuf[1024];  //前向缓冲区
BYTE bWindowBuf[8192];  //滑动窗口
BYTE bMatchString[1024];  //匹配串
WORD wMatchIndex;  //滑动窗口匹配串起始下标

BYTE FindSameString(BYTE* pbStrA, WORD wLenA, BYTE* pbStrB, WORD wLenB, WORD* pwMatchIndex);  //查找匹配串
DWORD LZSS_encode(char* pbReadFileName, char* pbWriteFileName);  //文件压缩
DWORD LZSS_decode(char* pbReadFileName, char* pbWriteFileName);  //文件解压

int lzss_test()
{
	bThreshold = 2;
	bPreBufSizeBits = 6;
	bWindowBufSizeBits = 16 - bPreBufSizeBits;
	wPreBufSize = ((WORD)1 << bPreBufSizeBits) - 1 + bThreshold;
	wWindowBufSize = ((WORD)1 << bWindowBufSizeBits) - 1 + bThreshold;

	LZSS_encode("test.txt", "encode");
	LZSS_decode("encode", "decode");
	return 0;
}

BYTE FindSameString(BYTE* pbStrA, WORD wLenA, BYTE* pbStrB, WORD wLenB, WORD* pwMatchIndex)
{
	WORD i, j;

	for (i = 0; i < wLenA; i++)
	{
		if ((wLenA - i) < wLenB)
		{
			return FALSE;
		}

		if (pbStrA[i] == pbStrB[0])
		{
			for (j = 1; j < wLenB; j++)
			{
				if (pbStrA[i + j] != pbStrB[j])
				{
					break;
				}
			}

			if (j == wLenB)
			{
				*pwMatchIndex = i;
				return TRUE;
			}
		}
	}
	return FALSE;
}

DWORD LZSS_encode(char* pbReadFileName, char* pbWriteFileName)
{
	WORD i, j;
	WORD wPreBufCnt = 0;
	WORD wWindowBufCnt = 0;
	WORD wMatchStringCnt = 0;
	BYTE bRestoreBuf[17] = { 0 };
	BYTE bRestoreBufCnt = 1;
	BYTE bItemNum = 0;
	FILE* pfRead = fopen(pbReadFileName, "rb");
	FILE* pfWrite = fopen(pbWriteFileName, "wb");

	//前向缓冲区没数据可操作了即为压缩结束
	while (1)
	{
		wPreBufCnt += fread(&bPreBuf[wPreBufCnt], 1, wPreBufSize - wPreBufCnt, pfRead);
		if (wPreBufCnt <= 0)
		{
			break;
		}
		wMatchStringCnt = 0;  //刚开始没有匹配到数据
		wMatchIndex = 0xFFFF;  //初始化一个最大值，表示没匹配到

		for (i = bThreshold; i <= wPreBufCnt; i++)  //在滑动窗口中寻找最长的匹配串
		{
			if (TRUE == FindSameString(bWindowBuf, wWindowBufCnt, bPreBuf, i, &wMatchIndex))
			{
				memcpy(bMatchString, &bWindowBuf[wMatchIndex], i);
				wMatchStringCnt = i;
			}
			else
			{
				break;
			}
		}

		//如果没找到匹配串或者匹配长度为1，直接输出原始数据
		if ((0xFFFF == wMatchIndex))
		{
			wMatchStringCnt = 1;
			bMatchString[0] = bPreBuf[0];
			bRestoreBuf[bRestoreBufCnt++] = bPreBuf[0];
		}
		else
		{
			j = (wMatchIndex << bPreBufSizeBits) + wMatchStringCnt - bThreshold;
			bRestoreBuf[bRestoreBufCnt++] = (BYTE)j;
			bRestoreBuf[bRestoreBufCnt++] = (BYTE)(j >> 8);
			bRestoreBuf[0] |= (BYTE)1 << (7 - bItemNum);
		}

		bItemNum += 1;  //操作完一个项目+1

		if (bItemNum >= 8)  //项目数达到8了，说明做完了一组压缩，将这一组数据写入文件，同时清空缓存
		{
			fwrite(bRestoreBuf, 1, bRestoreBufCnt, pfWrite);
			bItemNum = 0;
			memset(bRestoreBuf, 0, sizeof(bRestoreBuf));
			bRestoreBufCnt = 1;
		}

		//将刚刚匹配过的数据移出前向缓冲区
		for (i = 0; i < (wPreBufCnt - wMatchStringCnt); i++)
		{
			bPreBuf[i] = bPreBuf[i + wMatchStringCnt];
		}
		wPreBufCnt -= wMatchStringCnt;

		//如果滑动窗口将要溢出，先提前把前面的部分数据移出窗口
		if ((wWindowBufCnt + wMatchStringCnt) > wWindowBufSize)
		{
			j = ((wWindowBufCnt + wMatchStringCnt) - wWindowBufSize);
			for (i = 0; i < (wWindowBufSize - j); i++)
			{
				bWindowBuf[i] = bWindowBuf[i + j];
			}
			wWindowBufCnt = wWindowBufSize - wMatchStringCnt;
		}

		//将刚刚匹配过的数据加入滑动窗口
		memcpy((BYTE*)&bWindowBuf[wWindowBufCnt], bMatchString, wMatchStringCnt);
		wWindowBufCnt += wMatchStringCnt;
	}

	//文件最后可能不满一组数据量，直接写到文件里
	if (0 != bRestoreBufCnt)
	{
		fwrite(bRestoreBuf, 1, bRestoreBufCnt, pfWrite);
	}

	fclose(pfRead);
	fclose(pfWrite);

	return 0;
}

DWORD LZSS_decode(char* pbReadFileName, char* pbWriteFileName)
{
	WORD i, j;
	BYTE bItemNum;
	BYTE bFlag;
	WORD wStart;
	WORD wMatchStringCnt = 0;
	WORD wWindowBufCnt = 0;
	FILE* pfRead = fopen(pbReadFileName, "rb");
	FILE* pfWrite = fopen(pbWriteFileName, "wb");

	while (0 != fread(&bFlag, 1, 1, pfRead))  //先读一个标记字节以确定接下来怎么解压数据
	{
		for (bItemNum = 0; bItemNum < 8; bItemNum++)  //8个项目为一组进行解压
		{
			//从标记字节的最高位开始解析，0代表原始数据，1代表(下标，匹配数)解析
			if (0 == (bFlag & ((BYTE)1 << (7 - bItemNum))))
			{
				if (fread(bPreBuf, 1, 1, pfRead) < 1)
				{
					goto LZSS_decode_out_;
				}
				fwrite(bPreBuf, 1, 1, pfWrite);
				bMatchString[0] = bPreBuf[0];
				wMatchStringCnt = 1;
			}
			else
			{
				if (fread(bPreBuf, 1, 2, pfRead) < 2)
				{
					goto LZSS_decode_out_;
				}
				//取出高位的滑动窗口匹配串下标
				wStart = ((WORD)bPreBuf[0] | ((WORD)bPreBuf[1] << 8)) / ((WORD)1 << bPreBufSizeBits);
				//取出低位的匹配长度
				wMatchStringCnt = ((WORD)bPreBuf[0] | ((WORD)bPreBuf[1] << 8)) % ((WORD)1 << bPreBufSizeBits) + bThreshold;
				//将解压出的数据写入文件
				fwrite(&bWindowBuf[wStart], 1, wMatchStringCnt, pfWrite);
				memcpy(bMatchString, &bWindowBuf[wStart], wMatchStringCnt);
			}

			//如果滑动窗口将要溢出，先提前把前面的部分数据移出窗口
			if ((wWindowBufCnt + wMatchStringCnt) > wWindowBufSize)
			{
				j = (wWindowBufCnt + wMatchStringCnt) - wWindowBufSize;
				for (i = 0; i < wWindowBufCnt - j; i++)
				{
					bWindowBuf[i] = bWindowBuf[i + j];
				}
				wWindowBufCnt -= j;
			}

			//将解压处的数据同步写入到滑动窗口
			memcpy(&bWindowBuf[wWindowBufCnt], bMatchString, wMatchStringCnt);
			wWindowBufCnt += wMatchStringCnt;
		}
	}

LZSS_decode_out_:

	fclose(pfRead);
	fclose(pfWrite);
	return 0;
}
