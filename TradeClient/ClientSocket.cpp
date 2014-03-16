#include "ClientSocket.h"

#pragma comment(lib, "Ws2_32.lib")

ClientSocket::ClientSocket(void)
{
}


ClientSocket::~ClientSocket(void)
{
}

int ClientSocket::Connect(const char * server, int port, int connectTimeout)
{
	int rc = 0;
	u_long bio = 1;
	//int connectTimeout = 3;
	int readWriteTimeout = 3000;
	sockfd = INVALID_SOCKET;


	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockfd == INVALID_SOCKET )
	{
		return FALSE;
	}
	
	//设置为非阻塞模式
	bio = 1;
	rc = ioctlsocket(sockfd, FIONBIO, &bio); 
	if (rc == SOCKET_ERROR)
	{
		closesocket(sockfd);
		return FALSE;
	}
	
	
	
	

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(server);
	addr.sin_port = htons(port);

	rc = connect(sockfd, (const sockaddr *)&addr, sizeof(addr));
	// 异步模式不用判断
	if (rc == SOCKET_ERROR)
	{
		//closesocket(sockfd);
		//return FALSE;
	}

	
	
	
	fd_set writefds;
	FD_ZERO(&writefds);
	FD_SET(sockfd, &writefds);

	struct timeval timeout;
	timeout.tv_sec = connectTimeout;
	timeout.tv_usec = 0;

	rc = select(0, NULL, &writefds, NULL, &timeout);
	if (rc == 0)
	{
		// timeout
		closesocket(sockfd);
		return FALSE;
	}

	if (rc == SOCKET_ERROR)
	{
		closesocket(sockfd);
		return FALSE;
	}

	if(!FD_ISSET(sockfd, &writefds))  
    {  
		closesocket(sockfd);
		return FALSE;
    }  

	 
	// 设置为阻塞模式
	bio = 0;
	rc = ioctlsocket(sockfd, FIONBIO, &bio);
	if (rc == SOCKET_ERROR)
	{
		closesocket(sockfd);
		return FALSE;
	}

	// 设置读写超时
	rc = setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,(char*)&readWriteTimeout, sizeof(readWriteTimeout));
    rc = setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO,(char*)&readWriteTimeout, sizeof(readWriteTimeout));

	return TRUE;
}

int ClientSocket::Send(const char * buf, int len, int flags)
{
	int rc = 0;
	
	int totalBytes = 0;

	do
	{
		int bytes = 0;
		bytes = send(sockfd, buf + totalBytes, len - totalBytes, flags);
		if (bytes == 0)
		{
			// connection is closed
			break;
		}

		if (bytes < 0)
		{
			break;
		}

		totalBytes += bytes;


	} while(totalBytes < len);

	if (totalBytes != len)
		rc = FALSE;
	else
		rc = TRUE;

	return rc;
}

int ClientSocket::Recv(char* buf, int len, int flags)
{
	int rc = 0;
	int totalBytes = 0;

	do
	{
		int bytes = 0;
		bytes = recv(sockfd, buf + totalBytes, len - totalBytes, flags);
		if (bytes == 0)
		{
			// connection is closed
			break;
		}

		if (bytes < 0)
		{
			break;
		}

		totalBytes += bytes;


	} while(totalBytes < len);

	if (totalBytes != len)
		rc = FALSE;
	else
		rc = TRUE;

	return rc;
}
