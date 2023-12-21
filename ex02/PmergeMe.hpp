#ifndef _PMERGEME_HPP_
#define _PMERGEME_HPP_

#include <iostream>
#include <sstream>
#include <list>
#include <deque>
#include <algorithm>
#include <cstdlib>
#include <ctime>

class	PmergeMe
{
public:
	static PmergeMe*	getInstance();
	static void			releaseInstance();

	bool	parseArguments(int argc, char* argv[]);
	bool	isValidSequence(std::string& sequence);
	bool	isValidNum(std::string &temp);

	void	printList(const std::list<int>& list, const std::string& message);

	void    printDeque(const std::deque<int>& deque, const std::string& message);
	void	printSortInfo();
	void	mergeInsertSortDeque(void);
    void    initChainDeque();
	void	calculateJacubstalDeque(unsigned int size);
	void	binarySearchDeque(int pendingChainElement);
	void	binarySearchStraggler();

private:
	static PmergeMe*	instance;

	std::list<int> listSequence;

    std::deque<int> dequeSequence;
    std::deque<std::pair<int,int> > pairDeque;
	std::deque<int> mainChain;
	std::deque<int> pendingChain;
    int straggler;

	std::deque<unsigned int>	jacobsthalSequence;

	PmergeMe();
	~PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);

};

#endif