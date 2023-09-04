/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quitServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayrand <smayrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:04:12 by nadesjar          #+#    #+#             */
/*   Updated: 2023/09/04 17:03:08 by smayrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/IrcCore.hpp"
#include <vector>

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
                channel.users.erase(it);
                channel.nbrMembers--;
                break;
            }
            std::cout << "Debug2: " << std::endl;
        }
    }
}
