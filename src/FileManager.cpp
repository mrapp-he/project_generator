
#include "includes.hpp"

FileManager::FileManager(void) {

}

FileManager::~FileManager(void) {
	
}

void FileManager::createFile(const std::string& file_name, const std::string& content) {
	std::ofstream write_file(file_name.c_str());
	if (!write_file.is_open())
		throw std::runtime_error(std::string("Couldn't open write file" + file_name));
	write_file << content;
}