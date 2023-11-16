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
	if (!isValidField(line))
	{
		std::cerr << "Error: could not find data field: " << line << std::endl;
		return ;
	}
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
			std::cerr << "Error: date form [0000-00-00] : " << date << std::endl;
		}
		bitcoinData[date] = exchangeRate;
		//날짜 유효한지 확인
		// map에 넣어줘....
	}
}

bool	BitcoinExchange::isValidField(const std::string &firstLine)
{
	std::istringstream line(firstLine);
	std::string field1;
	std::string field2;
	std::getline(line, field1, ',');
	std::getline(line, field2);
	//각 필드의 맨 앞, 맨 뒤 화이트스페이스 제거
	field1 = removeWhitespace(field1);
	std::cout << "field1: " << field1 << std::endl;
	field2 = removeWhitespace(field2);
	std::cout << "field2: " << field2 << std::endl;
	if (field1 != "date" || field2 != "exchange_rate")
	{
		return false;
	}
	return true;
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
	return dateStream.eof() && year >= 0 && month >= 1 && month <= 12 \
	&& day >= 1 && day <= 31;
}

std::string BitcoinExchange::removeWhitespace(std::string &field)
{
	int start = 0;
	int end = field.size();
	while (start < end && std::isspace(field[start]))
	{
		start++;
	}
	while (end > start && std::isspace(field[end - 1]))
	{
		end--;
	}
	return field.substr(start, end - start);
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