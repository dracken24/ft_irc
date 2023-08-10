/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayrand <smayrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:43:10 by smayrand          #+#    #+#             */
/*   Updated: 2023/08/01 15:22:36 by smayrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/IrcCore.hpp"

//*********************************** INVITE ***********************************//

void	InviteUser(IrcCore *irc, IrcMemory *ircMemory, Splinter *splitCMD)
{
	if(splitCMD->GetWords().size() != 3)
		return(irc->_channels.SendReply("403 " + splitCMD->GetSender()->nickName + " Invite using this format :: /INVITE nickname #channel ",
			&splitCMD->_logger, splitCMD->GetSender()->fd->fd, 1));
	int32 targetfd = irc->GetClientFd(splitCMD->GetWords().at(1));
	std::string channelName = splitCMD->GetWords().at(2);
// DEBUG:
	std::cout << T_RED" * USER FD :: "<< targetfd << "  Word0: " << splitCMD->GetWords().at(0) <<  "  Word1: " << splitCMD->GetWords().at(1) << "  Word2: " << splitCMD->GetWords().at(2) << std::endl;
	splitCMD->_logger.TRACE("Invite: %s size: %d", channelName.c_str(), channelName.size());
	s_t i = 0;
	for (; i < channelName.size(); i++)
	{
		if (channelName.at(i) == '#' || channelName.at(i) == ',')
		{
			if (channelName.at(i) == '#' && channelName.at(i + 1) == '#')
			{
				continue;
			}
			splitCMD->_logger.INFO("i: %d", i);
		}
	}
	splitCMD->_logger.INFO("i: %d", i);
	std::cout << "Channel Name: " << splitCMD->GetWords().at(2) << " Target FD: " << targetfd << std::endl;
	CheckIfChannelExist(irc, &splitCMD->_logger, splitCMD->GetWords().at(2), &irc->GetClient(targetfd));
}