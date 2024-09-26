#include "RPN.hpp"

void RPN::performOp(char c)
{
	int	op2 = stack.top();
	stack.pop();
	int	op1 = stack.top();
	stack.pop();

	int	res;
	switch (c)
	{
	case '+':
		res = op1 + op2;
		break;
	case '-':
		res = op1 - op2;
		break;
	case '*':
		res = op1 * op2;
		break;
	case '/':
		res = op1 / op2;
		break;
	default:
		throw InvalidArgument();
		break;
	}
	stack.push(res);
}

RPN::RPN(std::string args) : args(args)
{
}

RPN::~RPN()
{
}

void RPN::compute(std::string token)
{
	if (token.size() > 1)
        throw InvalidArgument();
	if (isdigit(token.front()))
		stack.push(token.front() - '0');
	else
		performOp(token.front());
}

int RPN::performCalcul()
{
    std::string token;
    std::istringstream tokenStream(args);

    while (std::getline(tokenStream, token, ' ')) {
        compute(token);
    }
	if (stack.size() != 1)
		throw InvalidArgument();
	return stack.top();
}

const char* RPN::InvalidArgument::what() const throw() {
	return "Invalid Argument";
}
