/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structsUtility.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <nadesjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:24:19 by nadesjar          #+#    #+#             */
/*   Updated: 2023/08/10 15:14:12 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUTSUTILITY_HPP
# define STRUTSUTILITY_HPP

# include <iostream>
# include <vector>
# include <poll.h>

# include "defines.hpp"

typedef struct ircClient
{
	bl8				admit;
	bl8				emptyFd;
	bl8				setUser;

	int32				isAdmin;

	std::string		nickName;
	std::string		userName;
	std::string		realName;
	std::string		password;
	std::string		channel;
	
	std::vector<ircClient *>	privateMessages;
	std::vector<std::string>	clientChannelIn;
	pollfd			*fd;
}	ircClient;

typedef struct channel_t
{
	uint16 nbrMembers;
	std::string	channelName;
	std::string channelDescription;
	std::vector<ircClient *>	users;
}	channel_t;

#endif
