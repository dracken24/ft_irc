/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quitServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <nadesjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:04:12 by nadesjar          #+#    #+#             */
/*   Updated: 2023/07/24 16:50:45 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/IrcCore.hpp"

void	QuitServer(IrcCore *irc, Logger *log, IrcMemory *ircMemory, ircClient *client)
{
	log->INFO("Quit Server !!!");
	std::map<std::string, channel_t> servers = irc->GetAllChannelsInfos();
	std::map<std::string, channel_t>::const_iterator iter = servers.begin();
	for (; iter != servers.end(); iter++)
	{
		channel_t channel = iter->second;
		if (channel.channelName.size() <= 0)
		{
			continue;
		}
		std::cout << "Name: " << channel.channelName << std::endl;
		for (std::vector<ircClient *>::const_iterator it = channel.users.begin(); it != channel.users.end(); it++)
		{
			std::cout << "Debug1: " << std::endl;
			ircClient* cli = *it;
			if (client->fd->fd == cli->fd->fd)
			{
				log->DEBUG("Erase from channels: %s", channel.channelName.c_str());
				channel.users.erase(it);
				channel.nbrMembers--;
				continue;
			}
			std::cout << "Debug2: " << std::endl;
		}
	}
}
