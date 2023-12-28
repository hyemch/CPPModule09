#include "PmergeMe.hpp"

void	leak(void)
{
	system("leaks PmergeMe");
}

int main(int argc, char* argv[])
{
	atexit(leak);
	if (argc < 2)
	{
		std::cout << "Usage: ./PmergeMe [num1 num2 num3 ...]"<< std::endl;
		return 1;
	}
	PmergeMe*	pMergeMe = PmergeMe::getInstance();
	if (pMergeMe->parseArguments(argc, argv))
	{
		pMergeMe->printSortInfo();
	}
	PmergeMe::releaseInstance();
	return 0;
}