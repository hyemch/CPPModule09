#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}

PmergeMe*	PmergeMe::instance = NULL;

PmergeMe*	PmergeMe::getInstance()
{
	if (instance == NULL)
	{
		instance = new PmergeMe();
	}
	return instance;
}

void	PmergeMe::releaseInstace()
{
	if(instance != NULL)
	{
		delete instance;
		instance = NULL;
	}
}

void	PmergeMe::isValidSequence(const char *argv)
{
	long	num = atol(argv);

	if (strcmp(argv, "0") != 0 && num == 0)
	{
		std::cerr << "숫자 변환 실패" << std::endl;
		return ;
	}
}