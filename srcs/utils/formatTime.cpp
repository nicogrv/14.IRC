/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatTime.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 00:55:51 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/20 01:01:51 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.hpp"

/* ************************************************************************** */

string_t	formatTime(std::time_t givenTime)
{
	std::tm	*now;
    char 	buffer[80];
	
	now = std::localtime(&givenTime);
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", now);
	return buffer;
}
