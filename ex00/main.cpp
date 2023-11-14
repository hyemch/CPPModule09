#include "BitcoinExchange.hpp"
#include <fstream>

int main(int argc, char* argv[])
{
	if (argc != 2 || strcmp(argv[1], "input.txt") != 0)
	{
		std::cout << "Error: could not open file." << std::endl;
		return 1;
	}
	std::ifstream	file((argv[1]));
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}

	//open input file
	// open error 처리

	return 0;
}