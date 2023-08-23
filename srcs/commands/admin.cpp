/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   admin.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayrand <smayrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 23:38:31 by nadesjar          #+#    #+#             */
/*   Updated: 2023/08/23 15:44:28 by smayrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/IrcCore.hpp"

void	CheckAdminPassword(IrcCore *irc, Logger *log, int32 i, Splinter *splitCMD)
{
	if (splitCMD->GetWords().size() == 2 && splitCMD->GetWords().at(1) == irc->GetAdminPassword())
	{
		irc->SetAdminRights(i, 1);
//		std::string nicknameModif = irc->GetNickname(i) + "(🔥Admin🔥)";
//		irc->SetClientNickname(i, nicknameModif);
	}
}

void	MakeOperator(IrcCore *irc, Logger *log, int32 i, Splinter *splitCMD)
{
		irc->SetAdminRights(i, 2);
//		std::string nicknameModif = irc->GetNickname(i) + "(Moderator🍆💦👅)";
//		irc->SetClientNickname(i, nicknameModif);
}

void	PromoteToCustomer(IrcCore *irc, Logger *log, int32 i, Splinter *splitCMD)
{
		irc->SetAdminRights(i, 0);
//		std::string nicknameModif = irc->GetNickname(i);
//		std::string substring = "(Moderator🍆💦👅)";
//		int32 pos = nicknameModif.find(substring);
//		nicknameModif.erase(pos, substring.length());
//		irc->SetClientNickname(i, nicknameModif);
}
