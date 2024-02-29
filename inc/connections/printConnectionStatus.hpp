/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printConnectionStatus.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 00:37:09 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/20 00:40:25 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTCONNECTIONSTATUS_HPP
    #define PRINTCONNECTIONSTATUS_HPP

    class Client;

/* ************************************************************************** */

void    printConnectionStatus(unsigned char connStatus, const Client &client);

/* ************************************************************************** */

#endif
