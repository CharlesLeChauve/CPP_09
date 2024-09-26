#include <map>
#include <fstream>
#include <sstream>
#include <iostream>

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

void	BitcoinExchange::buildMapFromFile(std::string file)
{
	std::ifstream data;

	data.open(file);
	if (!data.is_open())
		throw(std::runtime_error("Error opening file"));
	std::string line;
	while (std::getline(data, line)) {
        std::istringstream ss(line);
        std::string datePart;
        std::string floatPart;

        if (std::getline(ss, datePart, ',') && std::getline(ss, floatPart)) {
            float number = std::strtof(floatPart.c_str(), NULL);
			rates[datePart] = number;
        } else {
            std::cerr << "Error reading file : " << line << std::endl;
        }
    }
	data.close();
}

int		BitcoinExchange::checkDate(std::string date) {

	std::istringstream yearStream(date.substr(0, 4));
	int year;
	if (!(yearStream >> year))
		return 0;

	std::istringstream monthStream(date.substr(5, 2));
	int month;
	if (!(monthStream >> month) || month < 1 || month > 12)
		return 0;

	std::istringstream dayStream(date.substr(8, 2));
	int day;
	if (!(dayStream >> day))
		return 0;
	int maxDays = 31;
	if (month == 2) {
		bool isLeap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
		maxDays = isLeap ? 29 : 28;
	} else if (month == 4 || month == 6 || month == 9 || month == 11) {
		maxDays = 30;
	}

	if (day < 1 || day > maxDays)
		return 0;

	return 1;
}

float	BitcoinExchange::getDayRate(std::string date)
{
	std::map<std::string, float>::iterator it = rates.lower_bound(date);
	if (it != rates.end() && it->first != date) {
		if (it != rates.begin())
			--it;
	}
	if (it != rates.end()) {
		return it->second;
	}

	std::cerr << "Error : No matching date" << std::endl;
	return 0;
}

void	BitcoinExchange::treatInput(std::string inputFile)
{
	std::ifstream data;

	data.open(inputFile);
	if (!data.is_open())
		throw(std::runtime_error("Error opening file"));
	std::string line;
	while (std::getline(data, line)) {
        std::istringstream ss(line);
        std::string datePart;
        std::string floatPart;

		std::getline(ss, datePart, '|');
		if (!checkDate(datePart)) {
			std::cerr << "Error: Bad Input => " << datePart << std::endl;
			continue ;
		}
		char *end;
        std::getline(ss, floatPart);
        float number = std::strtof(floatPart.c_str(), &end);
		if (*end != '\0')
			std::cerr << "Error : please verify number syntax" << std::endl;
		else if (number > 1000)
			std::cerr << "Error : number too large" << std::endl;
		else if (number < 0)
			std::cerr << "Error : not a positive number" << std::endl;
		else {
			std::cout << datePart << " => " << number << " = " << (number * getDayRate(datePart)) << std::endl;
		}
    }
	data.close();
}

BitcoinExchange::BitcoinExchange(std::string rateFile)
{
	buildMapFromFile(rateFile);
}

BitcoinExchange::~BitcoinExchange()
{
}
