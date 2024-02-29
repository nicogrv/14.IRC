/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callCorrespondingCommand.hpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:13:38 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/20 01:17:26 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALLCORRESPONDINGCOMMAND_HPP
    #define CALLCORRESPONDINGCOMMAND_HPP

    class Client;
    typedef struct s_message Message;

/* ************************************************************************** */

void	callCorrespondingCommand(Client &client, Message message);

/* ************************************************************************** */

#endif
