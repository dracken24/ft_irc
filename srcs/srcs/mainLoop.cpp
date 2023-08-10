/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainLoop.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayrand <smayrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:30:36 by dracken24         #+#    #+#             */
/*   Updated: 2023/08/09 13:44:01 by smayrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcCore.hpp"
#include "../others/Splinter.hpp"

#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sstream>

bool loop = true;
static std::map<std::string, std::vector<int> > channels;

void	QuitSignal(int nbr)
{ 
	// std::cout << "QuiSignal : " << nbr << std::endl;
	loop = false;
}

void	MainLoop(IrcCore *irc, Logger *log, IrcMemory *ircMemory)
{
	int32 *serverSocket = irc->GetServerSocket();
	pollfd *fds = irc->GetPoolfds();

	signal(SIGINT, QuitSignal);
	// Main loop
	while (loop)
	{
				log->DEBUG("ML: 1");
		// Wait for data on sockets
		int32 result = poll(fds, MAX_CLIENTS + 1, -1);
		if (result == -1 && loop == true)
		{
			log->ERROR("Error when waiting socket data");
			continue;
		}

		if (result == POLLIN)
		{
			// Check for the presence of new connections
			CheckIfNewConnexion( irc, log, ircMemory, fds, serverSocket);
		}

		// Processing data from customers
		ReceveAndSplitMessages(irc, log, ircMemory, fds);
	}
	close(*serverSocket);
	for (int32 i = 0; i < MAX_CLIENTS + 1; i++)
	{
		close(fds[i].fd);
	}

	log->DEBUG("Good Quit MainLoop\n");
}

void	ReceveAndSplitMessages(IrcCore *irc, Logger *log, IrcMemory *ircMemory, pollfd *fds)
{
	char buffer[MAX_MSG_LEN];
	for (int32 i = 1; i <= MAX_CLIENTS; i++)
	{
		if (fds[i].revents & POLLIN)
		{
			log->DEBUG("ML: for1 if1: 1 FD: %d", fds[i].fd);

			int32 numBytes = recv(fds[i].fd, buffer, MAX_MSG_LEN, 0); // Message entry from clients
			buffer[numBytes] = '\0';

			if (numBytes == -1)
			{
				log->ERROR("Error while receiving data from client");
				continue;
			}
			else if (numBytes == 0)
			{
				// The client closed the connection
				log->ERROR("Client #%d Logout", i);
				close(fds[i].fd);
				fds[i].fd = 0;
				continue;
			}

			log->WARNING("BUFFERRR: %s", buffer);
			// Ct_mprintf(buffer, std::strlen(buffer), 1, 'A');

			if (irc->GetAccess(i) == false)
			{
				log->WARNING("check pass");
				CheckClientsPassword(irc, log, ircMemory, fds, buffer, i);
			}
			else
			{
				// catch commands like /list, /join ....
				ChooseCommand(irc, log, ircMemory, fds, buffer, i);
			}
		}
	}
}

void	CheckIfNewConnexion(IrcCore *irc, Logger *log, IrcMemory *ircMemory,
			pollfd *fds, int32 *serverSocket)
{
	// Check for the presence of new connections
	if (fds[0].revents & POLLIN)
	{
		log->DEBUG("ML if1: 1");
		// New connection accepted
		int32 clientSocket = accept(*serverSocket, NULL, NULL);
		if (clientSocket == -1)
		{
			log->ERROR("Error when waiting socket data");
			// continue;
		}

		// Search for a free location in the structure of poll
		int32 i;
		for (i = 1; i <= MAX_CLIENTS; i++)
		{
			// Check for the existence of a free slot
			if (i > MAX_CLIENTS)
			{
				log->ERROR("Maximum number of customers reached");
				close(clientSocket);
			}
			else if (fds[i].fd == 0)
			{
				fds[i].fd = clientSocket;
				fds[i].events = POLLIN;
				
				ircClient	*client = (ircClient *)ircMemory->Mallocate(sizeof(ircClient), IRC_MEMORY_TAG_CLIENTS, log);
				client = (ircClient *)std::memset(client, 0, sizeof(ircClient));
				irc->SetNewlient(client, log, fds, i, true);

				log->TRACE("Client #%d enter chat.", i);
				break;
			}
		}
	}
}

void	ChooseCommand(IrcCore *irc, Logger *log, IrcMemory *ircMemory,
			pollfd *fds, std::string buffer, int32 i)
{
	// Class for split the buffer
	Splinter splitCMD(buffer, &irc->GetClient(i), irc->GetClientList());

	std::string message(buffer);
	
	if (strcmp(splitCMD.GetMasterCommand().c_str(), "#memoryUsage") == 0)
	{
		log->INFO("%s", ircMemory->GetMemoryUsageStr().c_str());
		return;
	}

	// Handle the message based on its command
	if (splitCMD.GetMasterCommand().size() > 0)
	{
		// log->TRACE("Choose CMD: %s", words[0].c_str());
		
	// join a channel
		if (strncmp(splitCMD.GetMasterCommand().c_str(), JOIN, 4) == 0)
		{
			log->WARNING("Enter Join: %s", splitCMD.GetMasterCommand().c_str());
			JoinChannel(irc, ircMemory, &splitCMD);
		}
	// Mute PONG
		else if (strncmp(splitCMD.GetMasterCommand().c_str(), PONG, 4) == 0)
		{
			return ;
		}
	// Part a channel
		else if (strncmp(splitCMD.GetMasterCommand().c_str(), PART, 4) == 0)
		{
			log->WARNING("Enter Part: %s", splitCMD.GetMasterCommand().c_str());
			PartChannel(irc, log, ircMemory, splitCMD.GetSender(), splitCMD.GetWords());
		}
	// list channel dispo
		else if (strncmp(splitCMD.GetMasterCommand().c_str(), LIST, 4) == 0)
		{
			log->WARNING("Enter List: %s", splitCMD.GetMasterCommand().c_str());
			ListChannels(irc, log, &splitCMD);
		}
	// private messages
		else if (strncmp(splitCMD.GetMasterCommand().c_str(), PRIVMSG, 7) == 0)
		{
			if (splitCMD.GetWords().size() >= 3)
			{
				log->WARNING("Enter PRIVMSG: %s", splitCMD.GetMasterCommand().c_str());
				std::string channelName = splitCMD.GetWords().at(1);
				std::string messageContent = message.substr(message.find(splitCMD.GetWords().at(2)));
				messageContent.erase(messageContent.size() - 2, 2);
				log->DEBUG("Mess: %s Name: %s", messageContent.c_str(), channelName.c_str());

				// send to target client
				PrivmsgGestion(irc, log, splitCMD.GetSender(), channelName, messageContent, i);
			}
		}
	// Quit chat
		else if (strncmp(splitCMD.GetMasterCommand().c_str(), QUIT, 4) == 0)
		{
			QuitServer(irc, log, ircMemory, splitCMD.GetSender());
		}
	//Admin
		else if (strncmp(splitCMD.GetMasterCommand().c_str(), ADMIN, 5) == 0)
		{
			log->WARNING("Enter ADMIN: %s", splitCMD.GetMasterCommand().c_str());
			CheckAdminPassword(irc, log, i, &splitCMD);
		}
	//TOPIC
		else if (strncmp(splitCMD.GetMasterCommand().c_str(), TOPIC, 5) == 0)
		{
			log->WARNING("Enter TOPIC: %s", splitCMD.GetMasterCommand().c_str());
			
		}
	// ***** ADMIN COMMANDS *****
		else if(irc->GetIsAdmin(i) == 1)
		{
		// KICK USER
			if (strncmp(splitCMD.GetMasterCommand().c_str(), KICK, 4) == 0)
			{
				log->WARNING("Enter KICK: %s", splitCMD.GetMasterCommand().c_str());
				i = 1;
				while(strcmp(irc->GetClient(i).userName.c_str(), splitCMD.GetWords().at(2).c_str()) != 0 && i <= irc->GetClientConnected())
				{
//debug:		std::cout << "Haystack : " << irc->GetClient(i).userName.c_str() << "   Needle :" << splitCMD.GetWords().at(2).c_str() << std::endl;
					i++;
				}
				if (strcmp(irc->GetClient(i).userName.c_str(), splitCMD.GetWords().at(2).c_str()) == 0)
					KickUser(irc, log, ircMemory, &irc->GetClient(i), splitCMD.GetWords());
				else
				{
					irc->_channels.SendReply("001 ERROR Error: User " + splitCMD.GetWords().at(2) + " not found", log, splitCMD.GetSender()->fd->fd , 1);
					return;
				}
			}
		//INVITE
			else if (strncmp(splitCMD.GetMasterCommand().c_str(), INVITE, 6) == 0)
			{
				log->WARNING("Enter INVITE: %s", splitCMD.GetMasterCommand().c_str());
				InviteUser(irc, ircMemory, &splitCMD);
			}
		//MODE
			else if (strncmp(splitCMD.GetMasterCommand().c_str(), MODE, 4) == 0)
			{
				log->WARNING("Enter MODE: %s", splitCMD.GetMasterCommand().c_str());
				Mode(irc, log, ircMemory, fds, &splitCMD , i);
				
			}
		}
		// Skip ping respond from client
		else if (strncmp(splitCMD.GetMasterCommand().c_str(), PONG, 4) == 0)
		{
			return;
		}
		// For debugging
		else if (strncmp(splitCMD.GetMasterCommand().c_str(), "LEAKS", 5) == 0)
		{
			loop = false;
		}
		// Default
		else
		{
//debug:
			std::cout << "ENTER HERE" << std::endl;
			irc->_channels.SendReply("PRIVMSG " + splitCMD.GetSender()->userName + " :" + buffer, log, splitCMD.GetSender()->fd->fd, 0);
		}
	}
}

void	CheckClientsPassword(IrcCore *irc, Logger *log, IrcMemory *ircMemory,
			pollfd *fds, std::string buffer, int32 i)
{
	log->FATAL("Need pass: getNc: %d getAccess: %d", irc->GetNewlient(i) , irc->GetAccess(i));
	#ifdef IRC_PLATFORM_APPLE
		if (irc->GetNewlient(i) == true && irc->GetAccess(i) == false)
		{
			if (irc->CheckClientInfosMac(irc, log, i, buffer, fds[i].fd) == false)
			{
				log->ERROR("Password invalid");
				irc->_channels.SendReply("464 * :Password incorrect", log, fds[i].fd, 1);

				fds[i].events = 0;
				close(fds[i].fd);
				fds[i].fd = 0;
			}
			if (irc->GetAccess(i) == true)
			{
				// set access
				ircClient *cli = &irc->GetClient(i);
				irc->SetAccess(i, true);
				irc->SetEmptyFd(i, false);
				std::cout << "Nick: " << cli->nickName << " User: " << cli->userName << " Real_Name: " << cli->realName << std::endl;
			}

			ircClient newClient = irc->GetClient(i);
			log->ERROR("New Client NICK: %s", newClient.nickName.c_str());
			log->ERROR("New Client PASS: %s", newClient.password.c_str());
		}
	#endif
	#ifdef IRC_PLATFORM_LINUX
		if (irc->GetAccess(i) == false)
		{
			if (irc->CheckClientInfosLinux(irc, log, ircMemory, fds[i].fd, buffer) == false)
			{
				log->ERROR("Password invalid");
				fds[i].events = 0;
				close(fds[i].fd);
				fds[i].fd = 0;
			}
			else if (irc->GetAccess(i) == true)
			{
				std::string message = "001 " + irc->GetClientUsername(i) + " :Welcone to our irc server. "
					+ irc->GetClientUsername(i) + "@localHost.com";
				irc->_channels.SendReply(message, log, fds[i].fd, 1);
			}
			ircClient newClient = irc->GetClient(i);
			// Ct_mprintf((void *)newClient.userName.c_str(), newClient.userName.size(), 1, 'F');
			log->ERROR("New Client PASS: %s, NICK: %s", newClient.password.c_str(), newClient.userName.c_str());
		}
	#endif
}
