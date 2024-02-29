/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safeStrtoi.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 00:00:26 by tchevrie          #+#    #+#             */
/*   Updated: 2024/02/26 00:12:24 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.hpp"

/* ************************************************************************** */

int	safeStrtoi(string_t str)
{
	long	nbr;
	int		index;
	int		sign;

	nbr = 0;
	if (str.length() == 1 && (str.c_str()[0] == '-' || str.c_str()[0] == '+'))
		return false;
	else if (str.c_str()[0] == '-')
	{
		sign = -1;
		str = str.c_str() + 1;
	}
	else
	{
		sign = 1;
		if (str.c_str()[0] == '+')
			str = str.c_str() + 1;
	}

	index = 0;
	while ('0' <= str.c_str()[index] && str.c_str()[index] <= '9')
	{
		nbr = nbr * 10 + str.c_str()[index] - '0';
		if (nbr > 2147483648)
			return 0;
		index++;
	}

	nbr = nbr * sign;
	if (-2147483648 <= nbr && nbr <= 2147483647 && str.c_str()[index] == '\0')
		return nbr;
	else
		return 0;
}
