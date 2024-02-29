/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CAP.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:26:26 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/26 18:53:41 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Client.hpp"
#include "utils/utils.hpp"

/* ************************************************************************** */

void	Client::CAP(string_t content)
{
	if (content.length() >= 2 && content[0] == 'L' && content[1] == 'S')
		sendMessage(formatIrcMessage(g_servername, "CAP * LS", this->_nickname, "none"));
}
