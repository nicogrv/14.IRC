/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:32:20 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/28 14:34:40 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Client.hpp"
#include "classes/Channel.hpp"
#include "utils/ircNumerics.hpp"
#include "utils/utils.hpp"

/* ************************************************************************** */

static void	_modifyChannelModes(Client *client, Channel &channel, string_t content)
{
	char		operation;
	size_t		pos;
	string_t	modes;
	string_t	parameter;

	operation = content[0];
	content = lTrim(content.substr(1));
	if (operation != '+' && operation != '-')		
		return client->sendMessage(formatIrcMessage(g_servername, ERR_UNKNOWNMODE, client->getNickname() + " #" + channel.getName(), "Syntax error, unknown symbol"));
	else if (content.empty())
		return client->sendMessage(formatIrcMessage(g_servername, ERR_NEEDMOREPARAMS, client->getNickname() + "MODE", "MODE needs more parameters"));
	pos = content.find_first_of(" \t");
	modes = content.substr(0, pos);
	if (pos != std::string::npos)
		parameter = lTrim(content.substr(pos + 1));

	switch (operation)
	{
		case '+':
			for (size_t i = 0; modes[i]; i++)
			{
				switch (modes[i])
				{
					case 'i':
						channel.setInviteOnly(true);
						channel.sendMessage(NULL, formatIrcMessage(client->getFullname(), "MODE", "#" + channel.getName() + " +" + modes.substr(i, 1), ""));
						break ;
					case 't':
						channel.setTopicRestricted(true);
						channel.sendMessage(NULL, formatIrcMessage(client->getFullname(), "MODE", "#" + channel.getName() + " +" + modes.substr(i, 1), ""));
						break ;
					case 'k':
						if (parameter.empty())
							client->sendMessage(formatIrcMessage(client->getFullname(), ERR_NEEDMOREPARAMS, client->getNickname() + "MODE", "MODE needs more parameters (+k)"));
						else
						{
							channel.setChannelKey(parameter);
							channel.sendMessage(NULL, formatIrcMessage(client->getFullname(), "MODE", "#" + channel.getName() + " +" + modes.substr(i, 1), ""));
							break ;
						}
						modes.erase(i--, 1);
						break ;
					case 'o':
						if (parameter.empty())
							client->sendMessage(formatIrcMessage(g_servername, ERR_NEEDMOREPARAMS, client->getNickname() + "MODE", "MODE needs more parameters (+o)"));
						else if (Client::nicknames.find(parameter) == Client::nicknames.end())
							client->sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHNICK, client->getNickname() + " " + parameter, "No such nick"));
						else if (!channel.isConnected(Client::nicknames[parameter]))
							client->sendMessage(formatIrcMessage(g_servername, ERR_NOTONCHANNEL, client->getNickname() + " " + parameter, "User not on channel"));
						else
						{
							channel.op(Client::nicknames[parameter]);
							channel.sendMessage(NULL, formatIrcMessage(client->getFullname(), "MODE", "#" + channel.getName() + " +" + modes.substr(i, 1) + " " + parameter, ""));
							break ;
						}
						modes.erase(i--, 1);
						break ;
					case 'l':
						if (parameter.empty())
							client->sendMessage(formatIrcMessage(g_servername, ERR_NEEDMOREPARAMS, client->getNickname() + "MODE", "MODE needs more parameters (+l)"));
						else
						{
							channel.setUserLimit(safeStrtoi(parameter));
							channel.sendMessage(NULL, formatIrcMessage(client->getFullname(), "MODE", "#" + channel.getName() + " +" + modes.substr(i, 1), ""));
							break ;
						}
						modes.erase(i--, 1);
						break ;
					default:
						modes.erase(i--, 1);
				}
			}
			break ;
		case '-':
			for (size_t i = 0; modes[i]; i++)
			{
				switch (modes[i])
				{
					case 'i':
						channel.setInviteOnly(false);
						channel.sendMessage(NULL, formatIrcMessage(client->getFullname(), "MODE", "#" + channel.getName() + " -" + modes.substr(i, 1), ""));
						break ;
					case 't':
						channel.setTopicRestricted(false);
						channel.sendMessage(NULL, formatIrcMessage(client->getFullname(), "MODE", "#" + channel.getName() + " -" + modes.substr(i, 1), ""));
						break ;
					case 'k':
						channel.setChannelKey("");
						channel.sendMessage(NULL, formatIrcMessage(client->getFullname(), "MODE", "#" + channel.getName() + " -" + modes.substr(i, 1), ""));
						break ;
					case 'o':
						if (parameter.empty())
							client->sendMessage(formatIrcMessage(g_servername, ERR_NEEDMOREPARAMS, client->getNickname() + "MODE", "MODE needs more parameters (+o)"));
						else if (Client::nicknames.find(parameter) == Client::nicknames.end())
							client->sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHNICK, client->getNickname() + " " + parameter, "No such nick"));
						else if (!channel.isConnected(Client::nicknames[parameter]))
							client->sendMessage(formatIrcMessage(g_servername, ERR_NOTONCHANNEL, client->getNickname() + " " + parameter, "User not on channel"));
						if (parameter.compare(client->getNickname()) != 0 && client->isOperator() == false)
							client->sendMessage(formatIrcMessage(g_servername, ERR_CHANOPRIVSNEEDED, client->getNickname() + " #" + channel.getName(), "Not enough permissions"));
						else
						{
							channel.deop(Client::nicknames[parameter]);
							channel.sendMessage(NULL, formatIrcMessage(client->getFullname(), "MODE", "#" + channel.getName() + " -" + modes.substr(i, 1) + " " + parameter, ""));
							break ;
						}
						modes.erase(i--, 1);
						break ;
					case 'l':
						channel.setUserLimit(0);
						channel.sendMessage(NULL, formatIrcMessage(client->getFullname(), "MODE", "#" + channel.getName() + " -" + modes.substr(i, 1), ""));
						break ;
					default:
						modes.erase(i--, 1);
				}
			}
			break ;
	}
}


static void	_modifyUserModes(Client *client, Client *user, string_t content)
{
	char		operation;
	size_t		pos;
	string_t	modes;

	operation = content[0];
	content = lTrim(content.substr(1));
	if (operation != '+' && operation != '-')		
		return client->sendMessage(formatIrcMessage(g_servername, ERR_UNKNOWNMODE, client->getNickname() + " " + user->getNickname(), "Syntax error, unknown symbol"));
	else if (content.empty())
		return client->sendMessage(formatIrcMessage(g_servername, ERR_NEEDMOREPARAMS, client->getNickname() + "MODE", "MODE needs more parameters"));
	pos = content.find_first_of(" \t");
	modes = content.substr(0, pos);

	switch (operation)
	{
		case '+':
			for (size_t i = 0; modes[i]; i++)
			{
				switch (modes[i])
				{
					case 'o':
						if (client != user && !client->isOperator())
							client->sendMessage(formatIrcMessage(g_servername, ERR_CHANOPRIVSNEEDED, client->getNickname() + " " + user->getNickname(), "You're not operator"));
						else if (client == user && ((string_t)"127.0.0.1").compare(client->getIp()) != 0 && ((string_t)"::ffff:127.0.0.1").compare(client->getIp()) != 0 && ((string_t)"::1").compare(client->getIp()) != 0);
						else
						{
							user->setOperator(true);
							client->sendMessage(formatIrcMessage(client->getFullname(), "MODE", client->getNickname() + " +" + modes.substr(i, 1) + " " + user->getNickname(), ""));
							if (user != client)
								user->sendMessage(formatIrcMessage(client->getFullname(), "MODE", client->getNickname() + " +" + modes.substr(i, 1) + " " + user->getNickname(), ""));
							break ;
						}
						modes.erase(i--, 1);
						break ;
					default:
						modes.erase(i--, 1);
				}
			}
			break ;
		case '-':
			for (size_t i = 0; modes[i]; i++)
			{
				switch (modes[i])
				{
					case 'o':
						if (!client->isOperator())
							client->sendMessage(formatIrcMessage(g_servername, ERR_CHANOPRIVSNEEDED, client->getNickname() + " " + user->getNickname(), "You're not operator"));
						else
						{
							user->setOperator(false);
							client->sendMessage(formatIrcMessage(client->getFullname(), "MODE", client->getNickname() + " -" + modes + " " + user->getNickname(), ""));
							if (user != client)
								user->sendMessage(formatIrcMessage(client->getFullname(), "MODE", client->getNickname() + " -" + modes + " " + user->getNickname(), ""));
							break ;
						}
						modes.erase(i--, 1);
						break ;
					default:
						modes.erase(i--, 1);
				}
			}
			break ;
	}
}

void	Client::MODE(string_t content)
{
	string_t	name;
	bool		isChannel;
	size_t		pos;

	if (content.empty())
		return sendMessage(formatIrcMessage(g_servername, ERR_NEEDMOREPARAMS, this->_nickname + "MODE", "MODE needs more parameters"));
	
	pos = content.find_first_of(" \t");

	if (content[0] == '#')
	{
		name = content.substr(1, pos - 1);
		isChannel = true;
	}
	else
	{
		name = content.substr(0, pos);
		isChannel = false;
	}
	
	if (isChannel)
	{
		if (name.empty())
			return sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHCHANNEL, this->_nickname + " #", "Syntax error, no channel name is given"));
		else if (g_channels.find(name) == g_channels.end())
			return sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHCHANNEL, this->_nickname + " #" + name, "No such channel"));
		else if (!g_channels[name].isConnected(this))
			return sendMessage(formatIrcMessage(g_servername, ERR_NOTONCHANNEL, this->_nickname + " #" + name, "You're not on channel"));
		else if (pos == std::string::npos)
			return sendMessage(formatIrcMessage(g_servername, RPL_CHANNELMODEIS, this->_nickname + " #" + name, "+" + g_channels[name].getModeList()));
		else if (!g_channels[name].isOp(this) && !this->isOperator())
			return sendMessage(formatIrcMessage(g_servername, ERR_CHANOPRIVSNEEDED, this->_nickname + " #" + name, "You're not channel operator"));
		_modifyChannelModes(this, g_channels[name], lTrim(content.substr(pos + 1)));
	}
	else
	{
		if (name.empty())
			return sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHNICK, this->_nickname, "Syntax error, no nickname is given"));
		else if (Client::nicknames.find(name) == Client::nicknames.end())
			return sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHNICK, this->_nickname + " " + name, "No such nick"));
		else if (pos == std::string::npos)
			return sendMessage(formatIrcMessage(g_servername, RPL_UMODEIS, this->_nickname + " " + name, "+" + Client::nicknames[name]->getModeList()));
		_modifyUserModes(this, Client::nicknames[name], lTrim(content.substr(pos + 1)));
	}
	
}
