/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcCore.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayrand <smayrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:21:34 by dracken24         #+#    #+#             */
/*   Updated: 2023/08/14 14:16:47 by smayrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcCore.hpp"

//**********************************************************************//
//**                     Constructors / Destructor                    **//
//**********************************************************************//

IrcCore::IrcCore(void)
{

}

IrcCore::IrcCore(IrcMemory *ircMemory, Logger *log)
{
	_ircInfo.fds = (pollfd *)ircMemory->Mallocate(sizeof(pollfd) * (MAX_CLIENTS), IRC_MEMORY_TAG_SERVER, log);

	ircClient	*client = (ircClient *)ircMemory->Mallocate(sizeof(ircClient), IRC_MEMORY_TAG_CLIENTS, log);
	client->admit = false;
	client->setUser = false;
	client->emptyFd = false;
	client->fd = &_ircInfo.fds[0];

	_ircInfo.clients.push_back(client);

	_channels.ReadConfig(_channels, "Config.INI");
	_ircInfo.TotalClients = 0;
	_ircInfo.adminPassword = "qwertyqaz";
}

IrcCore::~IrcCore(void)
{

}

IrcCore::IrcCore(IrcCore const &copy)
{
	if (this != &copy)
	{
		*this = copy;
	}
}

IrcCore	&IrcCore::operator=(IrcCore const &copy)
{
	if (this != &copy)
	{
		_ircInfo.port = copy._ircInfo.port;
		_ircInfo.mainPassword = copy._ircInfo.mainPassword;
		_ircInfo.serverSocket = copy._ircInfo.serverSocket;
	}

	return *this;
}

//**********************************************************************//
//**                     		SETTERS    	     		              **//
//**********************************************************************//
void	IrcCore::SetPassword(std::string password)
{
	_ircInfo.mainPassword = password;
}

void	IrcCore::SetServerSocket(int32 *socket)
{
	_ircInfo.serverSocket = socket;
}

void	IrcCore::SetPort(int port)
{
	_ircInfo.port = port;
}

void	IrcCore::SetEmptyFd(int32 client, bl8 fd)
{
	_ircInfo.clients.at(client)->emptyFd = fd;
}

void 	IrcCore::SetPoolfds(pollfd *fds)
{
	for (int i = 0; i < MAX_CLIENTS + 2; i++)
		_ircInfo.fds[i] = fds[i];
}

void	IrcCore::SetAccess(int32 clientNbr, bl8 access)
{
	_ircInfo.clients.at(clientNbr)->admit = access;
}

void	IrcCore::SetNewlient(ircClient *client, Logger *log, pollfd *fds,
			int32 clientNbr, bl8 access)
{
	client->admit = false;
	client->setUser = false;

	client->emptyFd = access;
	client->fd = &fds[clientNbr];
	
	_ircInfo.clients.push_back(client);
}

void	IrcCore::SetClientFd(int32 client, int32 fd)
{
	_ircInfo.clients.at(client)->fd->fd = fd;
}

void	IrcCore::SetSetUser(int32 clientNbr, bl8 access)
{
	_ircInfo.clients.at(clientNbr)->setUser = access;
}

void	IrcCore::SetClientUsername(int32 clientNbr, std::string userName)
{
	_ircInfo.clients.at(clientNbr)->userName = userName;
}

void	IrcCore::SetClientNickname(int32 clientNbr, std::string nickName)
{
	_ircInfo.clients.at(clientNbr)->nickName = nickName;
}

void	IrcCore::SetClientRealname(int32 clientNbr, std::string realName)
{
	_ircInfo.clients.at(clientNbr)->realName = realName;
}

void	IrcCore::SetAdminRights(int32 clientNbr, int32 admin)
{
	_ircInfo.clients.at(clientNbr)->isAdmin = admin;
}

//void	IrcCore::SetOperatorRights(int32 clientNbr, int32 admin)
//{
//	_ircInfo.clients.at(clientNbr)->isAdmin = admin;
//}

//**********************************************************************//
//**                     		GETTERS    	     		              **//
//**********************************************************************//

std::string	IrcCore::GetPassword(void) const
{
	return _ircInfo.mainPassword;
}

std::string	IrcCore::GetAdminPassword(void) const
{
	return _ircInfo.adminPassword;
}

int32		IrcCore::GetIsAdmin(int32 place) const
{
	return _ircInfo.clients.at(place)->isAdmin;
}

int32		*IrcCore::GetServerSocket(void) const
{
	return _ircInfo.serverSocket;
}

int32		IrcCore::GetPort(void) const
{
	return _ircInfo.port;
}

pollfd	*IrcCore::GetPoolfds(void) const
{
	return (pollfd *)_ircInfo.fds;
}

ircClient	&IrcCore::GetClient(int32 clientNbr) const
{
	return *_ircInfo.clients.at(clientNbr);
}

bl8			IrcCore::GetAccess(int32 place) const
{
	return _ircInfo.clients.at(place)->admit;
}

bl8			IrcCore::GetNewlient(int32 place) const
{
	return _ircInfo.clients.at(place)->emptyFd;
}

bl8			IrcCore::GetChannelExist(std::string channel) const
{
	if (_channels.GetChannel(channel) == "Channel not found")
	{
		return false;
	}
	
	return true;
}

std::map<std::string, struct channel_t >	IrcCore::GetAllChannelsInfos(void) const
{
	return _channels.GetAllChannelsInfos();
}

std::string IrcCore::GetClientUsername(int32 place) const
{
	return _ircInfo.clients.at(place)->userName;
}

std::string	IrcCore::GetClientChannelName(int32 clientFd) const
{
	for (s_t i = 0; i < _ircInfo.clients.size(); i++)
	{
		if (clientFd == _ircInfo.clients.at(i)->fd->fd)
		{
			return _ircInfo.clients.at(i)->channel;
		}
	}

	return 0;
}

std::string	IrcCore::GetClientUserNameFD(int32 clientFd) const
{
	for (s_t i = 0; i < _ircInfo.clients.size(); i++)
	{
		if (clientFd == _ircInfo.clients.at(i)->fd->fd)
		{
			return _ircInfo.clients.at(i)->userName;
		}
	}

	return 0;
}

bl8			IrcCore::GetSetUser(int32 place) const
{
	return _ircInfo.clients.at(place)->setUser;
}

int32		IrcCore::GetMemebersInChannel(std::string name) const
{
	return _channels.GetMemebersInChannel(name);
}

int32		IrcCore::GetClientFd(std::string userName)
{
	std::cout << "client fd username in: " << userName << std::endl;
	for (s_t i = 0; i < _ircInfo.clients.size(); i++)
	{
		std::cout << "name: " << _ircInfo.clients.at(i)->userName << "client #"
			<< i << " fd #" << _ircInfo.clients.at(i)->fd->fd << std::endl;
		if (userName == _ircInfo.clients.at(i)->userName)
		{
			std::cout << "\nReturn good client fd" << std::endl;
			return _ircInfo.clients.at(i)->fd->fd;
		}
	}
	std::cout << "\nReturn BAD client fd" << std::endl;
	return 0;
}

int32		IrcCore::GetClientNb(std::string userName)
{
	for (s_t i = 0; i < _ircInfo.clients.size(); i++)
	{
		if (userName == _ircInfo.clients.at(i)->userName)
		{
			std::cout << _ircInfo.clients.at(i)->userName <<"'s client number is #" << i << std::endl;
			return i;
		}
	}
	std::cout << "\nClient number not found." << std::endl;
	return 0;
}

int32		IrcCore::GetClientConnected()
{
	for (unsigned long i = 1; i < _ircInfo.clients.size(); i++)
	{
		_ircInfo.TotalClients = i - 1;
//		std::cout << "TOTAL CLIENT DEBUG : " << _ircInfo.TotalClients << std::endl;
	}
	return _ircInfo.TotalClients;
}

channel_t	IrcCore::GetSpecificChannel(std::string name) const
{
	return _channels.GetSpecificChannel(name);
}

std::vector<ircClient>	IrcCore::GetClientList(void)
{
	std::vector<ircClient> ret;
	for (s_t i = 1; i < _ircInfo.clients.size(); i++)
	{
		ret.push_back(*_ircInfo.clients.at(i));
	}

	return ret;
}

std::string	IrcCore::GetNickname(int32 place) const
{
	return _ircInfo.clients.at(place)->nickName;
}

//**********************************************************************//
//**                          PUBLIC METHODS                          **//
//**********************************************************************//

void		IrcCore::FreeCore(class IrcMemory *ircMemory)
{
	std::vector<ircClient *>::iterator it = _ircInfo.clients.begin();
	for (int i = 0; it != _ircInfo.clients.end(); it++)
	{
		ircClient *client = _ircInfo.clients.at(i++);
		ircMemory->FreeMem(client, sizeof(ircClient), IRC_MEMORY_TAG_CLIENTS);
	}

	delete []_ircInfo.fds;

	// ircMemory->FreeMem(_ircInfo.fds, sizeof(pollfd) * (MAX_CLIENTS * 2), IRC_MEMORY_TAG_SERVER);
}

// Check if client have aothorisation to connect to out irc serv.
bl8			IrcCore::CheckClientInfosLinux(IrcCore *irc, Logger *log, IrcMemory *ircMemory,
				int32 clientFd, std::string info)
{
	log->WARNING("Buffer Linux: %s len: %d", info.c_str(), info.length());
	if (info.size() < 1)
	{
		log->ERROR("Error, no infos for client connexion linux.");
		return false;
	}

	// if buffer send by client don't have nickname, return false
	char digit[555];
	Ftoa((float)info.find("NICK"), digit, 0);
	if (IsDigit(digit) == false)
	{
		log->ERROR("No nickname send by the client;");
		return false;
	}

	s_t place = 0;
	for (; place < _ircInfo.clients.size(); place++)
	{
		if (_ircInfo.clients.at(place)->fd->fd == clientFd)
			break;
	}

	ircClient *client = _ircInfo.clients.at(place);

	char tmp[32];
	std::memset(tmp, 0, sizeof(tmp));
	size_t ii;

	// Save password client
	ii = info.find("PASS ");
	info.copy(tmp, _ircInfo.mainPassword.length(), ii + 5);
	client->password = tmp;

	log->ERROR("tmp: %s ii: %d passlen: %d", tmp, ii, _ircInfo.mainPassword.length());

	// Save nickname client
	info.copy(tmp ,ii + 10, info.find('\n', ii + 5));
	for (ii = 1; tmp[ii] && tmp[ii] != '\n'; ii++)
	;
	tmp[ii - 1] = '\0';
	// log->WARNING("DEBUG 1 place: %d", place);
	
	client->userName = (tmp + 6);
	
	if (client->password == _ircInfo.mainPassword)
	{
		// log->WARNING("DEBUG 2");
		HandleNewConnection(irc->GetClient(place).fd->fd);
		_ircInfo.TotalClients++;
		client->admit = true;
		_ircInfo.clients.at(place) = client;
		
		return true;
	}

	client->password.clear();
	client->userName.clear();
	
	return false;
}

void	IrcCore::HandleNewConnection(int socket)
{
	// Envoyer le message de bienvenue
	std::string welcomeMessage = "Welcome to MyIRCServer!";
	send(socket, welcomeMessage.c_str(), welcomeMessage.length(), 0);

	// Envoyer la liste des canaux disponibles
	std::string channelListMessage = "Available channels:";

	std::vector<std::string> tmpChannels;
	tmpChannels.push_back("general");
	for (size_t i = 0; i < tmpChannels.size(); i++)
	{
		channelListMessage += " " + tmpChannels.at(i);
	}
	send(socket, channelListMessage.c_str(), channelListMessage.length(), 0);

	// Envoyer les modes d'utilisation
	std::string usageMessage = "To join a channel, type /join <channel>";
	send(socket, usageMessage.c_str(), usageMessage.length(), 0);

	// Continuer le traitement de la nouvelle connexion...
}

// Check if client have aothorisation to connect to out irc serv.
bl8			IrcCore::CheckClientInfosMac(IrcCore *irc, Logger *log,
						int place, std::string info, int fd)
{
	log->TRACE("Buffer Mac: %s", info.c_str());

	char tmp[32];
	int32 pt;
	std::memset(tmp, 0, sizeof(tmp));
	size_t ii;

	if (info.find("PASS ") == 0)
	{
		// find server password
		s_t len = info.find('\r');
		info[len] = '\0';
		info.erase(0, 5);

		_ircInfo.clients[place]->password = info;
		_ircInfo.clients[place]->nickName = "";

		return true;
	}
	else if (info.find("NICK ") == 0)
	{
		// find nickname
		s_t len = info.find('\r');
		info.erase(len);
		info.erase(0, 5);
		log->WARNING("Nick: %s", info.c_str());
		_ircInfo.clients[place]->nickName = info;
		irc->SetClientNickname(place, info);

		return true;
	}
	else if (info.find("USER ") == 0)
	{
		// find username
		std::string tmp = info;
		info.erase(0, 5);
		info.erase(info.find(' '), info.size());
		log->FATAL("USER: %s", info.c_str());
		s_t len = info.find('\r'); 
		irc->SetClientUsername(place, info);

		// find realname
		int32 star = tmp.find("*");
		tmp.erase(0, star + 2);
		star = tmp.find("\r");
		tmp.erase(star, 2);
		irc->SetClientRealname(place, tmp);
		// std::cout << "NAME: " << tmp << std::endl;

		// return true;
		if (strncmp(_ircInfo.mainPassword.c_str(), _ircInfo.clients[place]->password.c_str(), _ircInfo.clients[place]->password.length()) == 0)
		{
			_ircInfo.clients[place]->admit = true;
			_ircInfo.clients[place]->emptyFd = false;
			irc->SetAccess(place, true);
			
			log->FATAL("ADMIT");
			HandleNewConnection(fd);

			// Send welcome message to new user
			irc->_channels.SendReply("001 ", log, fd, 1);

			irc->_channels.SendReply("001 " + info + " :Welcome to NS irc server. your username is "
				+ _ircInfo.clients[place]->nickName, log, fd, 1);

			return true;
		}
	}

	log->WARNING("Bad Pass, clear infos2");
	_ircInfo.clients[place]->password.clear();
	_ircInfo.clients[place]->nickName.clear();
	_ircInfo.clients[place]->admit = false;
	_ircInfo.clients[place]->emptyFd = false;

	return false;
}

bl8		IrcCore::DeleteClient(IrcMemory *ircMemory, std::string clientName)
{
	std::cout << "delete cli" << std::endl;
	std::vector<ircClient *>::iterator it = _ircInfo.clients.begin();
	for (; it != _ircInfo.clients.end(); it++)
	{
		ircClient *cli = *it;
		if (clientName == cli->nickName)
		{
			std::cout << "client delete" << std::endl;
			// ircMemory->FreeMem(cli, sizeof(ircClient) * 1, IRC_MEMORY_TAG_CLIENTS);
			// _ircInfo.clients.erase(it);
			return true;
		}
	}
	std::cout << "client not found for delete" << std::endl;
	return false;
}

bl8		IrcCore::DeleteAllClient(IrcMemory *ircMemory)
{
	std::cout << "delete All clients: " << _ircInfo.TotalClients << std::endl;


	std::vector<ircClient *>::iterator it = _ircInfo.clients.begin();
	for (; it != _ircInfo.clients.end(); it++)
	{
		ircClient *cli = *it;

		std::cout << "client delete" << std::endl;

		//ircMemory->FreeMem(cli->fd, sizeof(pollfd), IRC_MEMORY_TAG_SERVER);
		ircMemory->FreeMem(cli, sizeof(ircClient), IRC_MEMORY_TAG_CLIENTS);
			// _ircInfo.clients.erase(it);
	}
	// delete []_ircInfo.fds;
	ircMemory->FreeMem(_ircInfo.fds, sizeof(pollfd) * (MAX_CLIENTS * 2), IRC_MEMORY_TAG_SERVER);
	return false;
}
