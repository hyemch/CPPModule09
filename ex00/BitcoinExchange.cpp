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

bool	BitcoinExchange::isValidField(const std::string &firstLine, const char sep, std::string str1, std::string str2)
{
	std::istringstream line(firstLine);
	std::string field1;
	std::string field2;
	std::getline(line, field1, sep);
	std::getline(line, field2);
	//각 필드의 맨 앞, 맨 뒤 화이트스페이스 제거
	removeWhitespace(field1);
	removeWhitespace(field2);
//	std::cout << "field1: [" << field1 << "]" << std::endl;
//	std::cout << "field2: [" << field2 << "]" << std::endl;
	if (field1 != str1 || field2 != str2)
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
	if (!isValidField(line, ',', "date", "exchange_rate"))
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

void	BitcoinExchange::setInputFile(const char* argv)
{
	std::ifstream	inputFile(argv);

	if (!inputFile.is_open())
	{
		std::cerr << "Error: could not find input file." << std::endl;
		return ;
	}
	std::string line;
	std::getline(inputFile, line);
	if (!isValidField(line, '|', "date", "value"))
	{
		std::cerr << "Error: could not find input file field: " << line << std::endl;
		return ;
	}
	while (std::getline(inputFile, line))
	{
		std::istringstream iss(line);
		std::string	date;
		float	value;
		if (!std::getline(iss, date, '|'))
		{
			std::cerr << "Error: database date error." << std::endl;
		}
		else
		{
			//value 파싱
		}
	}
	// 값이 유효하지 않아도 다음 줄 계속 파싱
	//isValiDdate
	//isValidValue (0~ 1000 사이의 양의정수 of float)
}

void	BitcoinExchange::removeWhitespace(std::string &field)
{
	size_t start = 0;
	while (start < field.size() && std::isspace(field[start]))
	{
		start++;
	}
	field.erase(0, start);
	size_t end = field.size();
	while (end > 0 && std::isspace(field[end - 1]))
	{
		end--;
	}
	field.erase(end);
}

//void	BitcoinExchange::printBitcoinData()
//{
//	for(std::map<std::string, double>::iterator it = bitcoinData.begin(); it != bitcoinData.end(); it++)
//	{
//		std::cout << "key: " << it->first << "exchangeRate: " << it->second << std::endl;
//	}
//}