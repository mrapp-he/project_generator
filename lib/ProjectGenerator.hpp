
#ifndef PROJECT_GENERATOR_HPP
# define PROJECT_GENERATOR_HPP

# include <string>
# include <vector>
# include <fstream>
# include <iostream>
# include "defines.hpp"
# include "FileManager.hpp"
# include "TemplateManger.hpp"

class ProjectGenerator {
	private:
		std::string _name;
		void generateFolders(void);
	public:
		ProjectGenerator(std::string name);
		~ProjectGenerator(void);
		void generate(void);
};

std::vector<std::string> split(std::string str, std::string del);

#endif