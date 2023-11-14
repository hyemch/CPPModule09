#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <map>

class BitcoinExchange
{
public:
	static BitcoinExchange* getInstance();
	//정적 멤버 함수를 통해 전역적으로 접근 가능한 인스턴스 반환
	void	someFunction(); // 필요한 멤버 함수 만들기

private:
	static BitcoinExchange* instance;

	BitcoinExchange();
	~BitcoinExchange();
	BitcoinExchange& operator=(const BitcoinExchange& other);
	BitcoinExchange(const BitcoinExchange& other);

};

#endif