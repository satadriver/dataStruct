#pragma once

#include <winsock.h>
#include <string>

using namespace std;



static bool g_initalization = 0;

class Network {
private:
	sockaddr_in m_saServer;
	SOCKET m_sock;
	bool m_working;

public:
	
	Network(string serverip,unsigned short serverport);
	~Network();

	void connectServer();

	int writeData(char * data, int size);
	int readData(char * data, int size);

	static int initNetwork();

	static void uninitNetwork();
};