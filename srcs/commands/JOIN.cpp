/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:28:03 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/28 14:47:23 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Client.hpp"
#include "classes/Channel.hpp"
#include "utils/utils.hpp"
#include "utils/ircNumerics.hpp"
#include <deque>

#define MAX_CHANNELS_PER_USER 10

/* ************************************************************************** */

static string_t	joinBurst(Client *client, string_t channelName, string_t userList)
{
	string_t	str;
	string_t	nickname;
	string_t	modeList;
	string_t	channelTopic;

	nickname = client->getNickname();
	channelTopic = g_channels[channelName].getTopic();
	modeList = g_channels[channelName].getModeList();
	g_channels[channelName].sendMessage(NULL, formatIrcMessage(client->getFullname(), "JOIN", "#" + channelName, ""));
	str += formatIrcMessage(client->getFullname(), "JOIN", "#" + channelName, "");
	if (modeList.length() > 0)
		str += formatIrcMessage(g_servername, "MODE", "#" + channelName + " +" + modeList, "");
	if (channelTopic.length() > 0)
	{
		str += formatIrcMessage(g_servername, RPL_TOPIC, nickname + " #" + channelName, channelTopic);
		str += formatIrcMessage(g_servername, RPL_TOPICWHOTIME, nickname + " #" + channelName + " " + g_channels[channelName].getTopicWhoTime(), "");
	}
	if (userList.empty())
		str += formatIrcMessage(g_servername, RPL_NAMREPLY, nickname + " = #" + channelName, "@" + nickname);
	else
		str += formatIrcMessage(g_servername, RPL_NAMREPLY, nickname + " = #" + channelName, nickname + " " + userList);
	str += formatIrcMessage(g_servername, RPL_ENDOFNAMES, nickname + " #" + channelName, "End of /NAMES list");
	return str;
}

static void _joinChannel(Client *client, string_t channelName, string_t key)
{
	char		firstChar;
	string_t	userList;

	firstChar = channelName[0];
	channelName.erase(0, 1);
	
	if (firstChar != '#' || channelName.empty())
		return client->sendMessage(formatIrcMessage(g_servername, ERR_BADCHANMASK, client->getNickname() + " " + firstChar + channelName, "Syntax error, invalid channel name"));
	else if (client->_channels.size() >= MAX_CHANNELS_PER_USER)
		return client->sendMessage(formatIrcMessage(g_servername, ERR_TOOMANYCHANNELS, client->getNickname() + " #" + channelName, "Too many channels"));
	else if (!containsOnlyAllowedChars(channelName))
		return client->sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHCHANNEL, client->getNickname() + " #" + channelName, "Channel name contains invalid characters"));
	
	transform(channelName.begin(), channelName.end(), channelName.begin(), tolower);
	
	if (g_channels.find(channelName) == g_channels.end())
		g_channels[channelName] = Channel(channelName);
	else
	{
		if (client->_channels.find(channelName) != client->_channels.end())
			return ;
		switch (g_channels[channelName].checkEligibilityToConnect(client, key))
		{
			case ERR_CHANNELISFULL:
				return client->sendMessage(formatIrcMessage(g_servername, ERR_CHANNELISFULL, client->getNickname() + " #" + channelName, "Cannot join channel (+l)"));
			case ERR_INVITEONLYCHAN:
				return client->sendMessage(formatIrcMessage(g_servername, ERR_INVITEONLYCHAN, client->getNickname() + " #" + channelName, "Cannot join channel (+i)"));
			case ERR_BADCHANNELKEY:
				return client->sendMessage(formatIrcMessage(g_servername, ERR_BADCHANNELKEY, client->getNickname() + " #" + channelName, "Cannot join channel (+k) - bad key"));
		}
	}
	
	userList = g_channels[channelName].getUserList();
	client->sendMessage(joinBurst(client, channelName, userList));
	g_channels[channelName].connect(client);
	client->_channels.insert(channelName);
	if (userList.empty())
		g_channels[channelName].op(client);
}

void	Client::JOIN(string_t content)
{
	std::deque<string_t>	splitedElements;
	std::deque<string_t>	channelNames;
	std::deque<string_t>	channelKeys;
	string_t				channelName;
	string_t				channelKey;
	size_t					pos;
	
	if (content.empty())
		return sendMessage(formatIrcMessage(g_servername, ERR_NEEDMOREPARAMS, this->_nickname + " " + "JOIN", "JOIN needs more parameters"));
	splitedElements = split(content, ",");

	while (splitedElements.size() > 0)
	{
		content = splitedElements.front();
		splitedElements.pop_front();
		pos = content.find_first_of(" \t");
		channelNames.push_back(content.substr(0, pos));
		if (pos != std::string::npos)
		{
			channelKeys.push_back(lTrim(content.substr(pos + 1)));
			while (splitedElements.size() > 0)
			{
				content = splitedElements.front();
				splitedElements.pop_front();
				channelKeys.push_back(content);
			}
			break ;
		}
	}

	while (channelNames.size() > 0)
	{
		channelName = channelNames.front();
		channelNames.pop_front();
		channelKey.clear();
		if (channelKeys.size() > 0)
		{
			channelKey = channelKeys.front();
			channelKeys.pop_front();
		}
		_joinChannel(this, channelName, channelKey);
	}
}
