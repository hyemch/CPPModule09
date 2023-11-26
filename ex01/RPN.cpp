#include "RPN.hpp"

RPN::RPN() {}
RPN::~RPN() {}

RPN*	RPN::instance = NULL;

RPN*	RPN::getInstance()
{
	if (instance == NULL)
	{
		instance = new RPN();
	}
	return instance;
}

void	RPN::releaseInstance()
{
	if (instance != NULL)
	{
		delete instance;
		instance = NULL;
	}
}

bool	RPN::isValidExpression(const char *argv)
{
	std::string expression = argv;
	for (size_t i = 0; i < expression.size(); i++)
	{
		if (!isdigit(expression[i]) && !(expression[i] == '+' || expression[i] == '-' \
		|| expression[i] == '*' || expression[i] == '/') && expression[i] != ' ')
		{
			std::cout << "Error" << std::endl;
			return false;
		}
		//숫자 10 넘어가는 경우도 x
	}
//	std::string operatorToken;
	return true;
}