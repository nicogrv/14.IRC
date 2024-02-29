/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:54:14 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/12 14:58:04 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_HPP
	#define TYPES_HPP
	
/* INCLUDES ***************************************************************** */

	#include <string>
	#include <iostream>
	#include <cstring>
	#include <algorithm>
	#include <cctype>
	#include <ctime>
	#include <sstream>
	#include <stdexcept>
	#include <cstdlib>
	#include <errno.h>
	#include <poll.h>
	#include <sys/types.h>
	#include <arpa/inet.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <unistd.h>
	#include <netdb.h>
	#include <sys/time.h>
	#include <bits/stdc++.h> 

	class Server;
	class Client;
	class Channel;

/* DEFINES ****************************************************************** */

	#ifndef EXECUTABLE
		#define EXECUTABLE "ircserv"
	#endif
	#define TIMEOUTSEC 300
	#define MAX_CLIENTS 3
	#define GUEST "anonymous"
	#define MIN_PORT 1024
	#define MAX_PORT 65535

/* COLORS ******************************************************************* */

	#define RED "\033[0;31m"
	#define GREEN "\033[0;32m"
	#define ORANGE "\033[0;33m"
	#define BLUE "\033[0;34m"
	#define MAGENTA "\033[35m"
	#define CYAN "\033[36m"
	#define BOLD "\033[1m"
	#define NC "\033[0m"

/* TYPEDEFS ***************************************************************** */

	typedef struct sockaddr 	sockaddr_t;
	typedef struct sockaddr_in6	sockaddr_in6_t;
	typedef struct sockaddr_in	sockaddr_in_t;
	typedef struct pollfd		pollfd_t;
	typedef int					socket_t;
	typedef	std::string			string_t;

/* STRUCTURES *************************************************************** */

	typedef struct s_message
	{
		string_t	command;
		string_t	content;
	}	Message;

	typedef struct s_ircResponse
	{
		string_t	numeric;
		string_t	content;
	}	IrcResponse;

/* GLOBALS ****************************************************************** */

	extern Client						*g_clients;
	extern pollfd_t						*g_pollfds;

	extern std::map<string_t, Channel>	g_channels;
	extern string_t						g_servername;
	extern string_t						g_serversion;

/* ************************************************************************** */

#endif
