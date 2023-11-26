#include "RPN.hpp"

int	main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << "\" Polish mathematical expression\"" << std::endl;
		return 1;
	}

	RPN* rpn = RPN::getInstance();
	rpn->isValidExpression(argv[1]);

	return 0;
}