/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayrand <smayrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:43:23 by smayrand          #+#    #+#             */
/*   Updated: 2023/08/16 15:57:38 by smayrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/IrcCore.hpp"
#include <string>

//*********************************** TOPIC ***********************************//
//TODO: DOIT VERIFIER SI L'USER EST DANS UN CHANNEL
void	topicCMD(IrcCore *irc, IrcMemory *ircMemory, Splinter *splitCMD)
{
	if(splitCMD->GetWords().size() == 1)
		return(irc->_channels.SendReply("403 " + splitCMD->GetSender()->nickName + " Change the topic using this format :: /TOPIC <New Topic>",
			&splitCMD->_logger, splitCMD->GetSender()->fd->fd, 1));
	std::string channelName = splitCMD->GetWords().at(1);
	if(channelName.at(0) == '#')
		channelName.erase(channelName.begin());
	if(irc->GetChannelExist(channelName) == false)
			return(irc->_channels.SendReply("403 " + splitCMD->GetSender()->nickName + "Error: You must be in a channel to change the Topic",
			&splitCMD->_logger, splitCMD->GetSender()->fd->fd, 1));
	if(splitCMD->GetWords().size() == 2)
		return(irc->_channels.SendReply("001 " + splitCMD->GetChannelName() + "Log: <" + channelName + "> Topic: " + irc->_channels.GetChannelTopic(channelName), 
			&splitCMD->_logger, splitCMD->GetSender()->fd->fd, 1));
	else if((irc->GetSpecificChannel(channelName)._topicFlag == true && splitCMD->GetSender()->isAdmin == 2 )|| splitCMD->GetSender()->isAdmin == true)
	{
		std::string newTopic = splitCMD->GetWords().at(2);
		for(unsigned long i = 3; i < splitCMD->GetWords().size(); i++)
			newTopic = newTopic + " " + splitCMD->GetWords().at(i);
		if(newTopic.at(0) == ':')
			newTopic.erase(newTopic.begin()); 
		irc->_channels.SetTopic(channelName, newTopic);
		return(irc->_channels.SendReply("001 " + splitCMD->GetChannelName() + "Log: <" + channelName + "> Topic: " + irc->_channels.GetChannelTopic(channelName), 
			&splitCMD->_logger, splitCMD->GetSender()->fd->fd, 1));
	}
	else
		return(irc->_channels.SendReply("403 " + splitCMD->GetSender()->nickName + "Error: You don't have the right to change Topic",
			&splitCMD->_logger, splitCMD->GetSender()->fd->fd, 1));
	
}