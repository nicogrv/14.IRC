/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callCorrespondingCommand.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:12:44 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/28 12:03:55 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/callCorrespondingCommand.hpp"
#include "core/routine.hpp"
#include "classes/Client.hpp"
#include "utils/ircNumerics.hpp"
#include "utils/utils.hpp"

/* ************************************************************************** */

static void _printLine(const Client &client, const Message &message)
{
	string_t	tmp;
	if (client.getNickname().empty())
		std::cout << "(" << RED << "CLIENT " << client.getIndex() << NC ") ";
	else
		std::cout << "(" << RED << client.getNickname() << NC ") ";
	std::cout << MAGENTA << message.command << " " << message.content << NC << '\n';
	
	tmp = client.getUsername();
	if (tmp.length() > 0)
		std::cout << " username: " << tmp << '\n';
	
	tmp = client.getRealname();
	if (tmp.length() > 0)
		std::cout << " realname: " << tmp << '\n';
	
	tmp = client.getIdentity();
	if (tmp.compare(client.getName()) == 0)
		std::cout << " host: " << tmp << " [" << client.getIp() << "]" << '\n';
	else
		std::cout << " host: " << tmp << '\n';
}

void	callCorrespondingCommand(Client &client, Message message)
{
	_printLine(client, message);
	if (message.command.empty());
	else if (message.command.compare("QUIT") == 0)
	{
		std::cout << "----------------------------------------" << '\n';
		client.disconnect();
		return ;
	}
	else if (message.command.compare("PASS") == 0)
	{
		if (!client.PASS(message.content))
			return ;
	}
	else if (message.command.compare("CAP") == 0)
		client.CAP(message.content);
	else if (message.command.compare("USER") == 0)
		client.USER(message.content);
	else if (!(client.isAuthenticated()))
		client.sendMessage(formatIrcMessage(g_servername, ERR_NOTREGISTERED, GUEST, "You must first authenticate"));
	else if (message.command.compare("NICK") == 0)
		client.NICK(message.content);
	else if (client.getNickname().empty())
		client.sendMessage(formatIrcMessage(g_servername, ERR_NONICKNAMEGIVEN, GUEST, "You must first set a nickname"));
	else if (message.command.compare("PING") == 0)
		client.PING(message.content);
	else if (message.command.compare("JOIN") == 0)
		client.JOIN(message.content);
	else if (message.command.compare("PART") == 0)
		client.PART(message.content);
	else if (message.command.compare("KICK") == 0)
		client.KICK(message.content);
	else if (message.command.compare("PRIVMSG") == 0)
		client.PRIVMSG(message.content);
	else if (message.command.compare("TOPIC") == 0)
		client.TOPIC(message.content);
	else if (message.command.compare("INVITE") == 0)
		client.INVITE(message.content);
	else if (message.command.compare("MODE") == 0)
		client.MODE(message.content);
	std::cout << "----------------------------------------" << '\n';
}
