/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   containsOnlyAllowedChars.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 00:56:29 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/20 01:01:51 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.hpp"

/* ************************************************************************** */

bool	containsOnlyAllowedChars(string_t str)
{
	size_t	len;

	len = str.length();
	for (size_t i = 0; i < len; i++)
	{
		if (!isalnum(str[i]) && str[i] != '-' && str[i] != '_')
			return false;
	}
	return true;
}
