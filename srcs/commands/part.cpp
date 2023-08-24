/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <nadesjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:18:13 by nadesjar          #+#    #+#             */
/*   Updated: 2023/08/24 00:27:29 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/IrcCore.hpp"

//*********************************** PART ***********************************//

void	PartChannel(IrcCore *irc, Logger *log, IrcMemory *ircMemory, ircClient *client,
			std::vector<std::string> words)
{
// DEBUG :	
// std::cout << "  Word0: " << words[0] <<  "  Word1: " << words[1] << "  Word2: " << words[2] << "  Word[] Size: " << words.size() << std::endl;
	// If using part in a channel
	if (words[1] == ":" || words[1].c_str() == NULL)
	{
		log->ERROR("Channel name missing");
		irc->_channels.SendReply("403 " + client->userName
			+ "@localHost.com #channel not found", log, client->fd->fd, 1);
		return;
	}
	std::string channelName = words[1];
	log->WARNING("PART() channelName1: %s", channelName.c_str());
	if (channelName.at(0) == '#')
		channelName.erase(channelName.begin());
	log->WARNING("PART() channelName2: %s", channelName.c_str());
	// if channel don't exist (2 words)
	if (irc->GetChannelExist(channelName) == false)
	{
		irc->_channels.SendReply("403 " + client->userName
			+ channelName + " : Channel not found", log, client->fd->fd, 1);
		return;
	}
	if (irc->_channels.AllreadyInThatChannel(channelName, client->fd->fd) == false)
	{
		log->ERROR("Not in the Channel");
		irc->_channels.SendReply("403 " + client->userName
			+ " Not in the channel", log, client->fd->fd, 1);
	return;
	}
	if (words.size() == 2)
	{
			irc->_channels.RemoveClientToChannel(log, client, channelName);
			irc->_channels.SendReply(":" + client->userName + "!~" + client->userName
				+ "@Localhost PART #" + channelName, log, client->fd->fd, 0);
			return;
	}
	else if (words.size() > 2)
	{
		// if word[2] == Leaving... // Right-click User interface
		if(strcmp("Leaving...", words.at(2).c_str()) == 0)
		{
			irc->_channels.RemoveClientToChannel(log, client, channelName);
			irc->_channels.SendReply(":" + client->userName + "!~" + client->userName
				+ "@Localhost PART #" + channelName, log, client->fd->fd, 0);
			return;
		}
		channelName = words[2];
		// log->WARNING("PART() channelName1: %s", channelName.c_str());
		if (channelName.at(0) == '#')
			channelName.erase(0, 1);
		// log->WARNING("PART() channelName2: %s", channelName.c_str());
		// if channel don't exist (3 words)
		if (irc->GetChannelExist(channelName) == false)
		{
			irc->_channels.SendReply("403 " + client->userName
				+ channelName + " : Channel not found", log, client->fd->fd, 1);

			return;
		}

		// Check if the client is already in the channel
		if (irc->_channels.AllreadyInThatChannel(channelName, client->fd->fd) == true)
		{
			irc->_channels.RemoveClientToChannel(log, client, channelName);
			irc->_channels.SendReply(":" + client->userName + "!~" + client->userName
				+ "@Localhost PART #" + channelName, log, client->fd->fd, 0);
			return;
		}
		else
		{
			irc->_channels.SendReply("403 " + client->userName + " #"
				+ channelName + " : You're not in that channel", log, client->fd->fd, 1);
		}
	}
}
