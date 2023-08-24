/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <nadesjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:42:43 by smayrand          #+#    #+#             */
/*   Updated: 2023/08/24 01:20:45 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/IrcCore.hpp"
#include <string>

void	Mode(IrcCore *irc, Logger *log, IrcMemory *ircMemory, pollfd *fds, Splinter *splitCMD, int32 i)
{
//debug:
//std::cout << "WORD0 : " << splitCMD->GetWords().at(0) <<"  WORD1 : " << splitCMD->GetWords().at(3) << "  I: " << i << std::endl;
 //"  WORD1 : " << splitCMD->GetWords().at(1) << "  WORD2 : " << splitCMD->GetWords().at(2) <<
	if(splitCMD->GetWords().size() >= 2)
	{
			std::cout << "Mode " ;
		std::string mode;
		if (splitCMD->GetWords().size() > 2)
		{
			mode = splitCMD->GetWords().at(2);
		}
			
	//Définir/supprimer le canal sur invitation uniquement
		if(strcmp(mode.c_str(), "-i") == 0)
		{
			std::cout << "-i " << std::endl;
			if(splitCMD->GetWords().size() == 6 || splitCMD->GetWords().size() == 5)
			{
				std::string channelName = splitCMD->GetWords().at(3);
				std::string topic = splitCMD->GetWords().at(4);
				std::string pass = "";
				if(splitCMD->GetWords().size() == 6)
					pass = splitCMD->GetWords().at(5);
				
				irc->_channels.SetNewChannel(channelName, topic, pass);
				JoinChannel(irc, ircMemory, splitCMD);
				irc->_channels.SendReply("001 " + splitCMD->GetChannelName() + "Log: Channel :<" + channelName + "> has been created. " , 
				&splitCMD->_logger, splitCMD->GetSender()->fd->fd, 1);
			}
			else if (splitCMD->GetWords().size() == 4)
			{
				// std::cout << "DEBUG 1" << std::endl;
				std::string Destroy = splitCMD->GetWords().at(3);
				if(strcmp(Destroy.c_str(), "delete") == 0)
				{
					// std::cout << "DEBUG 2: " << irc->GetChannelExist(splitCMD->GetWords().at(1)) << " " << splitCMD->GetWords().at(1) << std::endl;
					if (irc->GetChannelExist(splitCMD->GetWords().at(1)))
					{
						// std::cout << "DEBUG 3" << std::endl;
						if (splitCMD->GetWords().at(1).at(0) == '#')
						{
							splitCMD->GetWords().at(1).erase(0, 1);
						}
						irc->_channels.DeleteAllClientFromChannel(irc, log, splitCMD->GetSender(), ircMemory, splitCMD->GetWords(), splitCMD->GetWords().at(1));
					}
				}
			}
			else
				return(irc->_channels.SendReply("403 " + splitCMD->GetSender()->nickName + " Error: syntax error use this syntax: /mode -i <ChannelName> <Topic> <Password(Optional)>",
					&splitCMD->_logger, splitCMD->GetSender()->fd->fd, 1));		
		}
	//Définir/supprimer les restrictions de la commande TOPIC pour les opérateurs de canaux
		else if(strcmp(mode.c_str(), "-t") == 0)
		{
			std::cout << "-t " << std::endl;
			if(splitCMD->GetWords().size() == 4)
			{
				std::string channelName = splitCMD->GetWords().at(1);
				if(channelName.at(0) == '#')
					channelName.erase(channelName.begin());
				if(splitCMD->GetWords().at(3) == "true" && irc->GetSpecificChannel(channelName)._topicFlag == false)
				{
					irc->_channels.SetTopicRight(channelName, true);
					irc->_channels.SendReply("001 " + splitCMD->GetChannelName() + "Log: <" + channelName + "> Operators can now change the topic of this channel ", 
			&splitCMD->_logger, splitCMD->GetSender()->fd->fd, 1);
				}	
				else if(splitCMD->GetWords().at(3) == "false" && irc->GetSpecificChannel(channelName)._topicFlag == true)
				{
					irc->_channels.SetTopicRight(channelName, false);
					irc->_channels.SendReply("001 " + splitCMD->GetChannelName() + "Log: <" + channelName + "> Operators cannot change the topic of this channel anymore " , 
			&splitCMD->_logger, splitCMD->GetSender()->fd->fd, 1);
				}
			}
			else
				return(irc->_channels.SendReply("403 " + splitCMD->GetSender()->nickName + " Error: syntax error use this syntax: /mode -t <true/false>",
					&splitCMD->_logger, splitCMD->GetSender()->fd->fd, 1));		
				
		}
	//Définir/supprimer la clé du canal (mot de passe)
		else if(strcmp(mode.c_str(), "-k") == 0)
		{
			std::cout << "-k " << std::endl;
			if(splitCMD->GetWords().size() == 4)
			{
				std::string channelName = splitCMD->GetWords().at(1);
				std::string NewPass = splitCMD->GetWords().at(3);
				if(channelName.at(0) == '#')
					channelName.erase(channelName.begin());
				irc->_channels.SetChannelPassword(channelName, NewPass);
				irc->_channels.SendReply("001 " + splitCMD->GetChannelName() + "Log: <" + channelName + "> password has been changed to: " + splitCMD->GetWords().at(3), 
				&splitCMD->_logger, splitCMD->GetSender()->fd->fd, 1);
			}
			else if(splitCMD->GetWords().size() == 3)
			{
				std::string channelName = splitCMD->GetWords().at(1);
				std::string NewPass = "";
				if(channelName.at(0) == '#')
					channelName.erase(channelName.begin());
				irc->_channels.SetChannelPassword(channelName, NewPass);
				irc->_channels.SendReply("001 " + splitCMD->GetChannelName() + "Log: <" + channelName + "> password has been changed to: " + splitCMD->GetWords().at(3), 
				&splitCMD->_logger, splitCMD->GetSender()->fd->fd, 1);
			}
			else
				return(irc->_channels.SendReply("403 " + splitCMD->GetSender()->nickName + " Error: Syntax Error use this syntax: /mode -l <MaxUsersNb>",
					&splitCMD->_logger, splitCMD->GetSender()->fd->fd, 1));	
		}
	//Donner/retirer le privilège de l’opérateur de canal
		else if(strcmp(mode.c_str(), "-o") == 0)
		{
			std::cout << "-o " << std::endl;
			if (splitCMD->GetWords().size() != 5)
				return(irc->_channels.SendReply("403 " + splitCMD->GetSender()->nickName + " Change the Operator value using this syntax :: /mode -o <user> <true/false>  (You must be in a channel.)",
					&splitCMD->_logger, splitCMD->GetSender()->fd->fd, 1));
			else
			{
				i = irc->GetClientNb(splitCMD->GetWords().at(3));
				if(splitCMD->GetWords().at(4) == "true" && irc->GetIsAdmin(i) == 0)
				{
					MakeOperator(irc, log, i, splitCMD);
					irc->_channels.SendReply("001 " + splitCMD->GetChannelName() + "Log: <" + splitCMD->GetWords().at(3) + "> is now an operator ", 
					&splitCMD->_logger, splitCMD->GetSender()->fd->fd, 1);
				}
				else if(splitCMD->GetWords().at(4) == "false" && irc->GetIsAdmin(i) == 2)
				{
					PromoteToCustomer(irc, log, i, splitCMD);
					irc->_channels.SendReply("001 " + splitCMD->GetChannelName() + "Log: <" + splitCMD->GetWords().at(3) + "> has been promoted to customer ", 
					&splitCMD->_logger, splitCMD->GetSender()->fd->fd, 1);
				}	
				else if (splitCMD->GetWords().at(4) == "true" && irc->GetIsAdmin(i) == 2)
					return(irc->_channels.SendReply("403 " + splitCMD->GetSender()->nickName + " Error: User is already an operator",
						&splitCMD->_logger, splitCMD->GetSender()->fd->fd, 1));		
				else
					return(irc->_channels.SendReply("403 " + splitCMD->GetSender()->nickName + " Error: User is not an operator or syntax error",
						&splitCMD->_logger, splitCMD->GetSender()->fd->fd, 1));		
			}
		}
	//Définir/supprimer la limite d’utilisateurs pour le canal
		else if(strcmp(mode.c_str(), "-l") == 0)
		{
			std::cout << "-l " << std::endl;
			if(splitCMD->GetWords().size() == 4)
			{
				std::string channelName = splitCMD->GetWords().at(1);
				if (IsDigit(splitCMD->GetWords().at(3)) != 0)
				{
					uint16 nb = stoi(splitCMD->GetWords().at(3));
					if(channelName.at(0) == '#')
						channelName.erase(channelName.begin());
					irc->_channels.SetMaxUser(channelName, nb);
					irc->_channels.SendReply("001 " + splitCMD->GetChannelName() + "Log: <" + channelName + "> Max user number has been set to: " + splitCMD->GetWords().at(3), 
			&splitCMD->_logger, splitCMD->GetSender()->fd->fd, 1);
				}
				else
					return(irc->_channels.SendReply("403 " + splitCMD->GetSender()->nickName + " Error: Syntax Error last argument is not a number use this syntax: /mode -l <MaxUsersNb>",
						&splitCMD->_logger, splitCMD->GetSender()->fd->fd, 1));		
			}
			else
				return(irc->_channels.SendReply("403 " + splitCMD->GetSender()->nickName + " Error: Syntax Error use this syntax: /mode -l <MaxUsersNb>",
					&splitCMD->_logger, splitCMD->GetSender()->fd->fd, 1));		
			
		}
		else
		{
			std::cout << "Error: Unknown function" << std::endl;
				return(irc->_channels.SendReply("403 " + splitCMD->GetSender()->nickName + " Error: Unknown mode use these options: -i, -t, -k, -o, -l \n -i : create/delete channel\n -t : change right to change the topic of a channel\n -k : change the password of a channel\n -o : change user rights\n -l : change user limit in a channel\n  ",
					&splitCMD->_logger, splitCMD->GetSender()->fd->fd, 1));		
			
		}
	}
	else
	{
		std::cout << "Error: Need a function " << std::endl;
//		irc->_channels.SendReply("403 :Syntax Error", log,   client->fd->fd, 1);
	}
}