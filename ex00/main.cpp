#include "BitcoinExchange.hpp"

int main(void)
{
	BitcoinExchange be("data.csv");

	be.treatInput("input.txt");
}