/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   admin.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayrand <smayrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 23:38:31 by nadesjar          #+#    #+#             */
/*   Updated: 2023/07/27 02:11:20 by smayrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/IrcCore.hpp"

void	CheckAdminPassword(IrcCore *irc, Logger *log, int32 i, Splinter *splitCMD)
{
	if (splitCMD->GetWords().size() == 2 && splitCMD->GetWords().at(1) == irc->GetAdminPassword())
	{
		irc->SetAdminRights(i, true);
		std::string nicknameModif = irc->GetNickname(i) + "(🔥Admin🔥)";
		irc->SetClientNickname(i, nicknameModif);
	}
}
