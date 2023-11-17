#include "BitcoinExchange.hpp"

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Error: could not open file." << std::endl;
		return 1;
	}

	BitcoinExchange* btcExchange = BitcoinExchange::getInstance();
	btcExchange->setBitcoinData();
//	btcExchange->printBitcoinData();
	btcExchange->setInputFile(argv[1]);

	BitcoinExchange::releaseInstance();

	return 0;
}