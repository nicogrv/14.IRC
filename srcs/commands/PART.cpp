/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:29:58 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/28 12:30:44 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Client.hpp"
#include "utils/utils.hpp"
#include "classes/Channel.hpp"
#include "utils/ircNumerics.hpp"

/* ************************************************************************** */

static void _partChannel(Client *client, string_t channelName)
{
	char		firstChar;
	string_t	userList;

	firstChar = channelName[0];
	channelName.erase(0, 1);
	
	if (firstChar != '#' || channelName.empty())
		return client->sendMessage(formatIrcMessage(g_servername, ERR_BADCHANMASK, client->getNickname() + " " + firstChar + channelName, "Syntax error, invalid channel name"));
	else if (!containsOnlyAllowedChars(channelName))
		return client->sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHCHANNEL, client->getNickname() + " #" + channelName, "Channel name contains invalid characters"));
	
	transform(channelName.begin(), channelName.end(), channelName.begin(), tolower);
	
	if (g_channels.find(channelName) == g_channels.end())
		return client->sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHCHANNEL, client->getNickname() + " #" + channelName, "No such channel"));
	else if (!g_channels[channelName].isConnected(client) || client->_channels.find(channelName) == client->_channels.end())
		return client->sendMessage(formatIrcMessage(g_servername, ERR_NOTONCHANNEL, client->getNickname() + " #" + channelName, "You're not on channel"));
	g_channels[channelName].sendMessage(NULL, formatIrcMessage(client->getFullname(), "PART", "#" + channelName, ""));
	g_channels[channelName].disconnect(client);
	client->_channels.erase(channelName);
	if (g_channels[channelName].getUsers().empty())
		g_channels.erase(channelName);
}

void	Client::PART(string_t content)
{
	std::deque<string_t>	channelNames;
	
	if (content.empty())
		return sendMessage(formatIrcMessage(g_servername, ERR_NEEDMOREPARAMS, this->_nickname + " " + "PART", "PART needs more parameters"));
	channelNames = split(content, ",");

	while (channelNames.size() > 0)
	{
		_partChannel(this, channelNames.front());
		channelNames.pop_front();
	}
}
