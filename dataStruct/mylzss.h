#pragma once

int test_lgzz();
int lzss_compress(unsigned char* data, int size, unsigned char* buf, int bufsize);


int lzss_decompress(unsigned char* data, int size, unsigned char* buf, int bufsize);