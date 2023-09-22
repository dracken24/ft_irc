/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayrand <smayrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:18:13 by nadesjar          #+#    #+#             */
/*   Updated: 2023/09/22 13:26:11 by smayrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/IrcCore.hpp"

//*********************************** KICK ***********************************//

void	KickUser(IrcCore *irc, Logger *log, IrcMemory *ircMemory, ircClient *client,
			std::vector<std::string> words)
{
	int32 targetfd = irc->GetClientFd(words[2]);
	log->WARNING("KICK(): %s", words.at(1).c_str());

	if (words.size() == 1)
	{
		log->ERROR("Username missing");
		irc->_channels.SendReply("403 " + client->userName
			+ "@localHost.com #User not found", log, targetfd, 1);
		return;
	}
	std::string channelName = words.at(1);
	if (words.size() >= 2)
	{
		channelName.erase(channelName.begin());
		log->WARNING("KICK() channelName1: %s", channelName.c_str());
		if (channelName.at(0) == '#' && words.size() == 3)
		{
			channelName = words.at(2);
			// channelName.erase(0, 1);
		}
		log->WARNING("KICK() channelName2: %s", channelName.c_str());
		// if channel don't exist
		if (irc->GetChannelExist(channelName) == false)
		{
			irc->_channels.SendReply("403 " + client->userName +
				channelName + " : Channel not found", log, targetfd, 1);

			return;
		}

		// Check if the client is already in the channel
		if (irc->_channels.AllreadyInThatChannel(channelName, targetfd) == true)
		{
			irc->_channels.RemoveClientToChannel(log, client, channelName);
			irc->_channels.SendReply(":" + client->userName + "!~" + client->userName
				+ "@Localhost KICK #" + channelName, log, targetfd, 0);
			irc->_channels.SendReply("001 SUCCESS" + client->nickName + channelName + " has been kicked from the channel : " + words[3], log, client->fd->fd, 1);
			return;
		}
		else
		{
			irc->_channels.SendReply("001 " + client->userName + " #"
				+ channelName + " : User not in that channel", log, targetfd, 1);
		}
	}
}
