/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getMyHostname.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 00:56:11 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/20 05:20:19 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.hpp"

/* ************************************************************************** */

string_t	getMyHostname()
{
    char hostname[256];

    if (gethostname(hostname, sizeof(hostname)) == 0)
		  return hostname;
    return "ircserv";
}
