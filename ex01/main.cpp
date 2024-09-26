#include "RPN.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage : ./RPN <expr>" << std::endl;
		return 1;
	}
	try {
		RPN rpn(argv[1]);
		std::cout << rpn.performCalcul() << std::endl;
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}