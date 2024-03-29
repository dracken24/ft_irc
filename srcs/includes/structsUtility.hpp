/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structsUtility.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <nadesjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:24:19 by nadesjar          #+#    #+#             */
/*   Updated: 2023/08/21 14:12:41 by nadesjar         ###   ########.fr       */
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
	uint16	nbrMembers;
	uint16	maxUsers;
	
	bl8			didHavePassword;
	std::string password;
	
	std::string	channelName;
	// std::string channelDescription;
	std::string channelTopic;
	std::vector<ircClient *>	users;
	
	bl8		_topicFlag;	
}	channel_t;

#endif
