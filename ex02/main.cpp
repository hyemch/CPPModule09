#include "PmergeMe.hpp"

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << "Usage: ./PmergeMe [num1 num2 num3 ...]"<< std::endl;
		return 1;
	}
	PmergeMe*	pMergeMe = PmergeMe::getInstance();
	pMergeMe->parseArguments(argc, argv);
	PmergeMe::releaseInstance();
	return 0;
}