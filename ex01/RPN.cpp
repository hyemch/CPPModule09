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

void	RPN::calculateRPN(const char *argv)
{
	if (!isValidExpression(argv))
	{
		std::cerr << "Error: RPN example: \"[a positive integer1] [a positive integer2] [operator] ...\"" << std::endl;
		return ;
	}
	std::istringstream iss(argv);
	std::string token;
	while (iss >> token)
	{
		if (!isOperator(token))
		{
			int operand = atoi(token.c_str());
			if (operand > 9 || operand < 0)
			{
				std::cerr << "Error : operand range [0 ~ 9]" << std::endl;
				return ;
			}
			operandStack.push(operand);
		}
		else
		{
			if (operandStack.size() < 2)
			{
				std::cerr << "Error: Not enough operands." << std::endl;
				return ;
			}
			executeOperator(token);
		}
	}
	if (operandStack.size() == 1)
	{
		if (operandStack.top() > INT_MAX)
		{
			std::cerr << "Error: too large a number." << std::endl;
			return ;
		}
		else if (operandStack.top() < INT_MIN)
		{
			std::cerr << "Error: too small a number." << std::endl;
			return ;
		}
		std::cout << operandStack.top() << std::endl;
	}
	else
	{
		std::cerr << "Error: RPN is invalid." << std::endl;
		return ;
	}
}

bool	RPN::isValidExpression(const char* argv)
{
	std::string expression = argv;
	for (size_t i = 0; i < expression.size(); i++)
	{
		if (i % 2 == 1)
		{
			if (expression[i] != ' ')
				return false;
		}
		else if (!isdigit(expression[i]) && !(expression[i] == '+' || expression[i] == '-' \
		|| expression[i] == '*' || expression[i] == '/'))
		{
			return false;
		}
	}
	return true;
}

bool	RPN::isOperator(const std::string &token)
{
	if (token == "+" || token == "-" || token == "/" || token == "*")
	{
		return true;
	}
	else
	{
		return false;
	}
}

void	RPN::executeOperator(const std::string &token)
{
	long operand1 = operandStack.top();
	operandStack.pop();
	long operand2 = operandStack.top();
	operandStack.pop();

	if (token == "+")
	{
		operandStack.push(operand2 + operand1);
	}
	else if (token == "-")
	{
		operandStack.push(operand2 - operand1);
	}
	else if (token == "/")
	{
		operandStack.push(operand2 / operand1);
	}
	else if (token == "*")
	{
		operandStack.push(operand2 * operand1);
	}
}