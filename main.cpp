
#include "ProjectGenerator.hpp"

int main(int ac, char **av) {
	if (ac == 1)
		return (std::cerr << ERR_NO_ARGS << std::endl, 1);
	if (ac > 4)
		return (std::cerr << ERR_TOO_MANY_ARGS << std::endl, 1);
	return (0);
}