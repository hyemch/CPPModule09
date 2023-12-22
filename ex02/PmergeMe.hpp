#ifndef _PMERGEME_HPP_
#define _PMERGEME_HPP_

#include <iostream>
#include <sstream>
#include <deque>
#include <list>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <climits>

class	PmergeMe
{
public:
	static PmergeMe*	getInstance();
	static void			releaseInstance();

	bool	parseArguments(int argc, char* argv[]);
	bool	isValidSequence(std::string& sequence);
	bool	isValidNum(std::string &temp);

	void	printSortInfo();

	void    printDeque(const std::deque<int>& deque, const std::string& message);
	void	mergeInsertSortDeque(void);
    void    initChainDeque();
	void	binaryInsertionDeque(std::pair<int, int> newPair);
	void	calculateJacobsthalDeque(unsigned int size);
	void	binarySearchDeque(int pendingChainIdx);
	void	binarySearchStragglerDeque();

	void	printList(const std::list<int>& list, const std::string& message);
	void	mergeInsertSortList(void);
	void    initChainList();
	void	binaryInsertionList(std::pair<int,int> newPair);
	void	calculateJacobsthalList(int size);
	void	binarySearchList(std::list<int>::iterator listIt);
	void	binarySearchStragglerList();

private:
	static PmergeMe*				instance;

	int								stragglerDeque;
    std::deque<int> 				dequeSequence;
	std::deque<int>					mainChainDeque;
	std::deque<int> 				pendingChainDeque;
	std::deque<unsigned int>		jacobsthalSequenceDeque;
	std::deque<std::pair<int,int> > pairDeque;

	int								stragglerList;
	std::list<int>					listSequence;
	std::list<int>					mainChainList;
	std::list<int>					pendingChainList;
	std::list<int> 					jacobsthalSequenceList;
	std::list<std::pair<int,int> > pairList;



	PmergeMe();
	~PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);

};

#endif