/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:48:31 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/26 21:30:24 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
	#define UTILS_HPP
	#include "utils/types.hpp"

/* ************************************************************************** */

bool		containsOnlyAllowedChars(string_t str);

bool 		endsWith(const string_t &str, const string_t &suffix);

string_t	formatIrcMessage(string_t prefix, string_t command, string_t params, string_t trailing);
string_t	formatIrcMessage(string_t prefix, unsigned int code, string_t params, string_t trailing);

string_t	formatTime(std::time_t givenTime);

string_t	getMyHostname();

void		printError(string_t str);

int			safeStrtoi(string_t str);

std::deque<string_t>	split(string_t str, string_t splitChars);

string_t	lTrim(string_t str);
string_t	rTrim(string_t str);
string_t	trim(string_t str);

/* ************************************************************************** */

#endif