#ifndef _PMERGEME_HPP_
#define _PMERGEME_HPP_

#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>

class	PmergeMe
{
public:
	static PmergeMe*	getInstance();
	static void			releaseInstace();

	void	isValidSequence(const char* argv);

private:
	static PmergeMe*	instance;

	PmergeMe();
	~PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
};

#endif