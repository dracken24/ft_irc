/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayrand <smayrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 08:53:37 by dracken24         #+#    #+#             */
/*   Updated: 2023/08/10 14:11:28 by smayrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/IrcCore.hpp"

//************************************* JOIN *************************************//

void	CheckIfChannelExist(IrcCore *irc, Logger *log, std::string channelName, ircClient *client)
{
	if(channelName.at(0) == '#')
		channelName.erase(0, 1);
	// if channel don't existı
	if (irc->GetChannelExist(channelName) == false)
	{
		irc->_channels.SendReply("403 , channel #" + channelName + " don't exist", log, client->fd->fd, 1);
		return;
	}

	// Check if the client is already in the channel
	if (irc->_channels.AllreadyInThatChannel(channelName, client->fd->fd) == true)
	{
		irc->_channels.SendReply("403 , You are already in channel #" + channelName , log, client->fd->fd, 1);
		return;
	}
	else // Add client to channel
	{
		if (irc->_channels.AddClientToChannel(irc, log, client, channelName, false, 0) == true)
		{
			std::cout << "add client to channel" << std::endl;
			return;
		}
		else
		{
			irc->_channels.SendReply("403 :you fail join channel #"
				+ channelName + " :"  + client->userName + "@localHost.com", log, client->fd->fd, 1);
		}
	}
}

void	JoinChannel(IrcCore *irc, IrcMemory *ircMemory, Splinter *splitCMD)
{
	std::string channelName = splitCMD->GetChannelName();
	splitCMD->_logger.TRACE("Join: %s size: %d", channelName.c_str(), channelName.size());
	if (channelName.size() < 2 || splitCMD->GetWords().at(1) == "#") // Need a channel name after /join
	{
		splitCMD->_logger.WARNING("Need Channel name");
		irc->_channels.SendReply("403 " + splitCMD->GetSender()->nickName + " :need a channel name to join. from: "
			+ splitCMD->GetSender()->nickName + "@localHost.com", &splitCMD->_logger, splitCMD->GetSender()->fd->fd, 1);
		return;
	}
	
	// splitCMD->_logger.WARNING("JoinChannel() name: %s", channelName.c_str());

	std::vector<int32> hTags;
	s_t i = 0;
	for (; i < channelName.size(); i++)
	{
		if (channelName.at(i) == '#' || channelName.at(i) == ',')
		{
			if (channelName.at(i) == '#' && channelName.at(i + 1) == '#')
			{
				continue;
			}
			hTags.push_back(i);
			splitCMD->_logger.INFO("i: %d", i);
		}
	}
	hTags.push_back(i);
	splitCMD->_logger.INFO("i: %d", i);

	std::vector<std::string> channels;
	for (; hTags.size() > 0;)
	{
		std::string tmpNames = channelName;
		tmpNames = tmpNames.erase(hTags[1]);
		tmpNames = tmpNames.erase(0, hTags[0]);

		channels.push_back(tmpNames);
		// splitCMD->_logger.INFO("tmpNames: %s", tmpNames.c_str());
		hTags.erase(hTags.begin());
		hTags.erase(hTags.begin());
	}
	for (;channels.size() > 0;)
	{
		CheckIfChannelExist(irc, &splitCMD->_logger, channels.at(0), splitCMD->GetSender());
		// splitCMD->_logger.INFO("channelName: %s", channelName.c_str());
		channels.erase(channels.begin());
	}

	
}

//************************************* LIST *************************************//

void	ListChannels(IrcCore *irc, Logger *log, Splinter *splitCMD)
{
	std::cout << "client NickName: " << splitCMD->GetSender()->nickName << std::endl;
			// tell client he will receve #channels
			irc->_channels.SendReply("321 " + splitCMD->GetSender()->nickName +
					" Channel Users :Name", log, splitCMD->GetSender()->fd->fd, 1);
			
			std::vector<std::string> tmpChannels = irc->_channels.GetAllChannelsNames();

			for (size_t k = 0; k < tmpChannels.size(); k++)
			{
				std::string ret; 
				ret = Itoa(irc->_channels.GetMemebersInChannel(tmpChannels.at(k)));

				// send all channel to client one by one
				irc->_channels.SendReply("322 "+ splitCMD->GetSender()->nickName +
					" #" + tmpChannels.at(k) + " " + ret + " :" +
						irc->_channels.GetChannelDescription(tmpChannels.at(k)), log, splitCMD->GetSender()->fd->fd, 1);
			}
			// tell client he receve all avaliable #channels
			irc->_channels.SendReply("323 " + splitCMD->GetSender()->nickName +
					" :End of /LIST", log, splitCMD->GetSender()->fd->fd, 1);
}
