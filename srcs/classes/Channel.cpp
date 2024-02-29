/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 01:46:34 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/28 14:50:17 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Channel.hpp"
#include "classes/Client.hpp"
#include "utils/ircNumerics.hpp"

/* COMPULSORY MEMBERS OF THE ORTHODOX CANONICAL CLASS *********************** */

Channel::Channel() : _inviteOnly(false), _topicRestricted(false), _userLimit(0)
{
}

Channel::Channel(const Channel &copy)
{
	*this = copy;
}

Channel &Channel::operator=(const Channel &copy)
{
	this->_name = copy._name;
	this->_topic = copy._topic;
	this->_whoChangedTopic = copy._whoChangedTopic;
	this->_timeTopicChanged = copy._timeTopicChanged;
	
	this->_channelKey = copy._channelKey;
	this->_inviteOnly = copy._inviteOnly;
	this->_topicRestricted = copy._topicRestricted;
	this->_userLimit = copy._userLimit;

	return *this;
}

Channel::~Channel()
{
}

/* ADDITIONNAL CONSTRUCTOR *************************************************** */

Channel::Channel(string_t channelName) : _name(channelName), _inviteOnly(false), _topicRestricted(false), _userLimit(0)
{
}

/* CHANNEL CONNECTIONS ****************************************************** */

bool	Channel::connect(Client *client)
{
	if (this->_inviteOnly && this->_invitedUsers.find(client) != this->_invitedUsers.end())
		this->_invitedUsers.erase(client);
	if (this->_users.find(client) == this->_users.end())
		this->_users[client] = ISNOTOP;
	return true;
}

void	Channel::disconnect(Client *client)
{
	if (this->_users.find(client) != this->_users.end())
		this->_users.erase(client);
}

/* ************************************************************************** */

void	Channel::sendMessage(Client *client, string_t content)
{
	std::map<Client *, bool>::iterator it;

	for (it = this->_users.begin(); it != this->_users.end(); it++)
	{
		if (it->first != client)
			(it->first)->sendMessage(content);
	}
}

/* SETTERS ****************************************************************** */

void	Channel::setName(string_t name)
{
	this->_name = name;
}

void	Channel::setTopic(Client *client, string_t topic)
{
	this->_topic = topic;
	this->_whoChangedTopic = client->getNickname();
	this->_timeTopicChanged = std::time(NULL);
}

void	Channel::op(Client *client)
{
	std::map<Client *, bool>::iterator it;

	it = this->_users.find(client);
	if (it != this->_users.end())
		it->second = ISOP;
}

void	Channel::deop(Client *client)
{
	std::map<Client *, bool>::iterator it;

	it = this->_users.find(client);
	if (it != this->_users.end())
		it->second = ISNOTOP;
}

void	Channel::setInviteOnly(bool value)
{
	this->_inviteOnly = value;
}

void	Channel::setTopicRestricted(bool value)
{
	this->_topicRestricted = value;
}

void	Channel::setChannelKey(string_t key)
{
	this->_channelKey = key;
}

void	Channel::setUserLimit(unsigned short limit)
{
	this->_userLimit = limit;
}

void	Channel::invite(Client *client)
{
	this->_invitedUsers[client] = std::time(0);
}

/* GETTERS ****************************************************************** */

string_t	Channel::getTopic() const
{
	return this->_topic;
}

const std::map<Client *, bool>	&Channel::getUsers() const
{
	return this->_users;
}

string_t	Channel::getName() const
{
	return this->_name;
}

string_t	Channel::getUserList() const
{
	std::ostringstream							oss;
	std::map<Client *, bool>::const_iterator	it;

	for (it = this->_users.begin(); it != this->_users.end(); ++it)
	{
		if (it != this->_users.begin())
			oss << ' ';
		if (it->second == ISOP)
			oss << '@';
		oss << it->first->getNickname();
	}
	return oss.str();
}

bool	Channel::isOp(Client *client) const
{
	std::map<Client *, bool>::const_iterator it;

	it = this->_users.find(client);
	if (it != this->_users.end())
		return it->second;
	return false;
}

bool	Channel::isConnected(Client *client) const
{
	std::map<Client *, bool>::const_iterator it;

	it = this->_users.find(client);
	if (it != this->_users.end())
		return true;
	return false;
}

string_t	Channel::getTopicWhoTime() const
{
	std::ostringstream	oss;

	oss << this->_whoChangedTopic << " " <<this->_timeTopicChanged;
	return oss.str();
}

bool	Channel::isInviteOnly() const
{
	return this->_inviteOnly;
}

bool	Channel::isTopicRestricted() const
{
	return this->_topicRestricted;
}

string_t	Channel::getChannelKey() const
{
	return this->_channelKey;
}

int	Channel::checkEligibilityToConnect(Client *client, string_t key) const
{
	if (client->isOperator())
		return 0;
	if (this->_userLimit != 0 && this->_users.size() >= this->_userLimit)
		return ERR_CHANNELISFULL;
	if (this->_inviteOnly && (this->_invitedUsers.find(client) == this->_invitedUsers.end() || std::time(0) > (this->_invitedUsers.at(client) + 300)))
		return ERR_INVITEONLYCHAN;
	if (this->_channelKey.length() > 0 && key.compare(this->_channelKey) != 0)
		return ERR_BADCHANNELKEY;
	return 0;
}

unsigned short	Channel::getUserLimit() const
{
	return this->_userLimit;
}

string_t	Channel::getModeList() const
{
	string_t	list;

	if (this->_inviteOnly)
		list += "i";
	if (this->_topicRestricted)
		list += "t";
	if (this->_channelKey.length() > 0)
		list += "k";
	if (this->_userLimit != 0)
		list += "l";
	return list;	
}

