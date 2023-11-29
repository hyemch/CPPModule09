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

bool	PmergeMe::isValidNum(std::string &temp)
{
	for (size_t i = 0; i < temp.size(); i++)
	{
		if (!isdigit(temp[i]) && temp[i] != '+')
		{
			return false;
		}
	}
	return true;
}

bool	PmergeMe::isValidSequence(std::string& sequence)
{
	std::cout <<"sequence: " << sequence << std::endl;
	std::istringstream	iss(sequence);
	std::string	temp;
	long num;
	while (iss >> temp)
	{
		if (!isValidNum(temp))
		{
			std::cerr << "Error: Failed to convert to a number: [" << temp << "]" <<std::endl;
			return false;
		}
		num = atol(temp.c_str());
		if (num <= 0 || num > INT_MAX)
		{
			std::cerr << "Error: Failed to convert to a number: [" << num << "]" << std::endl;
			return false;
		}
		vectorSequence.push_back(num);
	}
	return true;
}

void	PmergeMe::printVector(const std::vector<long> &vector, const std::string &message)
{
	std::cout << message;
	for (std::vector<long>::const_iterator it = vector.begin(); it != vector.end(); it++)
	{
		std::cout << *it  << " ";
	}
	std::cout << std::endl;
}

void	PmergeMe::parseArguments(int argc, char **argv)
{
	std::string sequence;
	for (int i = 1; i < argc; ++i)
	{
		std::string temp = argv[i];
		sequence += temp;
		sequence += " ";
//		std::cout << i << ": [" << sequence << "]" << std::endl;
	}
	if (!isValidSequence(sequence))
	{
		return ;
	}
	printVector(vectorSequence, "Before: ");
}

void	PmergeMe::mergeInsertSort()
{

}


//void	PmergeMe::timeUsed(const std::string containerName)
//{
//	clock_t startTime = clock();
//	//merge-insert Sort
//	clock_t endTime = clock();
//	double printTime = startTime - endTime;
//	std::cout << "Time to process a rang of " << vectorSequence.size() \
//	<< "elements with " << containerName<< printTime << "seconds" << std::endl;
//}

