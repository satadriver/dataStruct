

//
//  main.cpp
//  DES算法
//
//  Created by CharlesYan on 2021/4/13.
//

#include <iostream>
#include <stdio.h>
#include<stdlib.h>

#include "des.h"

using namespace std;
//16-wheel secret key structural body
struct Secret_Key {
    int subKey[56] = {};
    int C[28];
    int D[28];
}Secret_KeyOf16[17];//save the 16-wheel sercet key,and the zero flag in order to save the first substitution selection.

// save the process of encryption
struct Encryption {
    int select_Operation[48];
    int secretKey_Operation[48];
    int boxOf_S[32];
    int L[32];
    int R[32];
}Encryption_Pro[17];

int result_Secret[64] = {};



//substitution selection table 1(置换选择1)
static int subSelect_table1[56] = {
    57,49,41,33,25,17, 9, 1,58,50,42,34,26,18,
    10, 2,59,51,43,35,27,19,11, 3,60,52,44,36,
    63,55,47,39,31,23,15, 7,62,54,46,38,30,22,
    14, 6,61,53,45,37,29,21,13, 5,28,20,12, 4
};
//substitution selection table 2(置换选择2)
static int subSelect_table2[48] = {
 14,17,11,24, 1, 5, 3,28,15, 6,21,10,
 23,19,12, 4,26, 8,16, 7,27,20,13, 2,
 41,52,31,37,47,55,30,40,51,45,33,48,
 44,49,39,56,34,53,46,42,50,36,29,32
};
//Move left shift bits table(循环左移位数表)
static int moveLeft_table[17] = { 0,1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 };
//initial substitution IP
static int init_subIP[64] = {
58,50,42,34,26,18,10, 2,60,52,44,36,28,20,12, 4,
62,54,46,38,30,22,14, 6,64,56,48,40,32,24,16, 8,
57,49,41,33,25,17, 9, 1,59,51,43,35,27,19,11, 3,
61,53,45,37,29,21,13, 5,63,55,47,39,31,23,15, 7
};
//selection operation E
static int sel_E[48] = {
32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9,
8, 9,10,11,12,13,12,13,14,15,16,17,
16,17,18,19,20,21,20,21,22,23,24,25,
24,25,26,27,28,29,28,29,30,31,32, 1
};
// Box of S 3D array
static int BoxOf_S[8][4][16] = {
    //S1
    14, 4,13, 1, 2,15,11, 8, 3,10, 6,12, 5, 9, 0, 7,
     0,15, 7, 4,14, 2,13, 1,10, 6,12,11, 9, 5, 3, 8,
     4, 1,14, 8,13, 6, 2,11,15,12, 9, 7, 3,10, 5, 0,
    15,12, 8, 2, 4, 9, 1, 7, 5,11, 3,14,10, 0, 6,13,
    //S2
    15, 1, 8,14, 6,11, 3, 4, 9, 7, 2,13,12, 0, 5,10,
     3,13, 4, 7,15, 2, 8,14,12, 0, 1,10, 6, 9,11, 5,
     0,14, 7,11,10, 4,13, 1, 5, 8,12, 6, 9, 3, 2,15,
    13, 8,10, 1, 3,15, 4, 2,11, 6, 7,12, 0, 5,14, 9,
    //S3
    10, 0, 9,14, 6, 3,15, 5, 1,13,12, 7,11, 4, 2, 8,
    13, 7, 0, 9, 3, 4, 6,10, 2, 8, 5,14,12,11,15, 1,
    13, 6, 4, 9, 8,15, 3, 0,11, 1, 2,12, 5,10,14, 7,
     1,10,13, 0, 6, 9, 8, 7, 4,15,14, 3,11, 5, 2,12,
     //S4
      7,13,14, 3, 0, 6, 9,10, 1, 2, 8, 5,11,12, 4,15,
     13, 8,11, 5, 6,15, 0, 3, 4, 7, 2,12, 1,10,14, 9,
     10, 6, 9, 0,12,11, 7,13,15, 1, 3,14, 5, 2, 8, 4,
      3,15, 0, 6,10, 1,13, 8, 9, 4, 5,11,12, 7, 2,14,
      //S5
       2,12, 4, 1, 7,10,11, 6, 8, 5, 3,15,13, 0,14, 9,
      14,11, 2,12, 4, 7,13, 1, 5, 0,15,10, 3, 9, 8, 6,
       4, 2, 1,11,10,13, 7, 8,15, 9,12, 5, 6, 3, 0,14,
      11, 8,12, 7, 1,14, 2,13, 6,15, 0, 9,10, 4, 5, 3,
      //S6
      12, 1,10,15, 9, 2, 6, 8, 0,13, 3, 4,14, 7, 5,11,
      10,15, 4, 2, 7,12, 9, 5, 6, 1,13,14, 0,11, 3, 8,
       9,14,15, 5, 2, 8,12, 3, 7, 0, 4,10, 1,13,11, 6,
          4, 3, 2,12, 9, 5,15,10,11,14, 1, 7, 6, 0, 8,13,
          //S7
           4,11, 2,14,15, 0, 8,13, 3,12, 9, 7, 5,10, 6, 1,
          13, 0,11, 7, 4, 9, 1,10,14, 3, 5,12, 2,15, 8, 6,
           1, 4,11,13,12, 3, 7,14,10,15, 6, 8, 0, 5, 9, 2,
           6,11,13, 8, 1, 4,10, 7, 9, 5, 0,15,14, 2, 3,12,
           //S8
           13, 2, 8, 4, 6,15,11, 1,10, 9, 3,14, 5, 0,12, 7,
            1,15,13, 8,10, 3, 7, 4,12, 5, 6,11, 0,14, 9, 2,
            7,11, 4, 1, 9,12,14, 2, 0, 6,10,13,15, 3, 5, 8,
            2, 1,14, 7, 4,10, 8,13,15,12, 9, 0, 3, 5, 6,11
};
//substitution IP
static char P_Table[32] = {
 16, 7,20,21,29,12,28,17, 1,15,23,26, 5,18,31,10,
  2, 8,24,14,32,27, 3, 9,19,13,30, 6,22,11, 4,25
};

const int IPR_Table[64] = {
 40, 8,48,16,56,24,64,32,39, 7,47,15,55,23,63,31,
 38, 6,46,14,54,22,62,30,37, 5,45,13,53,21,61,29,
 36, 4,44,12,52,20,60,28,35, 3,43,11,51,19,59,27,
 34, 2,42,10,50,18,58,26,33, 1,41, 9,49,17,57,25
};


//Convert an 8-byte key or plaintext to 64-bit binary
int* ChangeToBit(char code[], int n);
//Subfunction：change Byte to 8-bit binary
int* Change_bit(int a);
//create 16-wheel secret key and save them to Secret_KeyOf16
void set_16wheelKey(int* bit_SecretKey);
//the first step of encryption,set R0, as we know, we will not need L0 later.
void first_StepEncryption(int* bit_PlainText);
//encryption, return the result of encryption
void other_StepEncrtption(int flag);
//Box of S operation
void Box_operation(int* a, int n);
// Box of S change byte to bit
int* Change_bit_S(int a);
//IPR_table operation
void IPR_Operation(int result[]);
void print(int flag);
void Pri_ChangeToByte(int secretKey[]);
void desTest() {
    char my_Plaintext[9] = {};//save plaintext and the last one is '\0'
    char my_SecretKey[9] = {};//save secretkey
    cout << "Please input the plaintext of 8 byte:" << endl;
    cin.get(my_Plaintext, 9);
    cin.get();// getchar();
    cout << "Please input the secret key of 8 byte" << endl;
    cin.get(my_SecretKey, 9);
    printf("\n");
    //8-byte SecretKey turn into 64-bit binary
    int* bit_SecretKey = ChangeToBit(my_SecretKey, 8);
    //create 16-wheel secret key.
    set_16wheelKey(bit_SecretKey);
    //8-byte SecretKey turn into 64-bit binary
    int* bit_Plaintext = ChangeToBit(my_Plaintext, 8);

    //Encryption
    first_StepEncryption(bit_Plaintext);
    other_StepEncrtption(0);//the 0 is meant encryption
    IPR_Operation(result_Secret);
    print(0);

    //Decryption
    first_StepEncryption(result_Secret);
    other_StepEncrtption(1);//the 1 is meant decryption.
    IPR_Operation(result_Secret);
    print(0);
    Pri_ChangeToByte(result_Secret);
}
int* ChangeToBit(char code[], int n) {
    static int BinaryText[64] = {};
    int k = 0;
    for (int i = 0; i < n; i++) {
        int* temp = Change_bit(code[i]);
        for (int j = 0; j < n; j++) {
            BinaryText[k++] = temp[j];
        }
    }

    return BinaryText;
}
int* Change_bit(int a) {
    static int flag[8] = {};
    int k = 7;
    while (a / 2 != 0) {
        flag[k--] = a % 2;
        a = a / 2;
    }
    flag[k] = 1;
    return flag;
}
int* Change_bit_S(int a) {
    static int flag[4] = { 0 };
    int k = 0;
    while (a / 2 != 0) {
        flag[k++] = a % 2;
        a = a / 2;
    }
    if (a == 1)
        flag[k] = 1;
    return flag;
}
void set_16wheelKey(int* bit_SecretKey) {
    //substitution selection 1
    for (int i = 0; i < 56; i++) {
        Secret_KeyOf16[0].subKey[i] = bit_SecretKey[subSelect_table1[i] - 1];
    }
    //C0 D0
    for (int i = 0; i < 28; i++) {
        Secret_KeyOf16[0].C[i] = Secret_KeyOf16[0].subKey[i];
        Secret_KeyOf16[0].D[i] = Secret_KeyOf16[0].subKey[i + 28];
    }
    for (int i = 1; i < 17; i++) {
        if (moveLeft_table[i] == 1) {
            for (int j = 0; j < 27; j++) {
                Secret_KeyOf16[i].C[j] = Secret_KeyOf16[i - 1].C[j + 1];
                Secret_KeyOf16[i].D[j] = Secret_KeyOf16[i - 1].D[j + 1];
            }
            Secret_KeyOf16[i].C[27] = Secret_KeyOf16[i - 1].C[0];
            Secret_KeyOf16[i].D[27] = Secret_KeyOf16[i - 1].D[0];
        }
        else {
            for (int j = 0; j < 26; j++) {
                Secret_KeyOf16[i].C[j] = Secret_KeyOf16[i - 1].C[j + 2];
                Secret_KeyOf16[i].D[j] = Secret_KeyOf16[i - 1].D[j + 2];
            }
            Secret_KeyOf16[i].C[26] = Secret_KeyOf16[i - 1].C[0];
            Secret_KeyOf16[i].C[27] = Secret_KeyOf16[i - 1].C[1];
            Secret_KeyOf16[i].D[26] = Secret_KeyOf16[i - 1].D[0];
            Secret_KeyOf16[i].D[27] = Secret_KeyOf16[i - 1].D[1];
        }
    }
    //subKey1 ... subKey16
    for (int i = 1; i < 17; i++) {
        int flag[56] = {};
        for (int j = 0; j < 28; j++) {
            flag[j] = Secret_KeyOf16[i].C[j];
            flag[j + 28] = Secret_KeyOf16[i].D[j];
        }
        for (int j = 0; j < 48; j++) {
            Secret_KeyOf16[i].subKey[j] = flag[subSelect_table2[j] - 1];
        }
    }
    //print the result of secret key.
    for (int i = 1; i < 17; i++) {
        printf("N = %d\n", i);
        printf("C%d：", i);
        for (int j = 0; j < 28; j++) {
            printf("%d", Secret_KeyOf16[i].C[j]);
        }
        printf("\n");
        printf("D%d：", i);
        for (int j = 0; j < 28; j++) {
            printf("%d", Secret_KeyOf16[i].D[j]);
        }
        printf("\n");
        printf("子密钥%d：", i);
        for (int j = 0; j < 48; j++) {
            if (j % 8 == 0 && j) printf(" ");
            printf("%d", Secret_KeyOf16[i].subKey[j]);
        }
        printf("\n\n");
    }
}
void first_StepEncryption(int* bit_PlainText) {
    for (int i = 0; i < 32; i++) {
        Encryption_Pro[0].L[i] = bit_PlainText[init_subIP[i] - 1];
        Encryption_Pro[0].R[i] = bit_PlainText[init_subIP[i + 32] - 1];
    }
}
void other_StepEncrtption(int flag) {
    for (int i = 1; i < 17; i++) {
        for (int j = 0; j < 48; j++) {
            //selection
            Encryption_Pro[i].select_Operation[j] = Encryption_Pro[i - 1].R[sel_E[j] - 1];
            //secretion operation
            if (flag == 0)
                Encryption_Pro[i].secretKey_Operation[j] = Secret_KeyOf16[i].subKey[j] ^ Encryption_Pro[i].select_Operation[j];
            else
                Encryption_Pro[i].secretKey_Operation[j] = Secret_KeyOf16[17 - i].subKey[j] ^ Encryption_Pro[i].select_Operation[j];
        }
        // Box of S
        Box_operation(Encryption_Pro[i].secretKey_Operation, i);
        // XOR operation
        for (int j = 0; j < 32; j++) {
            Encryption_Pro[i].L[j] = Encryption_Pro[i - 1].R[j];
            Encryption_Pro[i].R[j] = Encryption_Pro[i - 1].L[j] ^ Encryption_Pro[i].boxOf_S[P_Table[j] - 1];
        }
    }
}
void Box_operation(int* a, int n) {
    int sum = 0;
    for (int i = 0; i < 48; i += 6) {
        int flag1 = BoxOf_S[i / 6][a[i] * 2 + a[i + 5]][a[i + 1] * 8 + a[i + 2] * 4 + a[i + 3] * 2 + a[i + 4]];
        int flag[4] = { 0 };
        int k = 0;
        while (flag1 / 2 != 0) {
            flag[k++] = flag1 % 2;
            flag1 = flag1 / 2;
        }
        if (flag1 == 1)
            flag[k] = 1;
        for (int j = 3; j >= 0; j--) {
            Encryption_Pro[n].boxOf_S[sum++] = flag[j];

        }

    }
}
void IPR_Operation(int result[]) {
    int temp[64] = {};
    for (int i = 0; i < 32; i++) {
        temp[i] = Encryption_Pro[16].R[i];
        temp[32 + i] = Encryption_Pro[16].L[i];
    }
    for (int i = 0; i < 64; i++) {
        result[i] = temp[IPR_Table[i] - 1];
    }
}
void print(int flag) {
    for (int i = 1; i < 17; i++) {
        printf("\nN = %d\n", i);
        printf("选择运算：");
        for (int j = 0; j < 48; j++) {
            if (j % 8 == 0 && j) printf(" ");
            printf("%d", Encryption_Pro[i].select_Operation[j]);
        }
        printf("\n子密钥加：");
        for (int j = 0; j < 48; j++) {
            if (j % 8 == 0 && j) printf(" ");
            printf("%d", Encryption_Pro[i].secretKey_Operation[j]);
        }
        printf("\nS盒：");
        for (int j = 0; j < 32; j++) {
            if (j % 8 == 0 && j) printf(" ");
            printf("%d", Encryption_Pro[i].boxOf_S[j]);
        }
        printf("\nL：");
        for (int j = 0; j < 32; j++) {
            if (j % 8 == 0 && j) printf(" ");
            printf("%d", Encryption_Pro[i].L[j]);
        }
        printf("\nR：");
        for (int j = 0; j < 32; j++) {
            if (j % 8 == 0 && j) printf(" ");
            printf("%d", Encryption_Pro[i].R[j]);
        }
        printf("\n");
    }
    printf("\n");
    if (flag == 0)
        cout << "the result of secret text: " << endl;
    else
        cout << "the result of plain text: " << endl;
    for (int i = 0; i < 64; i++) {
        if (i % 8 == 0 && i != 0) printf(" ");
        printf("%d", result_Secret[i]);
    }
    printf("\n");
}
void Pri_ChangeToByte(int secretKey[]) {
    char temp[8] = {};
    int k = 0;
    for (int i = 0; i < 64; i += 8) {
        int sum = 0;
        for (int j = i; j < i + 8; j++) {
            sum += secretKey[j] * pow(2, 7 - j % 8);
        }
        temp[k++] = sum;
    }
    cout << "the plaintext of 8 byte is :" << endl;
    for (int i = 0; i < 8; i++) {
        printf("%c", temp[i]);
    }
    printf("\n");
}

