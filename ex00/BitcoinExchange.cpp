#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange* BitcoinExchange::instance = NULL;

BitcoinExchange* BitcoinExchange::getInstance()
{
	if (instance == NULL)
	{
		instance = new BitcoinExchange();
	}
	return instance;
}

void	BitcoinExchange::releaseInstance()
{
	if (instance != NULL)
	{
		delete instance;
		instance = NULL;
	}
}

void	BitcoinExchange::setBitcoinData()
{
	std::ifstream dataFile("data.csv");

	if (!dataFile.is_open())
	{
		std::cerr << "Error: could not find datafile." << std::endl;
		return ;
	}
	std::string line;
	std::getline(dataFile, line);
	while (std::getline(dataFile, line))
	{
		std::istringstream	iss(line);
		std::string date;
		double	exchangeRate;
		if(!std::getline(iss, date, ','))
		{
			std::cerr << "Error: database date error." << std::endl;
			return ;
		}
		if (!(iss >> exchangeRate))
		{
			std::cerr << "Error: database exchange rate error." << std::endl;
			return ;
		}
		if (!isValidDate(date))
		{
			std::cerr << "Error: date is invalid." << std::endl;
		}
		bitcoinData[date] = exchangeRate;
		//날짜 유효한지 확인
		// map에 넣어줘....
	}
}

bool	BitcoinExchange::isValidDate(const std::string &date)
{
	if (date.length() != 10)
	{
		return false;
	}
	for (size_t i = 0; i < date.length(); i++)
	{
		if (i == 4 || i == 7)
		{
			if (date[i] != '-')
			{
				return false;
			}
		}
		else
		{
			if (!isdigit(date[i]))
			{
				return false;
			}
		}
	}
	std::istringstream dateStream(date);
	int year, month, day;
	char dash1, dash2;

	dateStream >> year >> dash1 >> month >> dash2 >> day;

	// stringstream이 제대로 파싱했는지와 각 부분이 유효한 값인지 확인
	return dateStream.eof() && dash1 == '-' && dash2 == '-' &&
		   year >= 0 && month >= 1 && month <= 12 &&
		   day >= 1 && day <= 31;
}

void	BitcoinExchange::printBitcoinData()
{
	for(std::map<std::string, double>::iterator it = bitcoinData.begin(); it != bitcoinData.end(); it++)
	{
		std::cout << "key: " << it->first << "exchangeRate: " << it->second << std::endl;
	}
}


//std::ifstream	file((argv[1]));
//if (!file.is_open())
//{
//std::cerr << "Error: could not open file." << std::endl;
//return 1;
//}