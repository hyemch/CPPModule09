#include "PmergeMe.hpp"

PmergeMe::PmergeMe() :straggler(0){}
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
		//static_cast<int>(num)
		listSequence.push_back(static_cast<int>(num));
        dequeSequence.push_back(static_cast<int>(num));
	}
    std::cout <<"Before: " << sequence << std::endl;
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
//	printList(listSequence, "list: Before: ");
//  printDeque(dequeSequence, "deque: Before: ");
	mergeInsertSortDeque();

}

void PmergeMe::initChainDeque()
{
    if (dequeSequence.size() % 2)
    {
        straggler = *dequeSequence.rbegin();
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
    //print
//    for (size_t i = 0; i < pairDeque.size(); i++)
//    {
//        std::cout << "pair: " << pairDeque[i].first << ", " << pairDeque[i].second << std::endl;
//    }
//    std::cout << "straggler: " << straggler << std::endl;
    //main-chain pending-chain setting
    std::sort(pairDeque.begin(), pairDeque.end());
    for(std::deque<std::pair<int,int> >::iterator it = pairDeque.begin(); it != pairDeque.end(); ++it)
    {
        mainChain.push_back(it->first);
        pendingChain.push_back(it->second);
    }
}

void	PmergeMe::mergeInsertSortDeque()
{
	//1. 두개 씩 묶는다. -> std::pair로 두 개씩 묶어서 새로운 각각의 컨테이너(덱, 리스트)에 넣는다.
	//2. 우리는 오름차순으로 정렬할 것이다. 따라서 pair의 first -> 큰 값 Second ->작은 값
	// 		first -> 메인체인 / second -> pending 체인
	//3. 메인체인 정렬
	//4. while을 돌며 야콥스탈수에 맞춰서 binary search 후 insert
	//5. 홀수일 경우 마지막 요소는 전체를 대상으로 binary search 후 삽입

	initChainDeque();
	//main-chain pending-chain print
//	printDeque(mainChain, "Before MainChain: ");
//	printDeque(pendingChain, "Before PendingChain: ");
	//야콥스탈 수에 따라 pending-chain의 요소를 main-chain에 insert, 이 때 binary search를 이용.
	calculateJacubstalDeque(pendingChain.size());
	clock_t startTime = clock();
	mergeInsertDeque();
	clock_t endTime = clock();
	long printTime = static_cast<long>(endTime - startTime);
	printDeque(mainChain, "After : ");
	std::cout << "Time to process a rang of " << dequeSequence.size() \
	<< " elements with [std::deque] " << printTime << "seconds" << std::endl;
}

void	PmergeMe::binarySearchStraggler()
{
	int	left = 0;
	int	right = mainChain.size() - 1;

	while(left <= right)
	{
		int	mid = (left + right) / 2;
//		std::cout << "[" << left << "]: " << mainChain[left] <<"[" << right << "]: " << mainChain[right] << std::endl;
		if (mainChain[mid] == straggler)
		{
			mainChain.insert(mainChain.begin() + mid, straggler);
			return ;
		}
		else if (mainChain[mid] < straggler)
		{
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	mainChain.insert(mainChain.begin() + left, straggler);
}

void	PmergeMe::binarySearchDeque(int pendingChainElement)
{
	int	left = 0;
	int	right = 0;

	for (std::deque<std::pair<int,int> >::iterator it = pairDeque.begin(); it != pairDeque.end(); ++it)
	{
		if (it->second == pendingChainElement)
		{
//			std::deque<int>::iterator mIt = std::find(mainChain.begin(), mainChain.end(), it->first);
//			right = std::distance(mainChain.begin(), mIt);
			right = std::distance(mainChain.begin(), std::find(mainChain.begin(), mainChain.end(), it->first));
			break ;
		}
	}
	while(left <= right)
	{
		int	mid = (left + right) / 2;
//		std::cout << "[" << left << "]: " << mainChain[left] <<"[" << right << "]: " << mainChain[right] << std::endl;
		if (mainChain[mid] == pendingChainElement)
		{
			mainChain.insert(mainChain.begin() + mid, pendingChainElement);
			return ;
		}
		else if (mainChain[mid] < pendingChainElement)
		{
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	mainChain.insert(mainChain.begin() + left, pendingChainElement);
}

void	PmergeMe::mergeInsertDeque(void)
{
    // pending-chain 원소들을 하나씩 돌면서 main-chain에 삽입
    // 이때 binary search하여 더 작은 원소 다음자리에 삽입
	// 야콥스탈수열에 따른 순서대로 진행 1 -> 3 2 -> 5 4 -> 11 10 9 8 7 6 -> 21 20 ..
	//야콥스탈수와 현재 인덱스가 일치할때, 이 전 여콥스탈수보다 클때까지 하나씩 바이너리 서치
    mainChain.push_front(pendingChain[0]);

	std::cout << "jacobstalSequence size: " << jacobsthalSequence.size() << std::endl;

	for (size_t jIdx = 3; jIdx < jacobsthalSequence.size(); ++jIdx)
	{
		for (size_t i = jacobsthalSequence[jIdx] - 1; i >= jacobsthalSequence[jIdx - 1]; --i)
		{
			binarySearchDeque(pendingChain[i]);
		}
	}
	if (straggler > 0)
	{
		binarySearchStraggler();
	}
}

//	for (size_t	pIdx = 1; pIdx < pendingChain.size(); ++pIdx)
//	{
//		for (size_t jIdx = 3; jIdx < jacobsthalSequence.size(); ++jIdx)
//		{
//			if (pIdx == (jacobsthalSequence[jIdx] - 1))
//			{
//				for (size_t i = jacobsthalSequence[jIdx] - 1; i >= jacobsthalSequence[jIdx - 1]; --i)
//				{
//					binarySearchDeque(pendingChain[i]);
//				}
//			}
//		}
//	}

void	PmergeMe::calculateJacubstalDeque(unsigned int size)
{
	jacobsthalSequence.push_back(0);
	jacobsthalSequence.push_back(1);

	for (size_t i = 2; i < size; ++i)
	{
		unsigned int jacobstalNum = jacobsthalSequence[i - 1] + 2 * jacobsthalSequence[i - 2];
		if (jacobstalNum > size)
		{
			jacobsthalSequence.push_back(size);
//			std::cout << "jacobstal num: " << i << ": "<< jacobsthalSequence[i] << std::endl;
			break;
		}
		jacobsthalSequence.push_back(jacobstalNum);
//		std::cout << "jacobstal num: " << i << ": "<< jacobsthalSequence[i] << std::endl;
	}
}

//void	PmergeMe::timeUsed(const std::string containerName)
//{
//	//std::list
//	clock_t startTime = clock();
//	//merge-insert Sort
//	clock_t endTime = clock();
//	double printTime = static_cast<double>(startTime - endTime);
//	//정렬 된 배열 출력 "After : "
//	std::cout << "Time to process a rang of " << listSequence.size() \
//	<< "elements with " << " std::list " << printTime << "seconds" << std::endl;
//
//	//std::deque
//	clock_t startTime = clock();
//	//merge-insert Sort
//	clock_t endTime = clock();
//	double printTime = static_cast<double>(startTime - endTime);
//	//정렬 된 배열 출력 "After : "
//	std::cout << "Time to process a rang of " << dequeSequence.size() \
//	<< "elements with " << " std::deque " << printTime << "seconds" << std::endl;
//
//}
