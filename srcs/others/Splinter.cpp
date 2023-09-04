/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Splinter.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayrand <smayrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:27:48 by nadesjar          #+#    #+#             */
/*   Updated: 2023/09/04 15:32:17 by smayrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Splinter.hpp"
# include "../../C_tools/C_tool.h"
# include "../includes/defines.hpp"

#include <sstream>

//**********************************************************************//
//**                     Constructors / Destructor                    **//
//**********************************************************************//
//PUBLIC

Splinter::Splinter(std::string buffer, ircClient *sender, std::vector<ircClient> clients) :
_buffer(buffer),
_sender(sender),
_targetClients(clients)
{
	// TODO: For debugging, remove eventualy
	_logger.DEBUG("Buffer in Splinter: %s", buffer.c_str());
	char *str = (char *)malloc(sizeof(char) * 4096);
	str = (char *)buffer.c_str();
	Ct_mprintf(str, std::strlen(str), 1, 'S');
	// *** //

	SplitCMD();
}

// Remove the sender client from clients list for send a general message
void	RemoveSenderInClients(ircClient *sender, std::vector<ircClient> *targetClients)
{
	std::vector<ircClient>::const_iterator it = targetClients->begin();
	while (it != targetClients->end())
	{
		ircClient cli = *it;
		if (sender->nickName == cli.nickName)
		{
			targetClients->erase(it);
			return;
		}
		it++;
	}
}

void	Splinter::SplitCMD()
{
	// std::vector<std::string> words;
	std::string message(_buffer);
	std::istringstream iss(message);
	std::string word;

	// Split words
	while (iss >> word)
	{
		_words.push_back(word);
		_logger.TRACE("Word: %s", word.c_str());
	}
//Debug _words
std::cout << "_words Nb -> " << _words.size() << std::endl;
	// Choose command
	if (_words[0] == JOIN)
	{
		_logger.ERROR("Commande Join: %s", _words[0].c_str());
		_cmd = JOIN;
		_isPrivate = false;
		_isChannel = true;
		_channelName = _words.at(1);

		// for (s_t i = 0; i < _targetClients.size(); i++)
		// {
		// 	_logger.WARNING("clents before: %s", _targetClients.at(i).nickName.c_str());
		// }
		RemoveSenderInClients(_sender, &_targetClients);
	}
	else if (_words[0] == PONG)
	{
		_logger.ERROR("Commande PONG: %s", _words[0].c_str());
		_cmd = PONG;
		_isPrivate = false;
		_isChannel = true;
		_channelName = _words.at(1);

		RemoveSenderInClients(_sender, &_targetClients);
	}
	else if (_words[0] == PART)
	{
		_logger.ERROR("Commande PART: %s", _words[0].c_str());
		_cmd = PART;
		_isPrivate = false;
		_isChannel = true;
		_channelName = _words.at(1);

		RemoveSenderInClients(_sender, &_targetClients);
	}
	else if (_words[0] == QUIT)
	{
		_logger.ERROR("Commande PART: %s", _words[0].c_str());
		_cmd = QUIT;
		_isPrivate = false;
		_isChannel = false;
	}
	else if (_words[0] == LIST)
	{
		_logger.ERROR("Commande List: %s", _words[0].c_str());
		_cmd = LIST;
		_isPrivate = false;
		_isChannel = false;
		_targetClients.clear();
	}
	else if (_words[0] == PRIVMSG)
	{
		_logger.ERROR("Commande PRIVMSG: %s", _words[0].c_str());
		_cmd = PRIVMSG;
		_isPrivate = true;
		_isChannel = false;
		_channelName = _words.at(1);

		RemoveSenderInClients(_sender, &_targetClients);
	}
	else if (_words[0] == KICK)
	{
		_logger.ERROR("Commande KICK: %s", _words[0].c_str());
		_cmd = KICK;
		_isPrivate = false;
		_isChannel = true;
		_channelName = _words.at(1);

		RemoveSenderInClients(_sender, &_targetClients);
	}
	else if (_words[0] == INVITE)
	{
		_logger.ERROR("Commande INVITE: %s", _words[0].c_str());
		_cmd = INVITE;
		_isPrivate = false;
		_isChannel = true;
		_channelName = _words.at(1);

		RemoveSenderInClients(_sender, &_targetClients);
	}
	else if (_words[0] == TOPIC)
	{
		_logger.ERROR("Commande TOPIC: %s", _words[0].c_str());
		_cmd = TOPIC;
		_isPrivate = false;
		_isChannel = false;
	}
	else if (_words[0] == MODE)
	{
		if(_words.size() > 3  && _words[2] == "-i")
		{
			_channelName = _words[3];
			if(_channelName.at(0) != '#')
				_channelName.insert(0, "#");
		}
		_logger.ERROR("Commande MODE: %s", _words[0].c_str());
		_cmd = MODE;
		_isPrivate = false;
		_isChannel = false;
	}
	else if (_words[0] == ADMIN && _words.size() == 2)
	{
		_logger.ERROR("Commande ADMIN: %s", _words[0].c_str());
		_cmd = ADMIN;
		_isPrivate = false;
		_isChannel = false;
	}
	else if (_words[0] == "LEAKS" && _words.size() == 1)
	{
		_logger.ERROR("Commande LEAKS: %s", _words[0].c_str());
		_cmd = "LEAKS";
		_isPrivate = false;
		_isChannel = false;
	}
	else
	{
		_logger.FATAL("Command not found!!!");
	}
}

Splinter::Splinter(Splinter const &src)
{
	if (this != &src)
	{
		*this = src;
	}
}

Splinter    &Splinter::operator=(Splinter const &src)
{
	if (this != &src)
	{
		_sender = src._sender;
		_targetClients = src._targetClients;

		_buffer = src._buffer;
		_cmd = src._cmd;
		_messages = src._messages;

		_isPrivate = src._isPrivate;
		_isChannel = src._isChannel;
		_logger = src._logger;
	}

	return *this;
}

Splinter::~Splinter(void)
{

}

// PRIVATE

Splinter::Splinter(void)
{ }

//**********************************************************************//
//**                     		SETTERS    	     		              **//
//**********************************************************************//

void	Splinter::SetTargetClients(std::vector<ircClient> const &targetlients)
{
	for (s_t i = 0; i < targetlients.size(); i++)
	{
		ircClient client = targetlients.at(i);
		_targetClients.push_back(client);
	}
}

//**********************************************************************//
//**                     		GETTERS    	     		              **//
//**********************************************************************//

std::string	Splinter::GetMasterCommand(void) const
{
	return _cmd;
}

std::string	Splinter::GetChannelName(void) const
{
	return _channelName;
}

ircClient	*Splinter::GetSender(void) const
{
	return _sender;
}

std::vector<ircClient>	Splinter::GetTargetClients(void) const
{
	return _targetClients;
}

std::vector<std::string>	Splinter::GetWords(void) const
{
	return _words;
}

//**********************************************************************//
//**                          PUBLIC METHODS                          **//
//**********************************************************************//
