#ifndef _RPN_HPP_
#define _RPN_HPP_

#include <iostream>
#include <sstream>
#include <stack>
#include <climits>
#include <cstdlib>

class RPN
{
public:
	static RPN*	getInstance();
	static void	releaseInstance();

	void	calculateRPN(const char* argv);
	bool	isValidExpression(const char* argv);
	bool	isOperator(const std::string& token);
	void	executeOperator(const std::string& token);

public:
	static RPN* instance;
	std::stack<long> operandStack;

	RPN();
	~RPN();
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);

};

#endif