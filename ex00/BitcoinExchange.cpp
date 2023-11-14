#include "BitcoinExchange.hpp"

BitcoinExchange* BitcoinExchange::getInstance()
{
	if (instance == NULL)
	{
		instance = new BitcoinExchange();
	}
	return instance;
}


//std::ifstream	file((argv[1]));
//if (!file.is_open())
//{
//std::cerr << "Error: could not open file." << std::endl;
//return 1;
//}