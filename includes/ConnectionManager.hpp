/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionManager.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:39:49 by lbroms            #+#    #+#             */
/*   Updated: 2024/04/08 22:09:52 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ConnectionManager.hpp

#ifndef CONNECTION_MANAGER_HPP
#define CONNECTION_MANAGER_HPP

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Server.hpp"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>

class Server;
class HttpRequest;
class HttpResponse;

class ConnectionManager
{
	public:
		ConnectionManager(Server *parent);
		~ConnectionManager();

		bool	handleConnection(int cs);
		int		handleResponse();
		bool	hasReadyResponses();
		bool	hasRunningProcesses();
		bool	completeProcess();
		bool	_hasMovableRequest;
		unsigned long		_movableIndex;
		HttpRequest	getMovable();
		void		recvMovable(HttpRequest objct);
		
	private:
		Server *_parent;
		int _responsesReady;
		std::vector<HttpRequest> _requests;
		std::vector<HttpResponse> _responses;

		int findObjectIndex(int cs);
	//HttpRequest httpRequest; // this parses the requests made by the clients.
	//RequestHandler requestHandler; // the actual things for example: cgi or GET POST DELETE. will be handled by request handler.
	//HttpResponse httpResponse; // reply to the client is done by this.

};

#endif

