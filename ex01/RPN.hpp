#include <stack>
#include <sstream>

class RPN
{
private:
	std::stack<int> stack;
	std::string		args;
public:
	RPN(std::string args);
	~RPN();

	class InvalidArgument : public std::exception
	{
		virtual const char* what() const throw();
	};

	void performOp(char c);
	void compute(std::string token);

	//General Method
	int performCalcul();
};

