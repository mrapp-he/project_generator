
#include "ProjectGenerator.hpp"

ProjectGenerator::ProjectGenerator(std::vector<std::string>& args) {
	this->_flags.push_back("--r");
	this->_flags.push_back("--ocf");
	args.at(0).erase(0, 1);
	this->_process = args.at(0);
	this->parseArgs(args);
}

ProjectGenerator::~ProjectGenerator(void) {
	
}

bool ProjectGenerator::isValidProjectName(const std::string& name) {
	if (name.empty())
		return (false);
	for (size_t i = 0; i < name.size(); ++i) {
		char c = name.at(i);
		if (!std::isalnum(c) && c != '_' && c != '-')
			return (false);
	}
	return (true);
}

bool ProjectGenerator::isValidFlag(const std::string& flag) {
	for (size_t i = 0; i < this->_flags.size(); ++i) {
		if (flag == this->_flags.at(i))
			return (true);
	}
	return (false);
}

bool ProjectGenerator::isValidClassName(const std::string& name) {
	if (name.empty())
		return (false);
	char c = name.at(0);
	if (!std::isupper(c))
		return (false);
	for (size_t i = 1; i < name.size(); ++i) {
		c = name.at(i);
		if (!std::isalnum(c))
			return (false);
	}
	return (true);
}

void ProjectGenerator::parseArgs(const std::vector<std::string>& args) {
	if (!this->isValidProjectName(args.at(1)))
		throw std::runtime_error(std::string(args.at(1) + " is not a valid project name"));
	this->_name = args.at(1);
	if (!this->isValidFlag(args.at(2)))
		throw std::runtime_error(std::string(args.at(2) + " is not a valid flag"));
	this->_flag = args.at(2);
	std::vector<std::string> check_classes = split(args.at(3), " ");
	for (size_t i = 0; i < check_classes.size(); ++i) {
		std::string class_name(check_classes.at(i));
		if (!this->isValidClassName(class_name))
			throw std::runtime_error(std::string(class_name + " is not a valid class name"));
	}
	this->_classes = check_classes;
}

void ProjectGenerator::makeFolder(std::string path, std::string name) {
	std::string new_folder(path + '/' + name);
	int status = mkdir(new_folder.c_str(), S_IRWXU);
	if (status < 0)
		throw std::runtime_error(std::string("mkdir() failed: ") + std::strerror(errno));
	this->_folders.insert(std::make_pair(name, new_folder));
}

void ProjectGenerator::generateFolders(void) {
	char buff[PATH_MAX];
	char *path = getcwd(buff, PATH_MAX);
	if (!path)
		throw std::runtime_error(std::string("getcwd() failed: ") + std::strerror(errno));
	this->makeFolder(path, this->_name);
	this->makeFolder(this->_folders.at(this->_name), "src");
	this->makeFolder(this->_folders.at(this->_name), "lib");
}

std::string ProjectGenerator::getPath(void) {
	char buff[PATH_MAX];
	ssize_t len = readlink("/proc/self/exe", buff, sizeof(buff));
	if (len < 0)
		throw std::runtime_error(std::string("readlink() failed: ") + std::strerror(errno));
	std::string path(buff);
	size_t i = path.find(this->_process);
	if (i != std::string::npos)
		path.erase(i, this->_process.size());
	return (path);
}

void ProjectGenerator::generate(void) {
	this->generateFolders();
	this->_templates.setTemplates(this->_flag, this->getPath());
	std::string file_name(this->_folders.at(this->_name) + "/main.cpp");
	std::string content(this->_templates.getTemplate("main"));
	this->_templates.replacePlaceHolder(content, "{{PROJECT_NAME}}", this->_name);
	this->_files.createFile(file_name, content);
	file_name = this->_folders.at(this->_name) + "/Makefile";
	content = this->_templates.getTemplate("Makefile");
	this->_templates.replacePlaceHolder(content, "{{PROJECT_NAME}}", this->_name);
	this->_files.createFile(file_name, content);
	file_name = this->_folders.at("lib") + "/" + this->_name + ".hpp";
	content = this->_templates.getTemplate("header");
	this->_templates.replacePlaceHolder(content, "{{PROJECT_NAME}}", this->_templates.formatHeaderName(this->_name));
	this->_files.createFile(file_name, content);
	for (size_t i = 0; i < this->_classes.size(); ++i) {
		std::string class_name(this->_classes.at(i));
		file_name = this->_folders.at("src") + "/" + class_name + ".cpp";
		content = this->_templates.getTemplate(".cpp");
		this->_templates.replacePlaceHolder(content, "{{CLASS_NAME}}", class_name);
		this->_files.createFile(file_name, content);
		file_name = this->_folders.at("lib") + "/" + class_name + ".hpp";
		content = this->_templates.getTemplate(".hpp");
		this->_templates.replacePlaceHolder(content, "{{CLASS_NAME}}", class_name);
		this->_templates.replacePlaceHolder(content, "{{HEADER_NAME}}", this->_templates.formatHeaderName(class_name));
		this->_files.createFile(file_name, content);
	}
}