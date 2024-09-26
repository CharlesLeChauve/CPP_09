#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Usage: ./btc <input_file>" << std::endl;
		return (1);
	}
	BitcoinExchange be("data.csv");

	be.treatInput(av[1]);
	return 0;
}