/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:33:04 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/28 14:17:03 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Client.hpp"
#include "classes/Channel.hpp"
#include "utils/ircNumerics.hpp"
#include "utils/utils.hpp"

/* ************************************************************************** */

bool checkIsGroup(string_t &content)
{
	if (content[0] != '#')
		return false;
	content = content.substr(1);
	return true;
}

bool checkIsAddress(string_t &content, Client &client)
{
	size_t		pos;

	pos = content.find("@");
	if (pos != std::string::npos)
	{
		string_t name = content.substr(0, pos);
		if (client.nicknames.find(name) == client.nicknames.end() || (content.substr(pos+1) != client.nicknames[name]->getIdentity()))
		{
			client.sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHNICK, client.getNickname() + " " + content, "No such nickname"));
			return false;
		}
		content = name;
	}
	return true;
}


void sendUser(string_t name, string_t msg, Client &client)
{
	if (client.nicknames.find(name) == client.nicknames.end())
		return client.sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHNICK, client.getNickname() + " " + name, "No such nickname"));
	else
		client.nicknames[name]->sendMessage(formatIrcMessage(client.getFullname(), "PRIVMSG", name, msg));
}

void sendGroup(string_t name, string_t msg, Client &client)
{
	if (g_channels.find(name) != g_channels.end())
	{
		if (g_channels[name].isConnected(&client))
			g_channels[name].sendMessage(&client, formatIrcMessage(client.getFullname(), "PRIVMSG", "#" + name, msg));
		else
			client.sendMessage(formatIrcMessage(g_servername, ERR_CANNOTSENDTOCHAN, client.getNickname() + " #" + name, "Cannot send to channel"));
	}
	else
		client.sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHCHANNEL, client.getNickname() + " #" + name, "No such channel"));
}

void parsingReceiver(string_t content, string_t msg, Client &client)
{
	bool		isChannelName;
	
	content = trim(content);
	if (content.empty())
		return ;
	isChannelName = checkIsGroup(content);
	if(!checkIsAddress(content, client))
		return ;
	transform(content.begin(), content.end(), content.begin(), tolower);
	isChannelName ? sendGroup(content, msg, client) : sendUser(content, msg, client);
}

void	Client::PRIVMSG(string_t content)
{
	string_t	name;
	size_t		pos;
	string_t	msg;
	if (content.length() <= 2)
		return sendMessage(formatIrcMessage(g_servername, ERR_NEEDMOREPARAMS, this->_nickname + " " + "PRIVMSG", "PRIVMSG needs more parameters"));	
	if (trim(content)[0] == ':')
		return sendMessage(formatIrcMessage(g_servername, ERR_NORECIPIENT, this->_nickname, "PRIVMSG needs a destinatair"));	
	pos = content.find(':');
	if (pos == std::string::npos)
		return sendMessage(formatIrcMessage(g_servername, ERR_NOTEXTTOSEND, this->_nickname, "PRIVMSG needs a messages"));	
	msg = content.substr(pos + 1);
	content = content.substr(0, pos - 1);
	while (true)
	{
			pos = content.find(',');
		if (pos == std::string::npos)
		{
			parsingReceiver(content, msg, *this);
			break ;
		}
		parsingReceiver(content.substr(0, pos), msg, *this);
		content = content.substr(pos+1);
	}
}
