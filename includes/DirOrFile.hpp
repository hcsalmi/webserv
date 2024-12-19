/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DirOrFile.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:07:39 by lbroms            #+#    #+#             */
/*   Updated: 2024/03/28 22:35:03 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIRORFILE_HPP
# define DIRORFILE_HPP

#include <map>
#include <iostream>
#include <string>
#include "FileSystem.hpp"

class DirOrFile
{
	private:
	/*directory specific*/
		bool _imDirectory;
	/*file specific*/
		std::string		_fileContent;

	public:
		bool	amIDir();
		std::string getFileContent();
		DirOrFile(bool imADir, std::string name, std::string path);
		DirOrFile(const DirOrFile& other);
		DirOrFile(bool imADir, std::string content);
		~DirOrFile();
};

#endif
