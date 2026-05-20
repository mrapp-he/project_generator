
#ifndef TEMPLATE_MANAGER_HPP
# define TEMPLATE_MANAGER_HPP

# include "includes.hpp"

class TemplateManager;

typedef void (TemplateManager::*setClassMethod)(const std::string&);

class TemplateManager {
	private:
	std::map<std::string, std::string> _templates;
	std::map<std::string, setClassMethod> _set_class; 
	public:
		TemplateManager(void);
		~TemplateManager(void);
		void setTemplates(const std::string& flag, const std::string &path);
		void setRClassTemplate(const std::string& path);
		void setOcfClassTemplate(const std::string& path);
		std::string getTemplate(std::string template_name);
		std::string formatHeaderName(std::string name);
		void replacePlaceHolder(std::string& template_content, std::string from, std::string to);
};

#endif