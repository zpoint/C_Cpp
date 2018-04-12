#pragma once
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include "Practical.h"

static const int MAXPENDING = 5; // Maximum outstanding connection requests

void HandleTCPClientCommon(int clntSocket)
{
		char buffer[BUFSIZ]; // Buffer for echo string

		// Receive message from client
		ssize_t numBytesRcvd = recv(clntSocket, buffer, BUFSIZ-1, 0);
		if (numBytesRcvd < 0)
				DieWithSystemMessage("recv() failed");
		buffer[numBytesRcvd] = '\0';
		// Send received string and receive again until end of stream
		while (numBytesRcvd > 0)
		{
				// 0 indicates end of stream
				// Echo message back to client
				// printf("numBytesRcvd: %ld, buffer: %s\n", numBytesRcvd, buffer);
				ssize_t numBytesSent = send(clntSocket, buffer, numBytesRcvd, 0);
				if (numBytesSent < 0)
						DieWithSystemMessage("send() failed");
				else if (numBytesSent != numBytesRcvd)
						DieWithUserMessage("send()", "sent unexpected number of bytes");

				// See if there is more data to receive
				// printf("numBytesSent: %ld\n", numBytesSent);
				numBytesRcvd = recv(clntSocket, buffer, BUFSIZ, 0);
				if (numBytesRcvd < 0)
						DieWithSystemMessage("recv() failed");
				buffer[numBytesRcvd] = '\0';
		}
}

void HandleTCPClient(int clntSocket)
{
		HandleTCPClientCommon(clntSocket);
		close(clntSocket); // close client socket
}

void HandleTCPClientSleep(int clntSocket, unsigned secondsToSleep)
{
		printf("clntSocket num: %d, Going to sleep for %d seconds\n", clntSocket, secondsToSleep);
		sleep(secondsToSleep);
		HandleTCPClientCommon(clntSocket);
		printf("clntSocket num: %d, sleep done, going to close\n", clntSocket);
		close(clntSocket);
}

int SetupTCPServerSocket(const char *service)
{
		// Construct the server address structure
		struct addrinfo addrCriteria; // Criteria for address match
		memset(&addrCriteria, 0, sizeof(addrCriteria)); // Zero out structure
		addrCriteria.ai_family = AF_UNSPEC; // Any address family
		addrCriteria.ai_flags = AI_PASSIVE; // Accept on any address/port
		addrCriteria.ai_socktype = SOCK_STREAM; // Only stream sockets
		addrCriteria.ai_protocol = IPPROTO_TCP; // Only TCP protocol

		struct addrinfo *servAddr; // List of server addresses
		int rtnVal = getaddrinfo(NULL, service, &addrCriteria, &servAddr);
		if (rtnVal != 0)
				DieWithUserMessage("getaddrinfo() failed", gai_strerror(rtnVal));

		int servSock = -1;
		for (struct addrinfo *addr = servAddr; addr != NULL; addr = addr->ai_next)
		{
				// Create a TCP socket
				servSock = socket(servAddr->ai_family, servAddr->ai_socktype, servAddr->ai_protocol);
				if (servSock < 0)
						continue;  // Socket creation failed; try next address

				// Bind to the local address and set socket to list
				if ((bind(servSock, servAddr->ai_addr, servAddr->ai_addrlen) == 0) && 
								listen(servSock, MAXPENDING) == 0)
				{
						// Print local address of socket
						struct sockaddr_storage localAddr;
						socklen_t addrSize = sizeof(localAddr);
						if (getsockname(servSock, (struct sockaddr *) &localAddr, &addrSize) < 0)
								DieWithSystemMessage("getsockname() failed");
						fputs("Binding to ", stdout);
						PrintSocketAddress((struct sockaddr *) &localAddr, stdout);
						fputc('\n', stdout);
						if (servAddr->ai_family == AF_INET)
								printf("AF_INET\n");
						else if (servAddr->ai_family == AF_INET6)
								printf("AF_INET6\n");
						else
								printf("Unknown AF Family\n");
						break;
				}

				close(servSock); // Close and try again
				servSock = -1;
		}

		// Free address list allocated by getaddrinfo()
		freeaddrinfo(servAddr);

		return servSock;
}

int AcceptTCPConnection(int servSock)
{
		struct sockaddr_storage clntAddr; // Client address
		// Set length of client address structure (in-out parameter)
		socklen_t clntAddrLen = sizeof(clntAddr);

		// Wait for a client to connect
		int clntSock = accept(servSock, (struct sockaddr *)&clntAddr, &clntAddrLen);
		if (clntSock < 0)
				DieWithSystemMessage("accept() failed");

		// clntSock is connected to a client
		
		fputs("Handling client ", stdout);
		PrintSocketAddress((struct sockaddr *) &clntAddr, stdout);
		fputc('\n', stdout);

		return clntSock;
}
