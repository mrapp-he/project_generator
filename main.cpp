
#include "ProjectGenerator.hpp"

int main(int ac, char **av) {
	if (ac == 1)
		return (std::cerr << ERR_NO_ARGS << std::endl, 1);
	if (ac > 4)
		return (std::cerr << ERR_TOO_MANY_ARGS << std::endl, 1);
	std::vector<std::string> args;
	for (int i = 0; i < ac; ++i)
		args.push_back(av[i]);
	if (ac == 2 && args.at(1) == "--help")
		return (std::cout << USAGE_NO_CLASS << USAGE_CLASS << USAGE_CLASSES<< std::endl, 0);
	else if (ac == 2 && args.at(0) == "--flags")
		return (std::cout << FLAGS << std::endl, 0);
	try {
		ProjectGenerator project(args);
		project.generate();
	} catch (std::exception& e) {
		return (std::cerr << e.what() << std::endl, 1);
	}
	return (0);
}