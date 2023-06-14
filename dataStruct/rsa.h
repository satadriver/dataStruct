#pragma once

#define  myInt64 unsigned long long

myInt64 pow_i(myInt64 a, myInt64 b);

myInt64 pow_i(myInt64 a, myInt64 b, myInt64 g_n);

int rsaInit(myInt64 p, myInt64 q);

int rsa_encrypt(char* data, int size, char* dst);

int rsa_decrypt(char* data, int size, char* dst);