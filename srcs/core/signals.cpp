/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:57:27 by tchevrie          #+#    #+#             */
/*   Updated: 2024/02/28 02:04:34 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/signals.hpp"
#include <csignal>
#include <cstring>
#include <iostream>

/* ************************************************************************** */

static void _sigintHandler(int signum)
{
	(void)	signum;
}

static void _sigtermHandler(int signum)
{
	(void)	signum;
}

static void _sighupHandler(int signum)
{
	(void)	signum;
}

int signalsHandler()
{
	struct sigaction sigint_action;
	struct sigaction sigterm_action;
	struct sigaction sighup_action;

	sigint_action.sa_handler = _sigintHandler;
	sigemptyset(&sigint_action.sa_mask);
	sigint_action.sa_flags = 0;
	sigaction(SIGINT, &sigint_action, NULL);

	sigterm_action.sa_handler = _sigtermHandler;
	sigemptyset(&sigterm_action.sa_mask);
	sigterm_action.sa_flags = 0;
	sigaction(SIGTERM, &sigterm_action, NULL);

	sighup_action.sa_handler = _sighupHandler;
	sigemptyset(&sighup_action.sa_mask);
	sighup_action.sa_flags = 0;
	sigaction(SIGTERM, &sighup_action, NULL);
	return 0;
}
