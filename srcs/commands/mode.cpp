/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayrand <smayrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:42:43 by smayrand          #+#    #+#             */
/*   Updated: 2023/08/09 15:04:03 by smayrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/IrcCore.hpp"

void	Mode(IrcCore *irc, Logger *log, IrcMemory *ircMemory, pollfd *fds, Splinter *splitCMD, int32 i)
{
//debug:
//std::cout << "WORD0 : " << splitCMD->GetWords().at(0) <<"  WORD1 : " << splitCMD->GetWords().at(1) << "  WORD2 : " << splitCMD->GetWords().at(2) << std::endl;
	if(splitCMD->GetWords().size() >= 2)
	{
		std::string mode = splitCMD->GetWords().at(2);
	//Définir/supprimer le canal sur invitation uniquement
		if(strcmp(mode.c_str(), "-i") == 0)
		{
			std::cout << "-i " << std::endl;
			
		}
	//Définir/supprimer les restrictions de la commande TOPIC pour les opérateurs de canaux
		else if(strcmp(mode.c_str(), "-t") == 0)
		{
			std::cout << "-t " << std::endl;
			
		}
	//Définir/supprimer la clé du canal (mot de passe)
		else if(strcmp(mode.c_str(), "-k") == 0)
		{
			std::cout << "-k " << std::endl;
	
		}
	//Donner/retirer le privilège de l’opérateur de canal
		else if(strcmp(mode.c_str(), "-o") == 0)
		{
			std::cout << "-o " << std::endl;
			
		}
	//Définir/supprimer la limite d’utilisateurs pour le canal
		else if(strcmp(mode.c_str(), "-l") == 0)
		{
			std::cout << "-l " << std::endl;
			
		}
		else
		{
			std::cout << "Error: Unknown function" << std::endl;
			
		}
	}
	else
	{
		std::cout << "Error: Need a function " << std::endl;
//		irc->_channels.SendReply("403 :Syntax Error", log,   client->fd->fd, 1);
	}
}