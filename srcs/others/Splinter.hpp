/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Splinter.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <nadesjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:27:43 by nadesjar          #+#    #+#             */
/*   Updated: 2023/07/03 12:48:16 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPLINTER_HPP
# define SPLINTER_HPP

# include "ChannelGestion.hpp"
# include "Logger.hpp"

class Splinter
{
	//**********************************************************************//
	//**                     Constructors / Destructor                    **//
	//**********************************************************************//
	public:
		Splinter(std::string buffer, ircClient *sender, std::vector<ircClient> clients);
		Splinter(Splinter const &src);
		Splinter    &operator=(Splinter const &src);
		~Splinter(void);

	private:
		Splinter(void);

	//**********************************************************************//
	//**                     		SETTERS    	     		              **//
	//**********************************************************************//

	public:
		void	SetTargetClients(std::vector<ircClient> const &targetlients);

	//**********************************************************************//
	//**                     		GETTERS    	     		              **//
	//**********************************************************************//
	
	std::string	GetMasterCommand(void) const;
	std::string	GetChannelName(void) const;
	
	ircClient	*GetSender(void) const;
	std::vector<ircClient>	GetTargetClients(void) const;
	std::vector<std::string> GetWords(void) const;

	//**********************************************************************//
	//**                          PUBLIC METHODS                          **//
	//**********************************************************************//

	//**********************************************************************//
	//**                         PRIVATE METHODS                          **//
	//**********************************************************************//
	private:
		void	SplitCMD();

	//**********************************************************************//
	//**                          MEMBERS VARS	                          **//
	//**********************************************************************//
	private:
		ircClient *_sender;						// Client sending the message
		std::vector<ircClient> _targetClients;	// List of client receve the message

		std::string	_buffer;					// The entier message
		std::string	_cmd;						// Command to execute
		std::string	_channelName;				// Channel to send to if it's applicable
		std::string	_messages;					// Message to send to target clients
		std::vector<std::string> _words;

		bl8		_isPrivate;						// True if it's a private message
		bl8		_isChannel;						// True if it's send to a specific channel if it's applicable

	public:
		Logger	_logger;						// For print color messages
};

#endif
