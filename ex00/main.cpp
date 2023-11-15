#include "BitcoinExchange.hpp"

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Error: could not open file." << std::endl;
		return 1;
	}
	(void)argv;
	BitcoinExchange* btcExchange = BitcoinExchange::getInstance();
	btcExchange->setBitcoinData();
	btcExchange->printBitcoinData();
	BitcoinExchange::releaseInstance();
	//open input file
	// open error 처리

	return 0;
}