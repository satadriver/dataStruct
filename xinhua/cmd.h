#pragma once

#include <windows.h>
#include "network.h"
#include <string>

using namespace std;

#define PACKET_BUF_SIZE 0X1000

#pragma pack(1)
typedef struct
{
	unsigned char flag[6];
	unsigned int datasize;
	unsigned short type;
	unsigned short retcode;
	unsigned short cmd;
}XINHUA_PACK_HDR, *LPXINHUA_PACK_HDR;
#pragma pack()

#pragma pack(1)
typedef struct {
	unsigned char oldpw[16];
	unsigned char newpw[16];
}XINHUA_RESET_PW_DATA;

typedef struct {
	unsigned char username[6];
	unsigned char password[16];
}XINHUA_LOGIN_DATA;
#pragma pack()

class Cmd {
private:
	Network * m_network;
	int m_tickCnt;
	int m_target;
public:
	Cmd(string serverip,int target);
	~Cmd();

	int writePacket(unsigned short cmd,unsigned short type,char * data,int datasize);
	
	int readPacket( char * data, int datasize);

	static void mainwork(Cmd*cmd);
};
