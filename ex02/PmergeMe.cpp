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

void	PmergeMe::releaseInstance()
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
    //'jot -r 3000 1 100000 | tr '\n' ' ''
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
		listSequence.push_back(num);
        dequeSequence.push_back(num);
	}
    std::cout <<"Before: " << sequence << std::endl;
	return true;
}

void	PmergeMe::printList(const std::list<long> &list, const std::string &message)
{
	std::cout << message;
	for (std::list<long>::const_iterator it = list.begin(); it != list.end(); it++)
	{
		std::cout << *it  << " ";
	}
	std::cout << std::endl;
}

void	PmergeMe::printDeque(const std::deque<long> &deque, const std::string &message)
{
    std::cout << message;
    for (std::deque<long>::const_iterator it = deque.begin(); it != deque.end(); it++)
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
	printList(listSequence, "list: Before: ");
    printDeque(dequeSequence, "deque: Before: ");

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
//	std::cout << "Time to process a rang of " << listSequence.size() \
//	<< "elements with " << containerName<< printTime << "seconds" << std::endl;
//}

