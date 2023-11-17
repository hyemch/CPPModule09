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
	void	setBitcoinData();
	bool	isValidField(const std::string& firstLine, const char sep, std::string str1, std::string str2);
	bool	isValidDate(const std::string& data);

	void	setInputFile(const char* argv);

	void	removeWhitespace(std::string& field);
	void	printBitcoinData();

private:
	static BitcoinExchange* instance;
	std::map<std::string, double> bitcoinData;

	BitcoinExchange();
	~BitcoinExchange();
	BitcoinExchange& operator=(const BitcoinExchange& other);
	BitcoinExchange(const BitcoinExchange& other);

};

#endif