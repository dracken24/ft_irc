/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelGestion.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayrand <smayrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:43:36 by dracken24         #+#    #+#             */
/*   Updated: 2023/08/23 17:28:50 by smayrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/defines.hpp"
# include "../srcs/IrcCore.hpp"
#include "ChannelGestion.hpp"

#include <cstddef>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>

void Ct_mprintf(void *ptr, size_t size, int type, int name);

ChannelGestion::ChannelGestion()
{
	
}

ChannelGestion::~ChannelGestion()
{
	
}

//**********************************************************************//
//**                     		SETTERS    	     		              **//
//**********************************************************************//

void		ChannelGestion::SetChannel(std::string channel)
{
	std::pair<std::string, struct channel_t > map;
	map.first = channel;
	map.second._topicFlag = false;
	map.second.maxUsers = 10;

	_channelMap.insert(map);
}

void		ChannelGestion::SetChannelPassword(std::string channel, std::string pass)
{
	std::pair<std::string, struct channel_t > map;
	map.first = channel;
	map.second.password = pass;

	_channelMap.insert(map);
}

void		ChannelGestion::SetTopic(std::string name, std::string topic)
{
	channel_t channel = GetSpecificChannel(name);
	channel.channelTopic = topic;
	
	_channelMap.at(name) = channel;
}

void		ChannelGestion::SetTopicRight(std::string name, bl8 right)
{
	channel_t channel = GetSpecificChannel(name);
	channel._topicFlag = right;
	
	_channelMap.at(name) = channel;
}

void		ChannelGestion::SetMaxUser(std::string name, uint16 UsersMax)
{
	channel_t channel = GetSpecificChannel(name);
	channel.maxUsers = UsersMax;
	
	_channelMap.at(name) = channel;
}

void		ChannelGestion::SendReply(const std::string& message, Logger *log, int32 clientFd, bl8 flag)
{
	std::string fullMessage = "";
	if (flag == 0) // Without server name
	{
		fullMessage = message + "\r\n";
	}
	else if (flag == 1) // With server name
	{
		fullMessage = ":ft_irc " + message + "\r\n";
	}

//debug
std::cout << "FM : " << fullMessage << std::endl;
	int32 numBytesSent = send(clientFd, fullMessage.c_str(), fullMessage.size(), 0);
	if (numBytesSent == -1)
	{
		log->ERROR("Error while sending data to client");
	}
	log->WARNING("%s", fullMessage.c_str());
	// Ct_mprintf((void *)fullMessage.c_str(), std::strlen(fullMessage.c_str()), 1, 'B');
}

void		ChannelGestion::SendPrivateReply(const std::string& message, Logger *log, int32 clientFd, std::string sender)
{
	std::string fullMessage = "";
	fullMessage = sender + ": " + message + "\r\n";
//debug
std::cout << "FM : " << fullMessage << std::endl;
	int32 numBytesSent = send(clientFd, fullMessage.c_str(), fullMessage.size(), 0);
	if (numBytesSent == -1)
	{
		log->ERROR("Error while sending data to client");
	}
	log->WARNING("%s", fullMessage.c_str());
	// Ct_mprintf((void *)fullMessage.c_str(), std::strlen(fullMessage.c_str()), 1, 'B');
}

bl8			ChannelGestion::AddClientToChannel(IrcCore *irc, Logger *log, ircClient *client,
				std::string channel, bl8 flag, int32 PmFlag)
{
	std::string removeChannel = client->channel;
	std::map<std::string, struct channel_t >::iterator find;
	if(PmFlag == 0)
		find = _channelMap.find(channel);
	if (PmFlag == 1 || channel == find->first )
	{
		log->TRACE("Find Channel: %s", channel.c_str());
		client->channel = channel;
		if(PmFlag == 0)
		{
			irc->_channels._channelMap.at(channel).users.push_back(client);
			irc->_channels._channelMap.at(channel).nbrMembers++;
			SendReply(":" + client->nickName + "!~"+ client->nickName + "@Localhost.com JOIN #" + channel, log, client->fd->fd, 0);
		}
		else
			SendReply(":" + client->nickName + "!~"+ client->nickName + "@Localhost.com JOIN " + channel, log, client->fd->fd, 0);
//		SendReply("332 " + client->nickName + " #" + channel + " :Welcome to the general discussion channel!", log, client->fd->fd, 1);
		
		std::string usersList;
		if(PmFlag == 0)
		{
			for (s_t i = 0; i < _channelMap.at(channel).users.size(); i++)
			{
				usersList += _channelMap.at(channel).users.at(i)->nickName;
				std::cout << _channelMap.at(channel).users.at(i)->nickName << std::endl;
			}
		}
		SendReply("353 " + client->nickName + " #" + channel + " :" + usersList, log, client->fd->fd, 1);
std::cout << "channel : "<< usersList.c_str() << std::endl;
	}
	else
	{
		log->INFO("Channel NOT FOUND: #%s", channel.c_str());
		return false;
	}

	return true;
}

bl8			ChannelGestion::RemoveClientToChannel(Logger *log, ircClient *client,
				std::string channel)
{
	std::map<std::string, struct channel_t>::iterator find;
	find = _channelMap.find(channel);
	
	std::vector<ircClient *>::const_iterator it = find->second.users.begin();
	for (; it != find->second.users.end(); it++)
	{
		ircClient *cli = *it;
		if (cli->nickName == client->nickName)
		{
			std::cout << "Erase: " << cli->userName << std::endl;

			_channelMap.at(channel).users.erase(it);
			client->channel = "";
			_channelMap.at(channel).nbrMembers--;
			return true;
		}
	}

	return false;
}

//**********************************************************************//
//**                     		GETTERS    	     		              **//
//**********************************************************************//

std::map<std::string, channel_t >	ChannelGestion::GetAllChannelsInfos(void) const
{
	return _channelMap;
}

std::string		ChannelGestion::GetChannelTopic(std::string name) const
{
	std::map<std::string, struct channel_t>::const_iterator it = _channelMap.begin();
	for (; it != _channelMap.end(); it++)
	{
		if (it->first == name)
		{
			return it->second.channelTopic;
		}
	}
	
	return "Error: Topic not found";
}

int32		ChannelGestion::GetMembersInChannel(std::string name) const
{
	std::map<std::string, struct channel_t >::const_iterator it = _channelMap.begin();
	for (; it != _channelMap.end(); it++)
	{
		if (it->first == name)
		{
			return it->second.nbrMembers;
		}
	}
	
	return -1;
}

channel_t	ChannelGestion::GetSpecificChannel(std::string name) const
{
	return _channelMap.at(name);
}

std::vector<std::string>			ChannelGestion::GetAllChannelsNames(void) const
{
	std::vector<std::string> ret;

	std::map<std::string, struct channel_t>::const_iterator pair = _channelMap.begin();
	for (; pair != _channelMap.end(); pair++)
	{
		ret.push_back(pair->first);
	}

	return ret;
}

std::string	ChannelGestion::GetChannel(std::string channel) const
{
	std::map<std::string, struct channel_t>::const_iterator it = _channelMap.begin();
	for (; it != _channelMap.end(); it++)
	{
		if (it->first == channel)
			return it->first;
	}

	return "Channel not found";
}

bl8		ChannelGestion::AllreadyInThatChannel(std::string channel, int32 clientFd)
{
	std::map<std::string, struct channel_t>::const_iterator it = _channelMap.begin();

	for (; it != _channelMap.end(); it++)
	{
		if (it->first == channel)
		{
			for (s_t i = 0; i < it->second.users.size(); i++)
			{
				if (it->second.users.at(i)->fd->fd == clientFd)
				{
					return true;
				}
			}
		}
	}

	return false;
}

bl8			ChannelGestion::GetChannelRight(std::string channelName)
{
	std::map<std::string, struct channel_t >::const_iterator it = _channelMap.begin();
	for (; it != _channelMap.end(); it++)
	{
		if (it->first == channelName)
		{
			return it->second.didHavePassword;
		}
	}
	return false;
}

std::string ChannelGestion::GetChannelPassword(std::string channelName)
{
	std::map<std::string, struct channel_t >::const_iterator it = _channelMap.begin();
	for (; it != _channelMap.end(); it++)
	{
		if (it->first == channelName)
		{
			return it->second.password;
		}
	}
	return "No password found";
}

//**********************************************************************//
//**                          PUBLIC METHODS                          **//
//**********************************************************************//

void	ChannelGestion::ReadConfig(ChannelGestion &config, const std::string &filename)
{
	FILE *file = fopen(filename.c_str(), "r");
	if (file == nullptr)
	{
		throw std::runtime_error("Unable to open configuration file " + filename);
	}

	char line[1024];
	std::string sectionName;
	while (std::fgets(line, sizeof(line), file))
	{
		// Skip empty lines and comments
		if (line == nullptr || line[0] == ';')
		{
			continue;
		}

		std::string tmp = line;
		// Check if line is a section
		if (tmp[0] == '[' && tmp[tmp.length() - 2] == ']')
		{
			sectionName = tmp.substr(1, tmp.length() - 3);
			continue;
		}

		// Parse parameter name and value
		std::istringstream iss(line);
		std::string paramName, paramValue;
		std::getline(std::getline(iss, paramName, '='), paramValue);

		// Set the value of the parameter in the config object
		if (sectionName == "Server")
		{
			if (paramName == "Name")
			{
				// std::pair<std::string, struct channel_t> map;
				// map.first = paramValue;

				// _channelMap.insert(map);
			}
			else if (paramName == "DefaultChannel" || paramName == "SupportChannel"
				|| paramName == "RandomChannel")
			{
				std::pair<std::string, struct channel_t> map;
				char info[512];
				std::memset(info, 0, sizeof(info));
				paramValue.erase(0, 1);
				int32 nbr = paramValue.find(" ");
				paramValue.copy(info, paramValue.size() - nbr, nbr + 1);
				paramValue.erase(nbr,paramValue.size());

				// std::cout << "param: " << paramValue << std::endl;

				map.first = paramValue;
				map.second.nbrMembers = 0;
				map.second.channelName = paramValue;
				map.second.channelTopic = info;
				map.second.maxUsers = 10;
				map.second.didHavePassword = false;
				// std::cout << paramValue << std::endl;

				_channelMap.insert(map);
			}
		}
	}

	std::map<std::string, struct channel_t>::const_iterator it = _channelMap.begin();
	for (; it != _channelMap.end(); it++)
		std::cout << "Channels name: " << it->first << std::endl;

	pclose(file);
}

void		ChannelGestion::SetNewChannel(std::string channelName, std::string topic, std::string password)
{
	std::cout << "IN SetNewChannel" << std::endl;
	if (channelName.at(0) == '#')
	{
		channelName.erase(0, 1);
	}

	std::string channelExist = GetChannel(channelName);
	if (channelExist != "Channel not found")
	{
		std::cout << "-- Channel Exist --\n";
		return;
	}

	// std::cout << "param: " << paramValue << std::endl;

	std::pair<std::string, struct channel_t> map;
	map.first = channelName;
	map.second.nbrMembers = 0;
	map.second.channelName = channelName;
	map.second.channelTopic = topic;
	map.second.maxUsers = 10;
	if (password.size() == 0)
	{
		map.second.didHavePassword = true;
		map.second.password = password;
	}
	else
	{
		map.second.didHavePassword = false;
	}
	std::cout << "channelName: " << channelName << " password: " << password << "topic: " << topic << std::endl;

	_channelMap.insert(map);
}
