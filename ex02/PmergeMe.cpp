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
	printList(listSequence, "list: Before: ");
    printDeque(dequeSequence, "deque: Before: ");
	mergeInsertSortDeque(dequeSequence);

}

void	PmergeMe::mergeInsertSortDeque(std::deque<int>& dequeSequence)
{
	//1. 두개 씩 묶는다. -> std::pair로 두 개씩 묶어서 새로운 각각의 컨테이너(덱, 리스트)에 넣는다.
	//2. 우리는 오름차순으로 정렬할 것이다. 따라서 pair의 first -> 큰 값 Second ->작은 값
	// 		first -> 메인체인 / second -> pending 체인
	//3. 메인체인 정렬
	//4. while을 돌며 야콥스탈수에 맞춰서 binary search 후 insert
	//5. 홀수일 경우 마지막 요소는 전체를 대상으로 binary search 후 삽입

	std::deque<std::pair<int,int> > pairDeque;
	int straggler = 0;
//	std::deque<int> mainChain;
//	std::deque<int> pendingChain;

	for(size_t i = 0; i < dequeSequence.size(); i += 2)
	{
//		if (dequeSequence.size() % 2 && i == dequeSequence.size() - 1)
//		{
//			straggler.push_back(*dequeSequence.rbegin());
//		}
		else if (dequeSequence[i] > dequeSequence[i + 1])
		{
			pairDeque.push_back(std::make_pair(dequeSequence[i],dequeSequence[i + 1]));
		}
		else
		{
			pairDeque.push_back(std::make_pair(dequeSequence[i + 1], dequeSequence[i]));
		}
	}
	//print
	for (size_t i = 0; i < pairDeque.size(); i++)
	{
		std::cout << "pair: " << pairDeque[i].first << ", " << pairDeque[i].second << std::endl;
	}
	if (dequeSequence.size() % 2)
		std::cout << "straggler: " << *straggler.begin() << std::endl;
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
