/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:39:07 by lbroms            #+#    #+#             */
/*   Updated: 2024/04/09 15:43:04 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGURATION_HPP
# define CONFIGURATION_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <vector>
#include <map>

class Configuration
{
	public:
		Configuration(std::string configData); // read config upon construction // the { } check comes in main
		~Configuration(void);

		void printMyVals();

		int	getListenPort();
		std::string	getHost();
		std::string getValue(std::string what);
		std::string	getDirective(std::string what);
		std::map<std::string, std::string> &getDirectives(){return _serverDirectives;};
		std::vector<std::pair<std::string, std::map<std::string, std::string>>> getLocations();
	private:
		int	_port;
		std::string _host;

		std::vector<std::pair<std::string, std::map<std::string, std::string>>> _locations;
		std::map<std::string, std::string>		_serverDirectives;

		std::string trimLeadingSpaces(const std::string& input);
		std::string trimTrailingSpaces(const std::string& input);
};

#endif
