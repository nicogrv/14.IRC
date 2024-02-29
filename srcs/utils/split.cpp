/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:45:55 by tchevrie          #+#    #+#             */
/*   Updated: 2024/02/26 19:55:58 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.hpp"
#include <deque>

/* ************************************************************************** */

std::deque<string_t>	split(string_t str, string_t splitChars)
{
	std::deque<string_t>	container;
	string_t				splited;
	size_t					pos;

	while (1)
	{
		pos = str.find_first_of(splitChars);
		splited = trim(str.substr(0, pos));
		if (splited.length() > 0)
			container.push_back(splited);
		if (pos == std::string::npos)
			break ;
		str = str.substr(pos + 1);
	}
	return container;
}
