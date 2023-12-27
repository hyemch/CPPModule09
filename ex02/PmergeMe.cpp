#include "PmergeMe.hpp"

PmergeMe::PmergeMe() :stragglerDeque(0), stragglerList(0) {}
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
		listSequence.push_back(static_cast<int>(num));
        dequeSequence.push_back(static_cast<int>(num));
	}
    std::cout <<"Before: " << sequence << std::endl;
	return true;
}

bool	PmergeMe::parseArguments(int argc, char **argv)
{
	std::string sequence;
	for (int i = 1; i < argc; ++i)
	{
		std::string temp = argv[i];
		sequence += temp;
		sequence += " ";
	}
	if (!isValidSequence(sequence))
	{
		return false;
	}
	return true;

}

void	PmergeMe::printList(const std::list<int> &list, const std::string &message)
{
	std::cout << message;
	for (std::list<int>::const_iterator it = list.begin(); it != list.end(); it++)
	{
		std::cout << *it  << " ";
	}
	std::cout << std::endl;
}

void	PmergeMe::printDeque(const std::deque<int> &deque, const std::string &message)
{
    std::cout << message;
    for (std::deque<int>::const_iterator it = deque.begin(); it != deque.end(); it++)
    {
        std::cout << *it  << " ";
    }
    std::cout << std::endl;
}

void	PmergeMe::printSortInfo()
{
	clock_t startTimeDeque = clock();
	mergeInsertSortDeque();
	clock_t endTimeDeque = clock();
	double printTimeDeque = static_cast<double>(endTimeDeque - startTimeDeque) / CLOCKS_PER_SEC * 1000;

//	printDeque(mainChainDeque, "After : ");

	clock_t startTimeList = clock();
	mergeInsertSortList();
	clock_t endTimeList = clock();
	double printTimeList = static_cast<double>(endTimeList - startTimeList) / CLOCKS_PER_SEC * 1000;

	printList(mainChainList, "After : ");

	std::cout << "Time to process a rang of " << dequeSequence.size() \
	<< " elements with [std::deque] " << printTimeDeque << " milliseconds" << std::endl;
	std::cout << "Time to process a rang of " << listSequence.size() \
	<< " elements with [std::list ] " << printTimeList << " milliseconds" << std::endl;
}

void	PmergeMe::mergeInsertSortDeque(void)
{
	if (dequeSequence.size() == 1)
	{
		mainChainDeque.push_back(dequeSequence[0]);
		return ;
	}
	initChainDeque();
	calculateJacobsthalDeque(pendingChainDeque.size());
	mainChainDeque.push_front(pendingChainDeque[0]);
	for (size_t jIdx = 3; jIdx < jacobsthalSequenceDeque.size(); ++jIdx)
	{
		for (size_t i = jacobsthalSequenceDeque[jIdx] - 1; i >= jacobsthalSequenceDeque[jIdx - 1]; --i)
		{
			binarySearchDeque(i);
		}
	}
	if (stragglerDeque > 0)
	{
		binarySearchStragglerDeque();
	}
}

static std::list<int>::iterator	advanceList(std::list<int>::iterator itStart, std::list<int>::iterator itEnd, int num)
{
	for (int i = 0; i < num; i++)
	{
		if (itStart != itEnd)
		{
			itStart++;
		}
	}
	return itStart;
}

void	PmergeMe::mergeInsertSortList(void)
{
	if (listSequence.size() == 1)
	{
		mainChainList.push_back(*listSequence.begin());
		return ;
	}
	initChainList();
	calculateJacobsthalList(static_cast<int>(pendingChainList.size()));
	mainChainList.push_front(*pendingChainList.begin());
	for (size_t jIdx = 3; jIdx < jacobsthalSequenceList.size(); ++jIdx)
	{
		for (int i = *advanceList(jacobsthalSequenceList.begin(), jacobsthalSequenceList.end(), jIdx) - 1; i >= *advanceList(jacobsthalSequenceList.begin(), jacobsthalSequenceList.end(), jIdx - 1); --i)
		{
			binarySearchList(advanceList(pendingChainList.begin(), pendingChainList.end(), i));
		}
	}
	if (stragglerDeque > 0)
	{
		binarySearchStragglerList();
	}
}

void PmergeMe::initChainDeque()
{
    if (dequeSequence.size() % 2)
    {
        stragglerDeque = *dequeSequence.rbegin();
    }
    for(size_t i = 1; i < dequeSequence.size(); i += 2)
    {
        if (dequeSequence[i - 1] > dequeSequence[i])
        {
			binaryInsertionDeque(std::make_pair(dequeSequence[i - 1],dequeSequence[i]));
        }
        else
        {
			binaryInsertionDeque(std::make_pair(dequeSequence[i], dequeSequence[i - 1]));
        }
    }
    for(std::deque<std::pair<int,int> >::iterator it = pairDeque.begin(); it != pairDeque.end(); ++it)
    {
        mainChainDeque.push_back(it->first);
        pendingChainDeque.push_back(it->second);
    }
}

void	PmergeMe::binaryInsertionDeque(std::pair<int,int> newPair)
{
	int left = 0;
	int right = pairDeque.size() - 1;
	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (pairDeque[mid].first == newPair.first)
		{
			pairDeque.insert(pairDeque.begin() + mid, newPair);
			return ;
		}
		else if (pairDeque[mid].first < newPair.first)
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}
	pairDeque.insert(pairDeque.begin() + left, newPair);
}

void PmergeMe::initChainList()
{
	if (listSequence.size() % 2)
	{
		stragglerList = *listSequence.rbegin();
	}
	for(size_t i = 1; i < listSequence.size(); i += 2)
	{
		if (*advanceList(listSequence.begin(), listSequence.end(), i - 1) > *advanceList(listSequence.begin(), listSequence.end(), i))
		{
			binaryInsertionList(std::make_pair(*advanceList(listSequence.begin(), listSequence.end(), i - 1), *advanceList(listSequence.begin(), listSequence.end(), i)));
		}
		else
		{
			binaryInsertionList(std::make_pair(*advanceList(listSequence.begin(), listSequence.end(), i), *advanceList(listSequence.begin(), listSequence.end(), i - 1)));
		}
	}
	for(std::list<std::pair<int,int> >::iterator it = pairList.begin(); it != pairList.end(); ++it)
	{
		mainChainList.push_back(it->first);
		pendingChainList.push_back(it->second);
	}
}

static std::list<std::pair<int, int> >::iterator advancePairList(std::list<std::pair<int, int> >& pairList, int idx)
{
	std::list<std::pair<int, int> >::iterator it = pairList.begin();
	for (int i = 0; i < idx && it != pairList.end(); ++i, ++it);
	return it;
}

void	PmergeMe::binaryInsertionList(std::pair<int,int> newPair)
{
	int left = 0;
	int right = pairList.size() - 1;

	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (advancePairList(pairList, mid)->first == newPair.first)
		{
			pairList.insert(advancePairList(pairList, mid), newPair);
			return ;
		}
		else if (advancePairList(pairList, mid)->first < newPair.first)
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}
	pairList.insert(advancePairList(pairList, left), newPair);
}

void	PmergeMe::calculateJacobsthalDeque(unsigned int size)
{
	jacobsthalSequenceDeque.push_back(0);
	jacobsthalSequenceDeque.push_back(1);

	for (size_t i = 2; i < size + 2; ++i)
	{
		unsigned int jacobsthalNum = jacobsthalSequenceDeque[i - 1] + 2 * jacobsthalSequenceDeque[i - 2];
		if (jacobsthalNum > size)
		{
			jacobsthalSequenceDeque.push_back(size);
			break;
		}
		jacobsthalSequenceDeque.push_back(jacobsthalNum);
	}
}

void	PmergeMe::calculateJacobsthalList(int size)
{
	jacobsthalSequenceList.push_back(0);
	jacobsthalSequenceList.push_back(1);

	for (int i = 2; i < size + 2; ++i)
	{
		int jacobsthalNum = *advanceList(jacobsthalSequenceList.begin(), jacobsthalSequenceList.end(), i - 1) + 2 * *(advanceList(jacobsthalSequenceList.begin(), jacobsthalSequenceList.end(), i - 2));
		if (jacobsthalNum > size)
		{
			jacobsthalSequenceList.push_back(size);
			break;
		}
		jacobsthalSequenceList.push_back(jacobsthalNum);
	}
}

void	PmergeMe::binarySearchDeque(int pendingChainIdx)
{
	int	left = 0;
	int	right = static_cast<int>(mainChainDeque.size() - pendingChainDeque.size());

	std::deque<std::pair<int, int> >::iterator  it = pairDeque.begin();
	for (; pendingChainIdx > 0; --pendingChainIdx)
	{
		if (it != pairDeque.end())
		{
			it++;
			right++;
		}
	}
	while(left <= right)
	{
		int	mid = (left + right) / 2;
		if (mainChainDeque[mid] == (it->second))
		{
			mainChainDeque.insert(mainChainDeque.begin() + mid, (it->second));
			return ;
		}
		else if (mainChainDeque[mid] < (it->second))
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}
	mainChainDeque.insert(mainChainDeque.begin() + left, (it->second));
}

void	PmergeMe::binarySearchList(std::list<int>::iterator listIt)
{
	int	left = 0;
	int	right = static_cast<int>(mainChainList.size() - pendingChainList.size());

	right += std::distance(pendingChainList.begin(), listIt);
	while(left <= right)
	{
		int	mid = (left + right) / 2;
		if (*advanceList(mainChainList.begin(), mainChainList.end(), mid) == *listIt)
		{
			mainChainList.insert(advanceList(mainChainList.begin(), mainChainList.end(), mid), *listIt);
			return ;
		}
		else if (*advanceList(mainChainList.begin(), mainChainList.end(), mid) < *listIt)
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}
	mainChainList.insert(advanceList(mainChainList.begin(), mainChainList.end(), left), *listIt);
}

void	PmergeMe::binarySearchStragglerDeque()
{
	int	left = 0;
	int	right = mainChainDeque.size() - 1;

	while(left <= right)
	{
		int	mid = (left + right) / 2;
		if (mainChainDeque[mid] == stragglerDeque)
		{
			mainChainDeque.insert(mainChainDeque.begin() + mid, stragglerDeque);
			return ;
		}
		else if (mainChainDeque[mid] < stragglerDeque)
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}
	mainChainDeque.insert(mainChainDeque.begin() + left, stragglerDeque);
}

void	PmergeMe::binarySearchStragglerList()
{
	int	left = 0;
	int	right = mainChainList.size() - 1;

	while(left <= right)
	{
		int	mid = (left + right) / 2;
		if (*advanceList(mainChainList.begin(), mainChainList.end(), mid) == stragglerList)
		{
			mainChainList.insert(advanceList(mainChainList.begin(), mainChainList.end(), mid), stragglerList);
			return ;
		}
		else if (*advanceList(mainChainList.begin(), mainChainList.end(), mid) < stragglerList)
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}
	mainChainList.insert(advanceList(mainChainList.begin(), mainChainList.end(), left), stragglerList);
}
