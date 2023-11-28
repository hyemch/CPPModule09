#include "PmergeMe.hpp"

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << "Usage: ./PmergeMe [num1 num2 num3 ...]"<< std::endl;
		return 1;
	}

	PmergeMe*	pMergeMe = PmergeMe::getInstance();
	for (int i = 0; i < argc; ++i)
	{
			pMergeMe->isValidSequence(argv[i]);
	}
	PmergeMe::releaseInstace();
	return 0;
}