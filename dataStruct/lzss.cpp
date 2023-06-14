#include <string.h>
#include <stdio.h>

#define BYTE unsigned char
#define WORD unsigned short
#define DWORD unsigned int

#define TRUE 1
#define FALSE 0

BYTE bThreshold;  //ѹ����ֵ�����ȴ��ڵ���2��ƥ�䴮���б�Ҫѹ��

BYTE bPreBufSizeBits;  //ǰ�򻺳���ռ�õı���λ
BYTE bWindowBufSizeBits;  //��������ռ�õı���λ

WORD wPreBufSize;  //ͨ��ռ�õı���λ���㻺������С
WORD wWindowBufSize;  //ͨ��ռ�õı���λ���㻬�����ڴ�С

BYTE bPreBuf[1024];  //ǰ�򻺳���
BYTE bWindowBuf[8192];  //��������
BYTE bMatchString[1024];  //ƥ�䴮
WORD wMatchIndex;  //��������ƥ�䴮��ʼ�±�

BYTE FindSameString(BYTE* pbStrA, WORD wLenA, BYTE* pbStrB, WORD wLenB, WORD* pwMatchIndex);  //����ƥ�䴮
DWORD LZSS_encode(char* pbReadFileName, char* pbWriteFileName);  //�ļ�ѹ��
DWORD LZSS_decode(char* pbReadFileName, char* pbWriteFileName);  //�ļ���ѹ

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

	//ǰ�򻺳���û���ݿɲ����˼�Ϊѹ������
	while (1)
	{
		wPreBufCnt += fread(&bPreBuf[wPreBufCnt], 1, wPreBufSize - wPreBufCnt, pfRead);
		if (wPreBufCnt <= 0)
		{
			break;
		}
		wMatchStringCnt = 0;  //�տ�ʼû��ƥ�䵽����
		wMatchIndex = 0xFFFF;  //��ʼ��һ�����ֵ����ʾûƥ�䵽

		for (i = bThreshold; i <= wPreBufCnt; i++)  //�ڻ���������Ѱ�����ƥ�䴮
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

		//���û�ҵ�ƥ�䴮����ƥ�䳤��Ϊ1��ֱ�����ԭʼ����
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

		bItemNum += 1;  //������һ����Ŀ+1

		if (bItemNum >= 8)  //��Ŀ���ﵽ8�ˣ�˵��������һ��ѹ��������һ������д���ļ���ͬʱ��ջ���
		{
			fwrite(bRestoreBuf, 1, bRestoreBufCnt, pfWrite);
			bItemNum = 0;
			memset(bRestoreBuf, 0, sizeof(bRestoreBuf));
			bRestoreBufCnt = 1;
		}

		//���ո�ƥ����������Ƴ�ǰ�򻺳���
		for (i = 0; i < (wPreBufCnt - wMatchStringCnt); i++)
		{
			bPreBuf[i] = bPreBuf[i + wMatchStringCnt];
		}
		wPreBufCnt -= wMatchStringCnt;

		//����������ڽ�Ҫ���������ǰ��ǰ��Ĳ��������Ƴ�����
		if ((wWindowBufCnt + wMatchStringCnt) > wWindowBufSize)
		{
			j = ((wWindowBufCnt + wMatchStringCnt) - wWindowBufSize);
			for (i = 0; i < (wWindowBufSize - j); i++)
			{
				bWindowBuf[i] = bWindowBuf[i + j];
			}
			wWindowBufCnt = wWindowBufSize - wMatchStringCnt;
		}

		//���ո�ƥ��������ݼ��뻬������
		memcpy((BYTE*)&bWindowBuf[wWindowBufCnt], bMatchString, wMatchStringCnt);
		wWindowBufCnt += wMatchStringCnt;
	}

	//�ļ������ܲ���һ����������ֱ��д���ļ���
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

	while (0 != fread(&bFlag, 1, 1, pfRead))  //�ȶ�һ������ֽ���ȷ����������ô��ѹ����
	{
		for (bItemNum = 0; bItemNum < 8; bItemNum++)  //8����ĿΪһ����н�ѹ
		{
			//�ӱ���ֽڵ����λ��ʼ������0����ԭʼ���ݣ�1����(�±꣬ƥ����)����
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
				//ȡ����λ�Ļ�������ƥ�䴮�±�
				wStart = ((WORD)bPreBuf[0] | ((WORD)bPreBuf[1] << 8)) / ((WORD)1 << bPreBufSizeBits);
				//ȡ����λ��ƥ�䳤��
				wMatchStringCnt = ((WORD)bPreBuf[0] | ((WORD)bPreBuf[1] << 8)) % ((WORD)1 << bPreBufSizeBits) + bThreshold;
				//����ѹ��������д���ļ�
				fwrite(&bWindowBuf[wStart], 1, wMatchStringCnt, pfWrite);
				memcpy(bMatchString, &bWindowBuf[wStart], wMatchStringCnt);
			}

			//����������ڽ�Ҫ���������ǰ��ǰ��Ĳ��������Ƴ�����
			if ((wWindowBufCnt + wMatchStringCnt) > wWindowBufSize)
			{
				j = (wWindowBufCnt + wMatchStringCnt) - wWindowBufSize;
				for (i = 0; i < wWindowBufCnt - j; i++)
				{
					bWindowBuf[i] = bWindowBuf[i + j];
				}
				wWindowBufCnt -= j;
			}

			//����ѹ��������ͬ��д�뵽��������
			memcpy(&bWindowBuf[wWindowBufCnt], bMatchString, wMatchStringCnt);
			wWindowBufCnt += wMatchStringCnt;
		}
	}

LZSS_decode_out_:

	fclose(pfRead);
	fclose(pfWrite);
	return 0;
}
