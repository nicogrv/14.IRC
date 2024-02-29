/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:49:28 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/28 12:08:49 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Server.hpp"

/* STATIC VARIABLES ********************************************************* */

const std::time_t	Server::launchTime = std::time(0);
uint16_t			Server::port;
string_t			Server::password;
socket_t			Server::sock;
sockaddr_in6_t		Server::sin6;

/* INITIALISATION *********************************************************** */

bool	Server::init(uint16_t port_, string_t password_)
{
	if (port_ == 0)
		port = MIN_PORT;
	else
		port = port_;
	password = password_;
	sin6.sin6_family = AF_INET6;
	sin6.sin6_addr = in6addr_any;
	sin6.sin6_port = htons(port);
	sock = -1;
	if (!initSocket() || !initBind(!port_) || !initListen())
	{
		closeSocket(); 
		return false;
	}
	return true;
}

bool	Server::initSocket()
{
	sock = socket(AF_INET6, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_TCP);
	if (sock == -1)
		return printError("socket"), false;
	return true;
}

bool	Server::initBind(bool useClosestAvailablePort)
{
	int	result;

	while (1)
	{
		result = bind(sock, (sockaddr_t *)&(sin6), sizeof(sin6));
		if (result == 0)
			return true;
		else if (!useClosestAvailablePort || port == 65535)
			return printError("bind"), false;
		else
		{
			port++;
			sin6.sin6_port = htons(port);
		}
	}
}

bool	Server::initListen()
{
	if (sock == -1 || listen(sock, SOMAXCONN) == -1)
		return printError("listen"), false;
	return true;
}

/* GETTERS ******************************************************************* */

uint16_t	Server::getPort()
{
	return port;
}

string_t	Server::getPassword()
{
	return password;
}

/* END OF PROGRAM ************************************************************ */

void	Server::closeSocket()
{
	if (sock != -1)
		close(sock);
	sock = -1;
}

/* ************************************************************************** */
