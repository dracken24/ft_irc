/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dracken24 <dracken24@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:47:23 by dracken24         #+#    #+#             */
/*   Updated: 2023/04/26 08:28:36 by dracken24        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcCore.hpp"

void    CheckEntry(IrcCore *irc, Logger *log, int argc, char **argv)
{
	if (argc != 3)
	{
		log->FATAL("Error, Usage: <%s> <port> <password>.", argv[0]);
		exit(-1);
	}

	if (!IsDigit(argv[1]))
	{
		log->FATAL("Error, Port not numeric.", argv[0]);
		exit(-1);
	}

	if (!IsAscii(argv[2]) || (std::strlen(argv[2]) < 8 || std::strlen(argv[2]) > 16))
	{
		log->FATAL("Error, Password need to be between 33 & 126 in Ascii table.", argv[0]);
		log->FATAL("Password need to be between 8 & 16 characters.", argv[0]);
		exit(-1);
	}

	if (MAX_CLIENTS > 250)
	{
		log->FATAL("Error, MAX_CLIENTS is set to more than 250.", argv[0]);
		exit(-1);
	}
	
	// Save port and password
	irc->SetPort(atoi(argv[1]));
	irc->SetPassword(argv[2]);
}

void	FindFirstUsableAddress(IrcCore	*irc, Logger *log, addrinfo *serverInfo, addrinfo *p)
{
	// Find the first usable address structure
	for (*p = *serverInfo; p != NULL; p = p->ai_next)
	{
		// Socket creation
		static int sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		irc->SetServerSocket(&sock);
		int *serverSocket = irc->GetServerSocket();
		if (*serverSocket == -1)
		{
			log->FATAL("ERROR opening socket");
		}

		// Disable protection against addresses already in use
		int yes = 1;
		int result = setsockopt(*serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
		if (result == -1)
		{
			close(*serverSocket);
			log->FATAL("Error when disabling protection against addresses already in use");
			exit(1);
		}

		// Assign address and port
		result = bind(*serverSocket, p->ai_addr, p->ai_addrlen);
		if (result == -1)
		{
			close(*serverSocket);
			continue;
		}

		break;
	}
}

void	BuildServerInfo(IrcCore	*irc, Logger *log, std::string port)
{
	// Initialization of address structures
	struct addrinfo	hints, *serverInfo, *p;
	p = (addrinfo *)std::memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_INET;			// IPv4 only
	hints.ai_socktype = SOCK_STREAM;	// TCP
	hints.ai_flags = AI_PASSIVE;		// Use local adress

	
	// Host name resolution
	int result = getaddrinfo(NULL, port.c_str(), &hints, &serverInfo);
	if (result != 0)
	{
		std::string ret = "Error resolving host name: ";
		ret += gai_strerror(result);
		log->FATAL(ret.c_str());
		exit(1);
	}

	// Find the first usable address structure, LINK: <init.cpp>
	static int sock = -1;
	irc->SetServerSocket(&sock);
	FindFirstUsableAddress(irc, log, serverInfo, p);

	// Free memory used by address structures
	freeaddrinfo(serverInfo);

	// Check the creation of the socket
	if (p == NULL)
	{
		log->FATAL("Error, when create socket");
		exit(1);
	}

}

void	SetQueueSocketAndClient(IrcCore	*irc, Logger *log)
{
	// Definition of the non-blocking mode of the socket
	int *serverSocket = irc->GetServerSocket();
	int result = fcntl(*serverSocket, F_SETFL, O_NONBLOCK);
	if (result == -1)
	{
		log->FATAL("Error, when passing in non-blocking mode");
		close(*serverSocket);
		exit(1);
	}

	// Define the size of the connection queue
	result = listen(*serverSocket, MAX_CLIENTS);
	if (result == -1)
	{
		log->FATAL("Error, when passing in listen mode");
		close(*serverSocket);
		exit(1);
	}

	// Create poll structure for server socket and clients
	struct pollfd *fds = irc->GetPoolfds();
	std::memset((void *)fds, 0, sizeof(fds));
	fds[0].fd = *serverSocket;
	fds[0].events = POLLIN;
	// irc->SetPoolfds(fds);
}
