/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privateMessages.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <nadesjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:26:11 by dracken24         #+#    #+#             */
/*   Updated: 2023/08/24 01:50:53 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/IrcCore.hpp"

// TODO: link privmsg together (pourrait marcher en créant un channel privé qui utiliserait
//	 les deux users dans le meme send reply et envoyer le dernier sendReply dans AddClienttoChannel)
// 		test à venir... 
void    PrivmsgGestion(IrcCore *irc, Logger *log, ircClient *senderClient,
			std::string channelName, std::string message, int32 i)
{
	// send to all channel members
	std::cout << "Channel name in PrivmsgGestion: " << channelName << std::endl;
	if (!irc->GetChannelExist(channelName))
	{
		return;
	}
	if (channelName.find("#") == 0)
	{
		channelName.erase(0, 1);
		channel_t channel = irc->GetSpecificChannel(channelName);
		if (channel.users.size() <= 0)
		{
			return;
		}
		for (s_t j = 0; j < channel.users.size(); j++)
		{
			if (channel.users.at(j) == senderClient || irc->_channels.AllreadyInThatChannel(channelName, senderClient->fd->fd) == false)
			{
				continue;
			}
			irc->_channels.SendReply(":" + senderClient->nickName + "!~" + senderClient->nickName 
				+ "@Localhost PRIVMSG #" + channelName + " " + message, log, channel.users.at(j)->fd->fd, 0);
		}
	}
	// send to a specific user
	else
	{
		log->ERROR("private channelName: %s", channelName.c_str());
		int32 targetfd = irc->GetClientFd(channelName);
		log->ERROR("private targetfd: %d", targetfd);
		std::string targetMessage = "PRIVMSG " + senderClient->userName + " :" + senderClient->userName + " : " + message;
		std::string VoidMessage = "PRIVMSG " + channelName + " :" + message;
//debug:
std::cout << "target fd : " << targetfd << " :: " << irc->GetClient(irc->GetClientNb(channelName)).userName << " ::  Sender : " << senderClient->userName << std::endl;
		irc->_channels.SendReply(targetMessage, log, targetfd, 0);
//		irc->_channels.SendReply(VoidMessage, log, senderClient->fd->fd, 0);
//		irc->_channels.SendPrivateReply(targetMessage, log, targetfd, senderClient->userName);
//		irc->_channels.AddClientToChannel(irc, log, &irc->GetClient(irc->GetClientNb(channelName)), senderClient->userName , false, 1);
	}
}
