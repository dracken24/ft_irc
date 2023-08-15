/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcCore.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <nadesjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:12:35 by dracken24         #+#    #+#             */
/*   Updated: 2023/08/10 16:10:53 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCCORE_HPP
# define IRCCORE_HPP

# include "../../C_tools/C_tool.h"

# include "../others/Logger.hpp"
# include "../others/Splinter.hpp"
# include "../others/IrcMemory.hpp"

# include "../includes/defines.hpp"
# include "../others/ChannelGestion.hpp"
# include "../includes/structsUtility.hpp"

#include <string>
# include <sys/socket.h>
# include <netinet/in.h>
# include <sys/select.h>
# include <sys/types.h>
# include <arpa/inet.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h> // for close
# include <fcntl.h>
# include <netdb.h>
# include <sstream>
# include <time.h>
# include <poll.h>

# include <functional>
# include <stdexcept>
# include <iostream>
# include <cstring>
# include <vector>
# include <cstdio>
# include <map>
# include <set>

class ChannelGestion;  // forward declaration

// struct ChannelGestion;  // forward declaration

typedef struct IrcInfo
{
	std::string		mainPassword;
	std::string		adminPassword;
	int32			port;			// Connexion port == argv[1]

	int32			*serverSocket;
	int32			TotalClients;
	
	pollfd						*fds;
	std::vector<ircClient *>	clients;
}	IrcInfo;

class IrcCore
{
	//**********************************************************************//
	//**                     Constructors / Destructor                    **//
	//**********************************************************************//
	public:
		IrcCore(IrcMemory *ircMemory, Logger *log);
		~IrcCore(void);

	private:
		IrcCore(void);
		IrcCore(IrcCore const &copy);
		IrcCore &operator=(IrcCore const &copy);

	//**********************************************************************//
	//**                     		SETTERS    	     		              **//
	//**********************************************************************//
	public:
		void	SetPassword(std::string password);

		void	SetServerSocket(int32 *socket);
		void	SetPort(int32 port);
		void	SetEmptyFd(int32 client, bl8 fd);

		void	SetPoolfds(pollfd *fds);
		void	SetAccess(int32 clientNbr, bl8 access);
		void	SetSetUser(int32 clientNbr, bl8 access);
		void	SetClientUsername(int32 clientNbr, std::string userName);
		void	SetClientNickname(int32 clientNbr, std::string userName);
		void	SetClientRealname(int32 clientNbr, std::string nickName);

		void	SetNewlient(ircClient *client, Logger *log, pollfd *fds,
					int32 clientNbr, bl8 access);
		void	SetClientFd(int32 client, int32 fd);
		void	SetAdminRights(int32 clientNbr, int32 admin);
		void	SetPrivateClient(ircClient *sender, Logger *log, ircClient *client, std::string messageContent);
		bool	SetPivateChannel(IrcCore *irc, ircClient *sender, Logger *log, std::string nickName, Splinter *splitCMD, std::string messageContent);

	//**********************************************************************//
	//**                     		GETTERS    	     		              **//
	//**********************************************************************//

		std::string	GetPassword(void) const;
		std::string	GetAdminPassword(void) const;

		int32		GetIsAdmin(int32 place) const;
		int32		*GetServerSocket(void) const;
		int32		GetPort(void) const;
		bl8			GetAccess(int32 place) const;
		bl8			GetNewlient(int32 place) const;
		bl8			GetSetUser(int32 place) const;
		int32		GetClientFd(std::string userName);
		int32		GetClientNb(std::string userName);
		int32		GetClientConnected();
		std::vector<ircClient>	GetClientList(void);
		std::map<std::string, struct channel_t >	GetAllChannelsInfos(void) const;

		pollfd		*GetPoolfds(void) const;
		std::string	GetClientUsername(int32 place) const;

		ircClient	&GetClient(int32 clientNbr) const;
		ircClient	*GetClientP(int32 clientNbr) const;
		std::string	GetClientChannelName(int32 clientFd) const;
		std::string	GetClientUserNameFD(int32 clientFd) const;
		bl8			GetChannelExist(std::string channel) const;
		int32		GetMemebersInChannel(std::string name) const;
		channel_t	GetSpecificChannel(std::string name) const;
		std::string	GetNickname(int32 place) const;

	//**********************************************************************//
	//**                          PUBLIC METHODS                          **//
	//**********************************************************************//

		// void		InitCore(class IrcMemory *ircMemory, class Logger *log);
		void		FreeCore(class IrcMemory *ircMemory);
		
		bl8			CheckClientInfosLinux(IrcCore *irc, Logger *log, IrcMemory *ircMemory,
						int place, std::string info);
		bl8			CheckClientInfosMac(IrcCore *irc, Logger *log,
						int place, std::string info, int fd);
		
		bl8			DeleteClient(IrcMemory *ircMemory, std::string clientName);
		bl8			DeleteAllClient(IrcMemory *ircMemory);
	
	private:
		void		HandleNewConnection(int socket);

	//**********************************************************************//
	//**                          MEMBERS VARS	                          **//
	//**********************************************************************//
	public:
		ChannelGestion	_channels;
	private:
		IrcInfo			_ircInfo;
};

// LINK: Init.cpp
void		FindFirstUsableAddress(IrcCore	*irc, Logger *log,
				addrinfo *serverInfo, addrinfo *p);
void		BuildServerInfo(IrcCore	*irc, Logger *log, std::string port);
void    	CheckEntry(IrcCore *irc, Logger *log, int argc, char **argv);
void		SetQueueSocketAndClient(IrcCore	*irc, Logger *log);

// LINK: MainLoop.cpp
void		MainLoop(IrcCore *irc, Logger *log, IrcMemory *ircMemory);
void		CheckClientsPassword(IrcCore *irc, Logger *log, IrcMemory *ircMemory,
				pollfd *fds, std::string buffer, int32 i);
void		CheckIfNewConnexion(IrcCore *irc, Logger *log, IrcMemory *ircMemory,
				pollfd *fds, int32 *serverSocket);
void		ChooseCommand(IrcCore *irc, Logger *log, IrcMemory *ircMemory,
				pollfd *fds, std::string buffer, int32 i);
void		ReceveAndSplitMessages(IrcCore *irc, Logger *log, IrcMemory *ircMemory, pollfd *fds);
void    	PrivmsgGestion(IrcCore *irc, Logger *log, ircClient *senderClient,
				std::string channelName, std::string message, int32 i);

// LINK: Utils.cpp
void		Ftoa(float nbr, char *destination, int afterpoint);
std::string	Itoa(int value);
std::string Gethannel(std::string channel);
bool		IsDigit(std::string str);
int			IsAscii(std::string str);

// LINK: join.cpp
// void		JoinChannel(IrcCore *irc, Logger *log, IrcMemory *ircMemory, pollfd *fds,
// 				ircClient *client, std::vector<std::string> words, s_t i);
void		JoinChannel(IrcCore *irc, IrcMemory *ircMemory, Splinter *splitCMD);
void		ListChannels(IrcCore *irc, Logger *log, Splinter *splitCMD);
void		CheckIfChannelExist(IrcCore *irc, Logger *log, std::string channelName, ircClient *client);

// LINK: invite.cpp
void		InviteUser(IrcCore *irc, IrcMemory *ircMemory, Splinter *splitCMD);

// LINK: part.cpp
void		PartChannel(IrcCore *irc, Logger *log, IrcMemory *ircMemory, ircClient *client,
			std::vector<std::string> words);

// LINK: kick.cpp
void		KickUser(IrcCore *irc, Logger *log, IrcMemory *ircMemory, ircClient *client,
			std::vector<std::string> words);

// LINK: quitServer.cpp
void		QuitServer(IrcCore *irc, Logger *log, IrcMemory *ircMemory, ircClient *client);

// LINK: admin.cpp
void		CheckAdminPassword(IrcCore *irc, Logger *log, int32 i, Splinter *splitCMD);
// LINK: mode.cpp
void 		Mode(IrcCore *irc, Logger *log, IrcMemory *ircMemory, pollfd *fds, Splinter *splitCMD, int32 i);
#endif
