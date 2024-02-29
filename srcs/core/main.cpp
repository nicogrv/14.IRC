/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:43:11 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/28 01:54:06 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/main.hpp"
#include "utils/utils.hpp"
#include "classes/Server.hpp"
#include "classes/Channel.hpp"
#include "classes/Client.hpp"
#include "core/signals.hpp"

/* ************************************************************************** */

int	main(int argc, char **argv)
{
	int				port;
	string_t		password;

	if (argc == 3)
	{
		port = portParsing(argv[1]);
		if (port == -1)
			return std::cerr << "Error: invalid port. [" << MIN_PORT << " - " << MAX_PORT << "]" << '\n', 1;
		password = argv[2];
	}
	else if (argc == 2)
	{
		port = 0;
		password = argv[1];
	}
	else
		return std::cerr << "Usage: ./" << EXECUTABLE << " [port] <password>" << '\n', 1;
	if (password.empty())
		return std::cerr << "Error: password cannot be empty" << '\n', 1;
	signalsHandler();
	g_servername = getMyHostname();
	g_serversion = "0.1";
	return !irc_serv(port, password);
}

bool	irc_serv(unsigned int port, string_t password)
{
	pollfd_t	pollfds[MAX_CLIENTS + 1];
	Client		clients[MAX_CLIENTS + 1];
	
	if (!Server::init(port, password))
		return false;
	
	for (size_t i = 0; i < MAX_CLIENTS + 1; i++)
	{
		clients[i] = Client();
		bzero(pollfds + i, sizeof(pollfd_t));
	}
	pollfds[0].fd = Server::sock;
    pollfds[0].events = POLLIN;

	g_pollfds = pollfds;
	g_clients = clients;
	
	std::cout << "----------------------------------------" << '\n';
	std::cout << "Launching " << RED << g_servername << NC << '\n';
	std::cout << "Port: " RED << Server::getPort() << NC ", Password: " RED << password << NC << '\n';
	std::cout << "Created on " RED << formatTime(Server::launchTime) << NC << '\n';
	std::cout << "Version: " RED << g_serversion << NC << '\n';
	std::cout << "----------------------------------------" << '\n';
	
	routine();

	Server::closeSocket();
	return true;
}

/* ************************************************************************** */

int	portParsing(string_t str)
{
	int		nbr;
	char	*ptr;

	nbr = std::strtod(str.c_str(), &ptr);
	if (nbr < MIN_PORT || nbr > MAX_PORT || ptr != (str.c_str() + str.length()))
		return -1;
	return nbr;	
}

/* GLOBALS ****************************************************************** */

Client						*g_clients = 0;
pollfd_t					*g_pollfds = 0;

std::map<string_t, Channel>	g_channels;
string_t					g_servername;
string_t					g_serversion;

/* ************************************************************************** */
