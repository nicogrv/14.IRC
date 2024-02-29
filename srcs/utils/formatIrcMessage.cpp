/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatIrcMessage.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 03:04:13 by tchevrie          #+#    #+#             */
/*   Updated: 2024/02/27 18:58:17 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.hpp"

/* ************************************************************************** */

string_t	formatIrcMessage(string_t prefix, string_t command, string_t params, string_t trailing)
{
	string_t	ircMessage;

	if (prefix.length() > 0)
		ircMessage += ":" + prefix + " ";
	transform(command.begin(), command.end(), command.begin(), toupper);
	if (command.empty())
		command = "-";
	ircMessage += command + " ";
	if (params.length() > 0)
		ircMessage += params + " ";
	if (trailing.length() > 0)
		ircMessage += ":" + trailing;
	ircMessage += "\n";
	return ircMessage;
}

string_t	formatIrcMessage(string_t prefix, unsigned int code, string_t params, string_t trailing)
{
	std::ostringstream	oss;

	oss << std::setw(3) << std::setfill('0') << code;
	return formatIrcMessage(prefix, oss.str(), params, trailing);
}
