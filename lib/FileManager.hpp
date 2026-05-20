
#ifndef FILE_MANAGER_HPP
# define FILE_MANAGER_HPP

# include "includes.hpp"

class FileManager {
	public:
		FileManager(void);
		~FileManager(void);
		void createFile(const std::string& file_name, const std::string& content);
};

#endif