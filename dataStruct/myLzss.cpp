#include <windows.h>

#include <stdio.h>

#define WINDOW_SIZE			256


#pragma pack(1)

typedef struct
{
	unsigned char offset;
	unsigned char size;
	unsigned char prev;
}LZSS_POSITION;

#pragma pack()



int search(unsigned char* data, int size, unsigned char* tag, int taglen) {
	if (size < taglen || taglen == 0 || size == 0 || data ==0 || tag == 0)
	{
		return -1;
	}

	int total = size - taglen + 1;
	for (int i = 0; i < total; i++)
	{
		if (memcmp(data + i, tag, taglen) == 0)
		{
			return  i;
		}
	}

	return -1;
}




int lzss_compress(unsigned char* d, int datasize, unsigned char* buf, int bufsize)
{

	unsigned char* data = new unsigned char[datasize + WINDOW_SIZE];
	memcpy(data + WINDOW_SIZE, d, datasize);

	memset(buf, 0, bufsize);

	int total = 0;

	unsigned char* win = data;

	unsigned char* lpd = data + WINDOW_SIZE;

	int pos = 0;

	while (lpd < data + datasize + WINDOW_SIZE) {
		int dl = datasize - (lpd - WINDOW_SIZE - data);	
		for (int j = WINDOW_SIZE; j > sizeof(LZSS_POSITION); j--) {
			int lpdsize = dl > j ? j : dl;
			pos = search(win, WINDOW_SIZE, lpd, lpdsize);
			if (pos >= 0) {
				LZSS_POSITION lzssp;
				lzssp.size = lpdsize;
				lzssp.offset = pos;
				lzssp.prev = 0xff;
				memcpy(buf + total, &lzssp, sizeof(LZSS_POSITION));

				total += sizeof(LZSS_POSITION);
				lpd += lpdsize;
				win += lpdsize;

				break;
			}
		}

		if(pos < 0)
		{
			memcpy(buf + total, lpd, 1);
			total++;
			win++;
			lpd++;
		}
	}

	delete[]data;

	return total;
}



int lzss_decompress(unsigned char* data, int datasize, unsigned char* buffer, int bufsize)
{
	unsigned char* buf = new unsigned char[bufsize + WINDOW_SIZE];

	memset(buf, 0, bufsize + WINDOW_SIZE);

	unsigned char* lpd = buf + WINDOW_SIZE;

	unsigned char* win = buf;

	unsigned char* enc = data ;

	int total = 0;

	while (enc < data + datasize) {
		LZSS_POSITION* lzss = (LZSS_POSITION*)enc;
		if ( lzss->size >= sizeof(LZSS_POSITION) && lzss->prev == 0xff) {
			memcpy(lpd, win + lzss->offset, lzss->size);

			total += lzss->size;
			enc += 3;
			lpd += lzss->size;
			win += lzss->size;
		}
		else {
			memcpy(lpd, enc, 1);

			lpd++;
			win++;
			total++;
			enc++;
		}
	}

	memcpy(buffer, buf + WINDOW_SIZE, total);

	delete[]buf;

	return total;
}



int test_mylzss()
{
	int result = 0;

	HANDLE hf = CreateFileA("test.txt", GENERIC_READ, 0, 0, OPEN_ALWAYS, 0, 0);
	if (hf == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	int filesize = GetFileSize(hf, 0);
	char* data = new char[filesize + 1024];
	
	DWORD cnt = 0;
	result = ReadFile(hf, data, filesize, &cnt, 0);
	CloseHandle(hf);

	unsigned char* encode = new unsigned char[filesize + 1024];
	int  compsize = lzss_compress((unsigned char*)data, filesize, encode, filesize + 1024);
	unsigned char* decode = new unsigned char[filesize + 1024];
	int umcompsize = lzss_decompress(encode, compsize, decode, filesize + 1024);

	HANDLE hfe = CreateFileA("test_encode.txt", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
	if (hfe == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	result = WriteFile(hfe, encode, compsize, &cnt, 0);
	CloseHandle(hfe);

	HANDLE hfd = CreateFileA("test_decode.txt", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
	if (hfd == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	result = WriteFile(hfd, decode, umcompsize, &cnt, 0);
	CloseHandle(hfd);

	return 0;
}