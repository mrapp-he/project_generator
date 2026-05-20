
#ifndef PROJECT_GENERATOR_HPP
# define PROJECT_GENERATOR_HPP

# include "includes.hpp"

class ProjectGenerator {
	private:
		std::string _name;
		std::string _flag;
		FileManager _files;
		std::string _process;
		TemplateManager _templates;
		std::vector<std::string> _flags;
		std::vector<std::string> _classes;
		std::map<std::string, std::string> _folders;
		bool isValidProjectName(const std::string& name);
		bool isValidFlag(const std::string& flag);
		bool isValidClassName(const std::string& name);
		void parseArgs(const std::vector<std::string>& args);
		void makeFolder(std::string path, std::string name);
		std::string getPath(void);
		void generateFolders(void);
	public:
		ProjectGenerator(std::vector<std::string>& args);
		~ProjectGenerator(void);
		void generate(void);
};

#endif