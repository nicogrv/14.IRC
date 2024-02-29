/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 00:55:08 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/20 01:01:51 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.hpp"

/* ************************************************************************** */

string_t	lTrim(string_t str)
{
	std::string::size_type first;

	first = str.find_first_not_of(" \t");
	if (first == std::string::npos) // If the string is all whitespace
		return "";
	return str.substr(first);
}

string_t	rTrim(string_t str)
{
	std::string::size_type last;

	last = str.find_last_not_of(" \t");
	if (last == std::string::npos)
		return "";
	return str.substr(0, last + 1);
}

string_t	trim(string_t str)
{
	str = lTrim(str);
	str = rTrim(str);
	return str;
}
