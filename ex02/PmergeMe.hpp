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

	void	parseArguments(int argc, char* argv[]);
	bool	isValidSequence(std::string& sequence);
	bool	isValidNum(std::string &temp);

	void	printList(const std::list<int>& list, const std::string& message);
    void    printDeque(const std::deque<int>& deque, const std::string& message);
	void	mergeInsertSortDeque(std::deque<int>& dequeSequence);

private:
	static PmergeMe*	instance;
	std::list<int>listSequence;
    std::deque<int>dequeSequence;

	PmergeMe();
	~PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
};

#endif