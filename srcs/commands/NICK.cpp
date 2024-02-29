/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:23:55 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/28 13:15:03 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Client.hpp"
#include "classes/Server.hpp"
#include "utils/ircNumerics.hpp"
#include "utils/utils.hpp"

/* ************************************************************************** */

static string_t	welcomeBurst(Client &client)
{
	string_t	str;
	string_t	nickname;

	nickname = client.getNickname();
	str += formatIrcMessage(g_servername, RPL_WELCOME, nickname, "Welcome to the " + g_servername + " Network, " + nickname);
	str += formatIrcMessage(g_servername, RPL_YOURHOST, nickname, "Your host is " + g_servername + ", running version " + g_serversion);
	str += formatIrcMessage(g_servername, RPL_CREATED, nickname, "This server was created " + formatTime(Server::launchTime));
	str += formatIrcMessage(g_servername, RPL_MYINFO, nickname, "-");
	str += formatIrcMessage(g_servername, RPL_MOTDSTART,nickname, "You are in a maze of twisty passages, all alike.");
	str += formatIrcMessage(g_servername, RPL_MOTD, nickname, "-");
	str += formatIrcMessage(g_servername, RPL_ENDOFMOTD, nickname, ">");
	return str;
}

void	Client::NICK(string_t nickname)
{
	bool	sendWelcomeBurst;

	if (nickname.empty())
		return sendMessage(formatIrcMessage(g_servername, ERR_NEEDMOREPARAMS, (string_t)GUEST + " " + "NICK", "NICK needs more parameters"));
	sendWelcomeBurst = false;
	transform(nickname.begin(), nickname.end(), nickname.begin(), tolower);
	if (this->_nickname.compare(nickname) == 0)
		return ;
	nickname = rTrim(nickname.substr(0, nickname.find(':')));
	
	if (!containsOnlyAllowedChars(nickname))
		return sendMessage(formatIrcMessage(g_servername, ERR_ERRONEUSNICKNAME, GUEST, "Nickname containing invalid characters"));
	else if (nickname.compare(GUEST) == 0)
		return sendMessage(formatIrcMessage(g_servername, ERR_ERRONEUSNICKNAME, GUEST, "Nickname reserved, choose a different one"));
	else if (nicknames.find(nickname) != nicknames.end())
		return sendMessage(formatIrcMessage(g_servername, ERR_NICKNAMEINUSE, GUEST, nickname + " :Nickname is already in use"));
	
	if (this->_nickname.empty())
		sendWelcomeBurst = true;
	else
		nicknames.erase(this->_nickname);
	nicknames[nickname] = this;
	this->_nickname = nickname;
	if (sendWelcomeBurst)
	{
		sendMessage(welcomeBurst(*this));
		sendWelcomeBurst = false;
	}
}
