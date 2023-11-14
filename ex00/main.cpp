#include "BitcoinExchange.hpp"


int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Error: could not open file." << std::endl;
		return 1;
	}

	BitcoinExchange& btcExchange = BitcoinExchange::getInstance();

	//open input file
	// open error 처리

	return 0;
}