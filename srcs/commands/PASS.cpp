/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:18:52 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/28 00:59:00 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Client.hpp"
#include "classes/Server.hpp"
#include "utils/ircNumerics.hpp"
#include "utils/utils.hpp"

/* ************************************************************************** */

bool	Client::PASS(string_t passphrase)
{
	if (this->_authenticated)
		return sendMessage(formatIrcMessage(g_servername, "NOTICE", this->_nickname, "You have already authenticated")), true;
	if (passphrase.compare(Server::getPassword()) != 0)
	{
		std::cout << "----------------------------------------" << '\n';
		sendMessage(formatIrcMessage(g_servername, ERR_PASSWDMISMATCH, this->_nickname, "Passwords don't match"));
		this->disconnect();
		return false;
	}
	this->_authenticated = true;
	return true;
}
