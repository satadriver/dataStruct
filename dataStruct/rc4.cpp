

#include<stdio.h>
#include<string.h>
#include "rc4.h"




#define KEY_SIZE 1024

/*��ʼ������*/
void rc4_init(unsigned char* s, unsigned char* key, unsigned long Len)
{
    int i = 0, j = 0;
    char k[KEY_SIZE] = { 0 };
    unsigned char tmp = 0;
    for (i = 0; i < KEY_SIZE; i++)
    {
        s[i] = i;
        k[i] = key[i % Len];
    }

    for (i = 0; i < KEY_SIZE; i++)
    {
        j = (j + s[i] + k[i]) % KEY_SIZE;

        tmp = s[i];
        s[i] = s[j];//����s[i]��s[j]
        s[j] = tmp;
    }
}

/*�ӽ���*/
void rc4_crypt(unsigned char* s, unsigned char* Data, unsigned long Len)
{
    int i = 0, j = 0, t = 0;
    unsigned long k = 0;
    unsigned char tmp;

    for (k = 0; k < Len; k++)
    {
        
        j = (j + s[i]) % KEY_SIZE;

        tmp = s[i];
        s[i] = s[j];//����s[x]��s[y]
        s[j] = tmp;

        t = (s[i] + s[j]) % KEY_SIZE;
        Data[k] ^= s[t];

        i = (i + 1) % KEY_SIZE;
    }
}

int rc4_test()
{
    unsigned char s[KEY_SIZE] = { 0 }, s2[KEY_SIZE] = { 0 };//S-box

    char key[KEY_SIZE] = { "this is the key to init RC4 key" };

    char pData[512] = "[Data]����һ����������RC4�ӽ����㷨�����ݣ��˶����ݻᱻ�������ܺͽ��ܡ����������ʾ���Ա���֤RC4�ӽ����㷨����ȷ��[Data]";

    unsigned long datalen = strlen(pData);

    printf("�ӽ��ܲ�������:\"%s\"\n\n", pData);

    printf("RC4��Կ:\"%s\",����:%d\n\n", key, strlen(key));

    rc4_init(s, (unsigned char*)key, strlen(key));

    printf("S-box��ʼ������:\r\n");
    for (int i = 0; i < KEY_SIZE; i++)
    {
        printf("%02X", s[i]);
        if (i && (i + 1) % 16 == 0)
            putchar('\n');
    }
    printf("\n\n");

    for (int i = 0; i < KEY_SIZE; i++)//��s2[i]��ʱ����������ʼ����s[i]
    {
        s2[i] = s[i];
    }

    
    rc4_crypt(s, (unsigned char*)pData, datalen);//����
    printf("RC4���ܺ������:%s\r\n\r\n", pData);

    
    rc4_init(s2,(unsigned char*)key,strlen(key));//��ʼ����Կ
    rc4_crypt(s2, (unsigned char*)pData, datalen);//����
    printf("RC4���ܺ������:%s\r\n\r\n", pData);

    return 0;
}


