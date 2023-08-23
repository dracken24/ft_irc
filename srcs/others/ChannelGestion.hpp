/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelGestion.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayrand <smayrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:43:47 by dracken24         #+#    #+#             */
/*   Updated: 2023/08/23 13:20:06 by smayrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNELGESTION_HPP
# define CHANNELGESTION_HPP

// # include "../srcs/IrcCore.hpp"
# include "../includes/defines.hpp"

# include "Logger.hpp"
# include "../includes/structsUtility.hpp"

# include <string>
# include <vector>
# include <map>
# include <set>
# include <poll.h>

// typedef struct ircClient
// {
// 	bl8				admit;
// 	bl8				emptyFd;
// 	bl8				setUser;

// 	std::string		userName;
// 	std::string		nickName;
// 	std::string		password;
// 	std::string		channel;

// 	pollfd			*fd;
// }	ircClient;


// typedef struct channel_t
// {
// 	uint16 nbrMembers;
// 	std::string	channelName;
// 	std::string channelDescription;
// 	std::vector<ircClient *>	users;
// }	channel_t;

class ChannelGestion
{
	//**********************************************************************//
	//**                     Constructors / Destructor                    **//
	//**********************************************************************//
	public:
		ChannelGestion();
		~ChannelGestion();
	//**********************************************************************//
	//**                     		SETTERS    	     		              **//
	//**********************************************************************//

		bl8			AddClientToChannel(class IrcCore *irc, Logger *log, ircClient *client,
						std::string channel, bl8 flag, int32 PmFlag);
		bl8			RemoveClientToChannel(Logger *log, ircClient *client,
						std::string channel);
		void		SetChannel(std::string channel);
		void		SetTopic(std::string name, std::string topic);
		void		SetTopicRight(std::string name, bl8 right);
		void		SetMaxUser(std::string name, uint16 UsersMax);
		void		SetNewChannel(std::string channelName, std::string topic, std::string password);

	//**********************************************************************//
	//**                     		GETTERS    	     		              **//
	//**********************************************************************//

		std::string	GetChannel(std::string channel) const;
		std::string	GetChannelTopic(std::string name) const;
		int32		GetMembersInChannel(std::string name) const;
		channel_t	GetSpecificChannel(std::string name) const;
		bl8			GetChannelRight(std::string channelName);
		std::string GetChannelPassword(std::string channelName);
		
		std::map<std::string, struct channel_t >	GetAllChannelsInfos(void) const;
		std::vector<std::string> GetAllChannelsNames(void) const;
		bl8			AllreadyInThatChannel(std::string channel, int32 clientFd);

	//**********************************************************************//
	//**                          PUBLIC METHODS                          **//
	//**********************************************************************//

		void		ReadConfig(ChannelGestion &config, const std::string &filename);
		
		void		SendReply(const std::string& message, Logger *log, int32 clientFd, bl8 flag);
		void		SendPrivateReply(const std::string& message, Logger *log, int32 clientFd, std::string sender);

	//**********************************************************************//
	//**                          MEMBERS VARS	                          **//
	//**********************************************************************//
	private :
		std::map<std::string, struct channel_t > _channelMap;

};

#endif
