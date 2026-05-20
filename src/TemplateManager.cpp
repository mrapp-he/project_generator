
#include "includes.hpp"

TemplateManager::TemplateManager(void) {
	this->_set_class.insert(std::make_pair("--r", &TemplateManager::setRClassTemplate));
	this->_set_class.insert(std::make_pair("--ocf", &TemplateManager::setOcfClassTemplate));
}

TemplateManager::~TemplateManager(void) {
	
}

void TemplateManager::setTemplates(const std::string& flag, const std::string &path) {
	setClassMethod set_class = this->_set_class.at(flag);
	(this->*set_class)(path);
	this->_templates.insert(std::make_pair("main", path + MAIN));
	this->_templates.insert(std::make_pair("Makefile", path + MAKE));
	this->_templates.insert(std::make_pair("header", path + HEADER));
}

void TemplateManager::setRClassTemplate(const std::string& path) {
	this->_templates.insert(std::make_pair(".cpp", path + R_CLASS));
	this->_templates.insert(std::make_pair(".hpp", path + R_HEADER));
}

void TemplateManager::setOcfClassTemplate(const std::string& path) {
	this->_templates.insert(std::make_pair(".cpp", path + OCF_CLASS));
	this->_templates.insert(std::make_pair(".hpp", path + OCF_HEADER));
}

std::string TemplateManager::getTemplate(std::string template_name) {
	std::string file(this->_templates.at(template_name));
	std::ifstream read_file(file.c_str());
	if (!read_file.is_open())
		throw std::runtime_error(std::string("Couldn't open read file " + file));
	std::string line;
	std::ostringstream content;
	while (std::getline(read_file, line)) {
		content << line;
		if (!read_file.eof())
			content << std::endl;
	}
	return (content.str());
}

std::string TemplateManager::formatHeaderName(std::string name) {
	for (std::string::iterator i = name.begin(); i != name.end(); ++i) {
		char c = *i;
		if (std::isupper(c) && i != name.begin())
			name.insert(i, '_');
		if (!std::isupper(c)) {
			i = name.erase(i);
			name.insert(i, std::toupper(c));
		}
	}
	return (name);
}

void TemplateManager::replacePlaceHolder(std::string& template_content, std::string from, std::string to) {
	size_t pos;
	while ((pos = template_content.find(from)) != std::string::npos) {
		template_content.erase(pos, from.size());
		template_content.insert(pos, to);
		pos += to.size();
	}
}