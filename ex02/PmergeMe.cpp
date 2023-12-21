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

/* 1. 두개 씩 묶는다. -> std::pair로 두 개씩 묶어서 새로운 각각의 컨테이너(덱, 리스트)에 넣는다.
 * 2. 우리는 오름차순으로 정렬할 것이다. 따라서 pair의 first -> 큰 값 Second ->작은 값
		first -> 메인체인 / second -> pending 체인
 * 3. 메인체인 정렬
 * 4. while을 돌며 야콥스탈수에 맞춰서 binary search 후 insert
 * 5. 홀수일 경우 마지막 요소는 전체를 대상으로 binary search 후 삽입
 * 6. clock_t : 클럭 틱 단위로 일반적으로는 초당 클럭 틱 수를 나타내며 CLOCKS_PER_SEC상수로 확인할 수 있다. */

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

/* pending-chain 원소들을 하나씩 돌면서 main-chain에 삽입
 * 이때 binary search하여 더 작은 원소 다음자리에 삽입
 * 야콥스탈수열에 따른 순서대로 진행 1 -> 3 2 -> 5 4 -> 11 10 9 8 7 6 -> 21 20 ..
 * 야콥스탈수와 현재 인덱스가 일치할때, 이 전 여콥스탈수보다 클때까지 하나씩 바이너리 서치 */

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
			binarySearchDeque(pendingChainDeque[i]);
		}
	}
	if (stragglerDeque > 0)
	{
		binarySearchStragglerDeque();
	}
}

static std::list<int>::iterator	doAdvanceList(std::list<int>::iterator itStart, std::list<int>::iterator itEnd, int num)
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
//		for (size_t i = jacobsthalSequenceList[jIdx] - 1; i >= jacobsthalSequenceList[jIdx - 1]; --i)
		for (int i = *doAdvanceList(jacobsthalSequenceList.begin(), jacobsthalSequenceList.end(), jIdx) - 1; i >= *doAdvanceList(jacobsthalSequenceList.begin(), jacobsthalSequenceList.end(), jIdx - 1); --i)
		{
			binarySearchList(*doAdvanceList(pendingChainList.begin(), pendingChainList.end(), i));
//			binarySearchList(pendingChainList[i]);
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
            pairDeque.push_back(std::make_pair(dequeSequence[i - 1],dequeSequence[i]));
        }
        else
        {
            pairDeque.push_back(std::make_pair(dequeSequence[i], dequeSequence[i - 1]));
        }
    }
    std::sort(pairDeque.begin(), pairDeque.end());
    for(std::deque<std::pair<int,int> >::iterator it = pairDeque.begin(); it != pairDeque.end(); ++it)
    {
        mainChainDeque.push_back(it->first);
        pendingChainDeque.push_back(it->second);
    }
}

void PmergeMe::initChainList()
{
	if (listSequence.size() % 2)
	{
		stragglerList = *listSequence.rbegin();
	}
	for(size_t i = 1; i < listSequence.size(); i += 2)
	{
		if (*doAdvanceList(listSequence.begin(), listSequence.end(), i - 1) > *doAdvanceList(listSequence.begin(), listSequence.end(), i))
		{
			pairList.push_back(std::make_pair(*doAdvanceList(listSequence.begin(), listSequence.end(), i - 1), *doAdvanceList(listSequence.begin(), listSequence.end(), i)));
		}
		else
		{
			pairList.push_back(std::make_pair(*doAdvanceList(listSequence.begin(), listSequence.end(), i), *doAdvanceList(listSequence.begin(), listSequence.end(),i - 1)));
		}
	}
	pairList.sort();
	for(std::list<std::pair<int,int> >::iterator it = pairList.begin(); it != pairList.end(); ++it)
	{
		mainChainList.push_back(it->first);
		pendingChainList.push_back(it->second);
	}
//	printList(mainChainList, "list mainchain: ");
//	printList(pendingChainList, "list pendingchain: ");
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
//		int jacobsthalNum = jacobsthalSequenceList[i - 1] + 2 * jacobsthalSequenceList[i - 2];
		int jacobsthalNum = *doAdvanceList(jacobsthalSequenceList.begin(), jacobsthalSequenceList.end(), i - 1) + 2 * *(doAdvanceList(jacobsthalSequenceList.begin(), jacobsthalSequenceList.end(), i - 2));
		if (jacobsthalNum > size)
		{
			jacobsthalSequenceList.push_back(size);
			break;
		}
		jacobsthalSequenceList.push_back(jacobsthalNum);
	}
}

void	PmergeMe::binarySearchDeque(int pendingChainElement)
{
	int	left = 0;
	int	right = 0;

	for (std::deque<std::pair<int,int> >::iterator it = pairDeque.begin(); it != pairDeque.end(); ++it)
	{
		if (it->second == pendingChainElement)
		{
			right = std::distance(mainChainDeque.begin(), std::find(mainChainDeque.begin(), mainChainDeque.end(), it->first));
			break ;
		}
	}
	while(left <= right)
	{
		int	mid = (left + right) / 2;
		if (mainChainDeque[mid] == pendingChainElement)
		{
			mainChainDeque.insert(mainChainDeque.begin() + mid, pendingChainElement);
			return ;
		}
		else if (mainChainDeque[mid] < pendingChainElement)
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}
	mainChainDeque.insert(mainChainDeque.begin() + left, pendingChainElement);
}

void	PmergeMe::binarySearchList(int pendingChainElement)
{
	//*doAdvanceList()
	int	left = 0;
	int	right = 0;

	for (std::list<std::pair<int,int> >::iterator it = pairList.begin(); it != pairList.end(); ++it)
	{
		if (it->second == pendingChainElement)
		{
			right = std::distance(mainChainList.begin(), std::find(mainChainList.begin(), mainChainList.end(), it->first));
			break ;
		}
	}
	while(left <= right)
	{
		int	mid = (left + right) / 2;
//		if (mainChainList[mid] == pendingChainElement)
		if (*doAdvanceList(mainChainList.begin(), mainChainList.end(), mid) == pendingChainElement)
		{
			mainChainList.insert(doAdvanceList(mainChainList.begin(), mainChainList.end(), mid), pendingChainElement);
			return ;
		}
		else if (*doAdvanceList(mainChainList.begin(), mainChainList.end(), mid) < pendingChainElement)
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}
	mainChainList.insert(doAdvanceList(mainChainList.begin(), mainChainList.end(), left), pendingChainElement);
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
		if (*doAdvanceList(mainChainList.begin(), mainChainList.end(), mid) == stragglerList)
		{
			mainChainList.insert(doAdvanceList(mainChainList.begin(), mainChainList.end(), mid), stragglerList);
			return ;
		}
		else if (*doAdvanceList(mainChainList.begin(), mainChainList.end(), mid) < stragglerList)
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}
	mainChainList.insert(doAdvanceList(mainChainList.begin(), mainChainList.end(), left), stragglerList);
}

