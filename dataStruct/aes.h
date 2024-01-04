#pragma once

#define uint32_t unsigned int

#define uint8_t unsigned char

int aesTest();

#pragma pack(1)

typedef struct {
    uint32_t eK[44], dK[44];    // encKey, decKey
    int Nr; // 10 rounds
}AesKey;

#pragma pack()