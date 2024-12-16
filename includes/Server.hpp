/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:39:31 by lbroms            #+#    #+#             */
/*   Updated: 2024/04/08 22:38:50 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <poll.h>
#include <sys/socket.h>
#include <iostream>
#include <vector>
#include <arpa/inet.h>
#include <unistd.h>
#include <utility>
#include "ConnectionManager.hpp"
#include "Configuration.hpp"
#include "FileSystem.hpp"

class ConnectionManager;

class Server
{
public:
    Server(Configuration &configuration, FileSystem *fs, std::vector<std::pair<int, int>> &portsInUse);
    ~Server();
	Server(const Server &other);
	Server& operator=(Server &other);

	int getSocket();
	std::string getValue(std::string what);
	void printMyVals();
	ConnectionManager *_connectionManager;
	FileSystem *_fileSystem;
	long long getBodySize();
	int getPort();
	std::string		_host;
	std::vector<std::string> _otherHosts;
	
private:
	int					_serverSocket;
	int					_port;

	std::string		_serverName;
	std::string		_root;

	long long _maxBodySizeInBytes;
};

#endif
