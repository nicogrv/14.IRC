/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleNewConnection.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:53:09 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/28 13:56:13 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connections/handleNewConnection.hpp"
#include "connections/printConnectionStatus.hpp"
#include "classes/Client.hpp"
#include "classes/Server.hpp"
#include "utils/types.hpp"

/* ************************************************************************** */

static void	rejectConn()
{
	Client		client;
	socket_t	clientFd;

	client.len = sizeof(client.addr);
	clientFd = accept(Server::sock, reinterpret_cast<sockaddr_t *>(&client.addr), &client.len);
	if (clientFd == -1)
		return printError("accept");
	client.setIdentity();
	printConnectionStatus('!', client);
	close(clientFd);
}

static void	acceptConn(Client &client, int index)
{
	pollfd_t	&pollfd = g_pollfds[index];

	client.len = sizeof(client.addr);
	pollfd.fd = accept(Server::sock, (sockaddr_t *)&(client.addr), &(client.len));
	if (pollfd.fd == -1)
		return printError("accept");
	pollfd.events = POLLIN;
	client.setIndex(index);
	client.setIdentity();
	printConnectionStatus('+', client);
}

void	handleNewConnection(Client *clients)
{
	pollfd_t	*pollfds = g_pollfds;
	int 		index;

	for (index = 1; index < MAX_CLIENTS + 1; ++index)
	{
		if (pollfds[index].fd == 0)
			return acceptConn(clients[index], index);
	}
	if (index == MAX_CLIENTS + 1)
		rejectConn();
}
