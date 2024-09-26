#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

class BitcoinExchange
{
private:
	std::map<std::string, float> rates;
	std::map<std::string, float> values;
	void	buildMapFromFile(std::string file);
public:
	BitcoinExchange(std::string rateFile);
	~BitcoinExchange();

	void	treatInput(std::string inputFile);
	int		checkDate(std::string date);
	float	getDayRate(std::string date);
};
