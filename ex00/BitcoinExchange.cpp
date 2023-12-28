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
	if (field1 != str1 || field2 != str2)
	{
		return false;
	}
	return true;
}

static bool monthOfDate(int &year,int &month,int &day)
{
	if (month == 2)
	{
		if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		{
			return day <= 29;
		}
		else
		{
			return day <= 28;
		}
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11)
	{ // 4, 6, 9, 11월
		return day <= 30;
	}
	else
	{ // 나머지 달 (1, 3, 5, 7, 8, 10, 12월)
		return day <= 31;
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
	if (dateStream.eof() && year >= 0 && month >= 1 && month <= 12 \
	&& day >= 1 && day <= 31 && monthOfDate(year, month, day))
	{
		return true;
	}
	else
		return false;
//	if (!monthOfDate(year, month, day))
//	{
//		return false;
//	}
//	return true;
}

bool	BitcoinExchange::setBitcoinData()
{
	std::ifstream dataFile("data.csv");

	if (!dataFile.is_open())
	{
		std::cerr << "Error: could not find datafile." << std::endl;
		return false;
	}
	std::string line;
	std::getline(dataFile, line);
	if (!isValidField(line, ',', "date", "exchange_rate"))
	{
		std::cerr << "Error: could not find data field: " << line << std::endl;
		return false;
	}
	while (std::getline(dataFile, line))
	{
		std::istringstream	iss(line);
		std::string date;
		double	exchangeRate;
		if(!std::getline(iss, date, ','))
		{
			std::cerr << "Error: database date error." << std::endl;
			return false;
		}
		if (!isValidDate(date))
		{
			std::cerr << "Error: Invalid date form : " << date << std::endl;
			return false;
		}
		if (!(iss >> exchangeRate) || !iss.eof())
		{
			std::cerr << "Error: database exchange rate error." << std::endl;
			return false;
		}
//		if (!iss.eof())
//		{
//			std::cerr << "Error: database exchange rate value error." << std::endl;
//			return ;
//		}
		bitcoinData[date] = exchangeRate;
	}
	return true;
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
		double	value;
		if (!std::getline(iss, date, '|') || !line.find('|', 11))
		{
			std::cout << "Error: bad input => [" << line << "]"<< std::endl;
			continue;
		}
		if (!(iss >> value) || !iss.eof())
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		removeWhitespace(date);
		if (!isValidDate(date))
		{
			std::cerr << "Error: date form [0000-00-00] and valid date : " << date << std::endl;
			continue;
		}
		if (value <= 0 || value >= 1000)
		{
			std::cerr << "Error: Out of range [0 ~ 1000]" << std::endl;
			continue;
		}
		std::map<std::string, double>::iterator findData = bitcoinData.lower_bound(date);
		if (findData->first != date && findData == bitcoinData.begin())
		{
			std::cerr << "Error: no valid date found." << std::endl;
			continue;
		}
		else if (findData->first != date)
		{
			--findData;
		}
		double result = value * findData->second;
		std::cout << date << " => " << value << " = " << result << std::endl;

//		/*value 파싱
//		 * 1. date 0000-00-00
//		 * 2. value 0 - 1000 사이의 unsigned int or float
//		 * 유효할 경우 data.cvs 의 환율 곱해서 결과 표준 출력에 표시
//		 * -> 날짜가 없을 경우 가장 가까운 하위 날
//		 * 아닐경우 다음 줄 파싱
//		 * */
	}
//isValidValue (0~ 1000 사이의 양의정수 or 부동소수점)
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
//		std::cout << "key: " << it->first << " exchangeRate: " <<  std::setprecision(15) <<it->second << std::endl;
//	}
//}