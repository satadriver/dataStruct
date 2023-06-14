#include <windows.h>

#include <stdio.h>

#define BLOCKSIZE  0x10000
char* srcfilename = "src.txt";
char* dstfilename = "dst.txt";


//#define WINDOW_FIXED

#pragma pack(1)

typedef struct
{
	WORD offset;
	WORD size;

}DATASTRUCT;

#pragma pack()



int search(unsigned char* data, int size, unsigned char* flag, int flaglen) {
	if (size < flaglen || flaglen == 0 || size == 0)
	{
		return -1;
	}

	int total = size - flaglen;
	for (int i = 0; i < total; i++)
	{
		if (memcmp(data + i, flag, flaglen) == 0)
		{
			return  i;
		}
	}

	return -1;
}




int writelog(char* filename, char* data, int size) {
	int result = 0;
	HANDLE hf = CreateFileA(filename, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_ALWAYS, 0, 0);
	if (hf == INVALID_HANDLE_VALUE) {
		return FALSE;
	}
	DWORD filesize = GetFileSize(hf, 0);

	result = SetFilePointer(hf, filesize, 0, FILE_BEGIN);

	DWORD cnt = 0;
	result = WriteFile(hf, data, size, &cnt, 0);

	CloseHandle(hf);

	return cnt;
}


int lzss_compress(unsigned char* data, int size, unsigned char* buf, int bufsize, unsigned char* datamap, int mapsize) {

	unsigned char* window = data;

	unsigned char* dst = buf;

	unsigned char* src = data;

	int windowsize = 0;

	int result = 0;

	while (src < data + size)
	{
		unsigned long findsize = 4 - 1;
		unsigned long offset = 0;
		while (findsize < BLOCKSIZE)
		{
			int least = data + size - src;

			if (findsize >= least)
			{
				memmove(dst, src, least);
				dst += least;
				src += least;
				windowsize++;
				if (windowsize >= BLOCKSIZE)
				{
					window = window + BLOCKSIZE;
					windowsize = 0;
				}
				return dst - buf;
			}

			result = search(window, windowsize, src, findsize + 1);
			if (result != -1)
			{
				offset = result;
				findsize++;
			}
			else {
				break;
			}
		}

		if (findsize > 4)
		{

			*(WORD*)dst = offset;
			*(WORD*)(dst + sizeof(WORD)) = findsize;

			int byte_offset = dst - buf;
			int bit_off_mod = byte_offset % 8;
			int bit_off = byte_offset / 8;

			DWORD value = *(datamap + bit_off);
			DWORD orvalue = 0xf;
			if (bit_off_mod)
			{
				orvalue = 0xf << (bit_off_mod);
			}

			orvalue = orvalue | value;
			*(datamap + bit_off) = (unsigned char)orvalue;
			*(datamap + bit_off + 1) = (unsigned char)(orvalue >> 8);

#ifdef		WINDOW_FIXED
			if (windowsize < BLOCKSIZE)
			{
				windowsize += findsize;
				if (windowsize > BLOCKSIZE)
				{
					windowsize = windowsize % BLOCKSIZE;
					window += BLOCKSIZE;
				}
			}
			else {
				window = window + findsize;
			}
#else
			windowsize += findsize;
			if (windowsize >= BLOCKSIZE)
			{
				windowsize = windowsize % BLOCKSIZE;
				window = window + BLOCKSIZE;
			}
#endif
			dst += 4;
			src += findsize;

			DATASTRUCT mydatastruct;
			mydatastruct.offset = offset;
			mydatastruct.size = findsize;
			writelog(srcfilename, (char*)&mydatastruct, sizeof(DATASTRUCT));
		}
		else {

			*dst = *src;
			dst++;
			src++;

#ifdef WINDOW_FIXED
			if (windowsize < BLOCKSIZE)
			{
				windowsize++;
			}
			else {
				window++;
			}
#else
			windowsize++;
			if (windowsize >= BLOCKSIZE)
			{
				window = window + BLOCKSIZE;
				windowsize = 0;
			}
#endif
		}
	}

	return dst - buf;

}


int lzss_decompress(unsigned char* data, int size, unsigned char* buf, int bufsize, unsigned char* datamap, int mapsize) {

	unsigned char* window = buf;

	int windowsize = 0;

	unsigned char* dst = buf;

	unsigned char* src = data;

	int offset = 0;

	while (src < data + size)
	{

		DWORD value = *(datamap + offset) + (*(datamap + offset + 1) << 8);

		for (DWORD i = 0; i < 8 && i >= 0; i++)
		{
			DWORD testkey = (0xf << i);

			int data_off = offset * 8 + i;

			int src_off = src - data;

			if ((value & testkey) == testkey)
			{
				WORD* structdata = (WORD*)(data_off + data);
				WORD window_offset = *structdata;
				int findsize = *(WORD*)(structdata + 1);
				if (findsize > 100 || findsize < 4)
				{
					printf("error\r\n");
				}

				memmove(dst, window + window_offset, findsize);
				//src += 4;
				dst += findsize;

#ifdef		WINDOW_FIXED
				if (windowsize < BLOCKSIZE)
				{
					windowsize += findsize;
					if (windowsize > BLOCKSIZE)
					{
						windowsize = windowsize % BLOCKSIZE;
						window += BLOCKSIZE;
					}
				}
				else {
					window = window + findsize;
				}


#else
				windowsize += findsize;
				if (windowsize >= BLOCKSIZE)
				{
					windowsize = windowsize % BLOCKSIZE;
					window = window + BLOCKSIZE;
				}
#endif

				i += 4;
				if (i >= 8)
				{
					//i -= 8;

					//offset++;
					//continue;
				}
				//value = (~testkey) & value;
				//value = *(datamap + offset) + (*(datamap + offset + 1) << 8);
			}
			else {
				*dst = *src;
				dst++;
				src++;

#ifdef WINDOW_FIXED
				if (windowsize < BLOCKSIZE)
				{
					windowsize++;
				}
				else {
					window++;
				}
#else
				windowsize++;
				if (windowsize >= BLOCKSIZE)
				{
					window = window + BLOCKSIZE;
					windowsize = 0;
				}
#endif
			}
		}
		offset++;
	}
	return dst - buf;
}


int test_lgzz()
{

	HANDLE hf = CreateFileA("test.txt", GENERIC_READ, 0, 0, OPEN_ALWAYS, 0, 0);
	if (hf == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}


	int filesize = GetFileSize(hf, 0);
	char* data = new char[filesize + 1024];


	int result = 0;
	DWORD cnt = 0;
	result = ReadFile(hf, data, filesize, &cnt, 0);

	CloseHandle(hf);

	unsigned char* dstbuf = new unsigned char[filesize + 1024];

	unsigned char* datamap = new unsigned char[filesize + 1024];
	memset(datamap, 0, filesize);
	int  compsize = lzss_compress((unsigned char*)data, filesize, dstbuf, filesize + 1024, datamap, filesize);

	unsigned char* dstbuf2 = new unsigned char[filesize + 1024];

	lzss_decompress(dstbuf, compsize, dstbuf2, filesize + 1024, datamap, filesize);

	return 0;
}