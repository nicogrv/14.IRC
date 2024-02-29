/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:24:52 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/20 01:40:32 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.hpp"
#include "classes/Client.hpp"

/* ************************************************************************** */

void	Client::USER(string_t content)
{
	string_t			username;
	string_t			realname;
	size_t				pos;

	pos = content.find_first_of(" \t");
	if (pos == std::string::npos)
		return ;
	username = content.substr(0, pos);
	content = lTrim(content.substr(pos));

	pos = content.find_first_of(" \t");
	if (pos == std::string::npos)
		return ;
	// hostname = content.substr(0, pos);
	content = lTrim(content.substr(pos));

	pos = content.find_first_of(" \t");
	if (pos == std::string::npos)
		return ;
	// servname = content.substr(0, pos);
	content = lTrim(content.substr(pos));

	if (content.c_str()[0] != ':')
		return ;
	realname = rTrim(content.substr(1));
	if (!realname.length())
		return ;
	this->_username = username;
	this->_realname = realname;
}
