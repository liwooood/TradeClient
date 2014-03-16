#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>

class ClientSocket
{
public:
	ClientSocket(void);
	~ClientSocket(void);

	int Connect(const char * server, int port, int connectTimeout);
	int Send(const char * buf, int len, int flags);
	int Recv(char* buf, int len, int flags);

private:
	SOCKET sockfd;
};

