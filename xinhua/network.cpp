
#include <Windows.h>
#include "network.h"
#include <winsock.h>
#include <stdio.h>

#include <iostream>
#include <stdlib.h>

#pragma comment (lib,"ws2_32")

using namespace std;


int Network::initNetwork() {
	int ret = 0;
	WSADATA wsa = { 0 };
	ret = WSAStartup(MAKEWORD(2, 2), &wsa);
	return ret;
}

void Network::uninitNetwork() {
	WSACleanup();
}

Network::Network(string serverip, unsigned short serverport) {

	if (g_initalization==FALSE)
	{
		int ret = initNetwork();
		if (ret)
		{
			return;
		}
		g_initalization = TRUE;
	}

	memset(&m_saServer, 0, sizeof(sockaddr_in));
	this->m_saServer.sin_family = AF_INET;
	m_saServer.sin_addr.S_un.S_addr = inet_addr(serverip.c_str());
	m_saServer.sin_port = htons(serverport);
}

Network::~Network() {

	if (m_working)
	{
		if (m_sock)
		{
			closesocket(m_sock);
		}
	}
}

void Network::connectServer() {
	m_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);	
	if (m_sock == INVALID_SOCKET)
	{
		m_working = FALSE;
		return;
	}

	int ret = connect(m_sock, (SOCKADDR*)&m_saServer, sizeof(sockaddr_in));
	if (ret == 0)
	{
		m_working = TRUE;
	}
	else {
		m_working = FALSE;
	}
}



int Network::readData(char * data, int bufsize) {
	if (m_working)
	{
		int len = recv(m_sock, data, bufsize, 0);

		return len;
	}
	return -1;
}


int Network::writeData(char * data, int size) {
	if (m_working)
	{
		int len = send(m_sock, data, size, 0);

		return len;
	}
	return -1;
}


