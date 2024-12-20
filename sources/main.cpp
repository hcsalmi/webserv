/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:32:31 by lbroms            #+#    #+#             */
/*   Updated: 2024/04/09 17:26:49 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Configuration.hpp"
#include "../includes/Cluster.hpp"

std::vector<std::string> splitConfigs(const std::string& configFile)
{
    std::vector<std::string> serverConfigs;

    std::ifstream file(configFile);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open configuration file: " << configFile << std::endl;
        return serverConfigs;
    }
	std::string configBlock;
	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty())
			continue;
		std::string trimmedLine = line.substr(line.find_first_not_of(" \t"));
		trimmedLine = trimmedLine.substr(0, trimmedLine.find_last_not_of(" \t") + 1);
		if (trimmedLine == "server")
		{
			std::getline(file, line);
			line = line.substr(line.find_first_not_of(" \t"));
			line = line.substr(0, line.find_last_not_of(" \t") + 1);
			if (line != "{")
				throw std::runtime_error("Error: server block must start with {");
			int brackets = 1;
			while (std::getline(file, line) && brackets)
			{
				line = line.substr(line.find_first_not_of(" \t"));
				line = line.substr(0, line.find_last_not_of(" \t") + 1);
				if (!line.empty())
				{
					if (line.find("}") != std::string::npos)
					{
						brackets--;
						if (brackets)
							configBlock += line + "\n";
					}
					else if (line.find("{") != std::string::npos)
					{
						configBlock += line + "\n";
						brackets++;
					}
					else
						configBlock += line + "\n";
				}
			}
			if (brackets)
				throw std::runtime_error("Error: server block format issue");
			serverConfigs.push_back(configBlock);
			configBlock.clear();
		}
	}
    file.close();
    return serverConfigs;
}

std::vector<Configuration> readAndSetConfigs(const char* pathToConfig)
{
    std::vector<Configuration> ret;

    std::vector<std::string> serverConfigs = splitConfigs(pathToConfig);

    for (std::vector<std::string>::iterator it = serverConfigs.begin(); it != serverConfigs.end(); ++it)
    {
        std::string& serverConfig = *it;
		try {
			Configuration config(serverConfig);
			ret.push_back(config);
		} catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
			std::cout << "Error found in config. The faulty server will not be included" << std::endl;
		}
    }
	if (ret.size() < 1)
	{
		throw std::runtime_error("Error: No viable configurations found. Aborting initialization");
	}
    return ret;
}


int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Usage: ./program_name one_argument" <<  std::endl;
		return (1);
	}
	try
	{
		std::cout << "###INITIALIZING###" << std::endl;
		std::vector<Configuration> conf_array = readAndSetConfigs(argv[1]);
		Cluster cluster(conf_array);
		cluster.theMainLoop();
	}
	catch(std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		return 1;
	}
	return (0);
}
