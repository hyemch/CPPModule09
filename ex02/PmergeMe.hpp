#ifndef _PMERGEME_HPP_
#define _PMERGEME_HPP_

#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>
#include <cstdlib>
#include <ctime>

class	PmergeMe
{
public:
	static PmergeMe*	getInstance();
	static void			releaseInstace();

	void	parseArguments(int argc, char* argv[]);
	bool	isValidSequence(std::string& sequence);
	bool	isValidNum(std::string &temp);

	void	printVector(const std::vector<long>& vector, const std::string& message);

	void	mergeInsertSort(void);

private:
	static PmergeMe*	instance;
	std::vector<long> vectorSequence;
//	std::list<int> listSequence;

	PmergeMe();
	~PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
};

#endif