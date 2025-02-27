/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:39:27 by lbroms            #+#    #+#             */
/*   Updated: 2024/04/09 15:34:19 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

long long Server::getBodySize()
{
	return _maxBodySizeInBytes;
}

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/

Server::Server(const Server &other) : _connectionManager(new ConnectionManager(this))
{
	_host = other._host;
	_otherHosts = other._otherHosts;
	_fileSystem = other._fileSystem;
	_serverSocket = other._serverSocket;
	_serverName = other._serverName;
	_root = other._root;
	_maxBodySizeInBytes = other._maxBodySizeInBytes;
	_port = other._port;
}

Server& Server::operator=(Server& other)
{
	if (this != &other) 
	{
		delete this->_connectionManager;
		_connectionManager = new ConnectionManager(this);
		_fileSystem = other._fileSystem;
		_serverSocket = other._serverSocket;
		_serverName = other._serverName;
		_host = other._host;
		_root = other._root;
		_maxBodySizeInBytes = other._maxBodySizeInBytes;
		_port = other._port;
		_otherHosts = other._otherHosts;
	}
	return *this;
}

Server::Server(Configuration &configuration, FileSystem *fs, std::vector<std::pair<int,int>> &portsInUse):
	 _connectionManager(new ConnectionManager(this)),
	 _fileSystem(fs)
{
	bool portUnused = true;
	for (unsigned long i = 0; i < portsInUse.size(); i++)
	{
		std::pair<int,int> portAndSock = portsInUse[i];
		if (portAndSock.first == configuration.getListenPort())
		{
			this->_serverSocket = portAndSock.second;
			portUnused = false;
			break;
		}
	}
	if (portUnused)
	{
		this->_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (_serverSocket == -1)
			throw std::runtime_error("Error creating socket");
		int reuse = 1;
		if (setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
		{
			close(_serverSocket);
			throw std::runtime_error("Error setting socket options");
		}
		sockaddr_in serverAddress;
		std::memset(&serverAddress, 0, sizeof(serverAddress));
		serverAddress.sin_family = AF_INET;
		serverAddress.sin_addr.s_addr = INADDR_ANY;
		serverAddress.sin_port = htons(configuration.getListenPort());
		if (bind(_serverSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1)
		{
			close(_serverSocket);
			throw std::runtime_error("Error binding socket");
		}
		if (listen(_serverSocket, 10) == -1)
		{
			close(_serverSocket);
			throw std::runtime_error("Error listening on socket");
		}
	}
	_port = configuration.getListenPort();
	_serverName = configuration.getValue("server_name");
	_host = configuration.getValue("host");
	_root = configuration.getValue("root");
	if (configuration.getValue("client_max_body_size") != "")
		_maxBodySizeInBytes = std::stoull(configuration.getValue("client_max_body_size"));
}

Server::~Server(void)
{
	delete this->_connectionManager;
}

/******************************************************************************/
/*							PRIVATE FUNCTIONS								  */
/******************************************************************************/

/******************************************************************************/
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/

int Server::getPort()
{
	return _port;
}

int Server::getSocket()
{
	return (this->_serverSocket);
}

std::string	Server::getValue(std::string what)
{
	if (what == "server_name")
		return _serverName;
	if (what == "host")
		return _host;
	if (what == "root")
		return _root;
	return "";
}

void Server::printMyVals()
{
	std::cout << "##server " << _serverName << " has these values##" << std::endl;
	std::cout << "serverSocket: " << _serverSocket << std::endl;
	std::cout << "serverName: " << _serverName << std::endl;
	std::cout << "hostAddress: " << _host << std::endl;
	std::cout << "rootDir: " << _root << std::endl;
	std::cout << "###########################" << std::endl;
}
