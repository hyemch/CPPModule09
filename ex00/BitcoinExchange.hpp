#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

class BitcoinExchange
{
public:
	//정적 멤버 함수를 통해 전역적으로 접근 가능한 인스턴스 반환
	static BitcoinExchange*	getInstance();
	static void	releaseInstance();

	// 필요한 멤버 함수 만들기
	void	printBitcoinData();
	void	setBitcoinData();
	bool	isValidField(const std::string& firstLine);
	bool	isValidDate(const std::string& data);
	std::string	removeWhitespace(std::string& field);

private:
	static BitcoinExchange* instance;
	std::map<std::string, double> bitcoinData;

	BitcoinExchange();
	~BitcoinExchange();
	BitcoinExchange& operator=(const BitcoinExchange& other);
	BitcoinExchange(const BitcoinExchange& other);

};

#endif