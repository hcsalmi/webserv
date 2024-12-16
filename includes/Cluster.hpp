/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cluster.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:01:35 by lbroms            #+#    #+#             */
/*   Updated: 2024/03/28 20:13:08 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLUSTER_HPP
# define CLUSTER_HPP

#include <vector>
#include <string>
#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <poll.h>
#include <fcntl.h>
#include <errno.h>
#include "Configuration.hpp"
#include "Server.hpp"
#include "ConnectionManager.hpp"
#include "FileSystem.hpp"

class Cluster
{
	private:
		Cluster(void) {};
		void addServers(std::vector<pollfd> &pollfds);
		pollfd	newSocketNode(int socket);

	public:
		~Cluster(void);
		Cluster(std::vector<Configuration> configs);

		void	theMainLoop();

		std::vector<Server> servers;
		std::vector<FileSystem *> filesystems;
		unsigned long serverCount;

};

#endif
