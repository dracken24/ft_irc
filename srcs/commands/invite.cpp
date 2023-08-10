/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayrand <smayrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:43:10 by smayrand          #+#    #+#             */
/*   Updated: 2023/08/10 14:39:48 by smayrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/IrcCore.hpp"

//*********************************** INVITE ***********************************// Should Work Properly

void	InviteUser(IrcCore *irc, IrcMemory *ircMemory, Splinter *splitCMD)
{
	if(splitCMD->GetWords().size() != 3)
		return(irc->_channels.SendReply("403 " + splitCMD->GetSender()->nickName + " Invite using this format :: /INVITE nickname #channel ",
			&splitCMD->_logger, splitCMD->GetSender()->fd->fd, 1));
	std::string Guest = splitCMD->GetWords().at(1);
	std::string channelName = splitCMD->GetWords().at(2);
	int32 targetfd = irc->GetClientFd(Guest);
// DEBUG:
//std::cout << T_RED" * GUEST FD :: "<< targetfd << "  Word0: " << splitCMD->GetWords().at(0) <<  "  Word1: " << splitCMD->GetWords().at(1) << "  Word2: " << splitCMD->GetWords().at(2) << std::endl;
//std::cout << "Channel Name: " << channelName << " Target FD: " << targetfd << "  GUEST : " << Guest << std::endl;
	splitCMD->_logger.TRACE("Invite: %s size: %d", channelName.c_str(), channelName.size());
	CheckIfChannelExist(irc, &splitCMD->_logger, channelName, &irc->GetClient(irc->GetClientNb(Guest)));
}