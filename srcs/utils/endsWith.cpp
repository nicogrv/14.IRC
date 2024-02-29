/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endsWith.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 00:54:48 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/20 01:01:51 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.hpp"

/* ************************************************************************** */

bool	endsWith(const string_t &str, const string_t &suffix)
{
	if (str.length() < suffix.length())
		return false;
	else
		return str.substr(str.length() - suffix.length()) == suffix;
}
