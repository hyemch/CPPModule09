#ifndef _RPN_HPP_
#define _RPN_HPP_

#include <iostream>
#include <sstream>
#include <stack>

class RPN
{
public:
	static RPN*	getInstance();
	static void	releaseInstance();

//	void	calculationNum(const char* argv);
	bool	isValidExpression(const char *argv);

public:
	static RPN* instance;
	std::stack<int> operandStack;

	RPN();
	~RPN();
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);

};

#endif