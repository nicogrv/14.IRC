/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:42:18 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/20 01:01:51 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
	#define SERVER_HPP
	#include "utils/utils.hpp"

/* NON INSTANCIABLE CLASS *************************************************** */

class Server
{
	public:
		static bool					init(uint16_t port_, string_t password_);
		static void					closeSocket();
		static uint16_t				getPort();
		static string_t				getPassword();

		static const std::time_t	launchTime;
		static socket_t				sock;
		static sockaddr_in6_t		sin6;

	private:
		virtual ~Server() 			= 0;
		static bool					initSocket();
		static bool					initBind(bool useClosestAvailablePort);
		static bool					initListen();

		static uint16_t				port;
		static string_t				password;
};

/* ************************************************************************** */

#endif
