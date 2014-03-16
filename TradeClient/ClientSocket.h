#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>

class ClientSocket
{
public:
	ClientSocket(void);
	~ClientSocket(void);

	int Connect();
};

