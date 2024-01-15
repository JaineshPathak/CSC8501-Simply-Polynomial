#include "ProcessExprForward.h"

struct ProcessExprForward::m_StrIndex
{
	const char* str;
} strIndexer;

ProcessExprForward::ProcessExprForward()
{
	Process();
}

ProcessExprForward::~ProcessExprForward()
{
}

void ProcessExprForward::InputStringExpression(std::string& polyStr)
{
	std::cout << "Enter Algebraic Expression, for example: 5x^3 + 2x^2 - x + 3\n";
	std::cout << "Enter the Expression: ";
	std::cin.ignore();
	std::getline(std::cin, polyStr);

	polyStr.erase(remove_if(polyStr.begin(), polyStr.end(), isspace), polyStr.end());
}

void ProcessExprForward::InputRangeAndCalc(Poly& poly)
{
	int startNum = 0, finishNum = 0;
	std::cout << "\nEnter First and Finish Number: ";
	std::cin >> startNum >> finishNum;

	poly.CalculatePoly(startNum, finishNum, m_OutputSet);

	std::cout << "\nOutput Set: ";
	Utils::PrintVector(m_OutputSet);
}

void ProcessExprForward::ParsePoly(m_StrIndex* strIndex, Poly& poly)
{
	while (*strIndex->str)
	{
		int coeff = 1, power = 1;
		bool coeffIsConstant = false;

		int sign = CheckSign(strIndex);
		Utils::GetNumberFromString(&strIndex->str, coeff);
		coeff *= sign;

		power = CheckExponent(strIndex, coeffIsConstant);
		(power > Rules::MAX_DEGREE) ? throw std::invalid_argument(std::string("Invalid Exponent/Degree: " + std::to_string(power) + " in the term. Must be less or equal to " + std::to_string(Rules::MAX_DEGREE))) : void();

		(!coeffIsConstant && std::abs(coeff) > Rules::MAX_COEFFICIENT) ? throw std::invalid_argument(std::string("Invalid Coefficient: " + std::to_string(coeff) + " in the term. Must be less or equal to ") + std::to_string(Rules::MAX_COEFFICIENT)) : void();
		(coeffIsConstant && std::abs(coeff) > Rules::MAX_CONSTANT) ? throw std::invalid_argument(std::string("Invalid Constant: " + std::to_string(coeff) + " in the term. Must be less or equal to " + std::to_string(Rules::MAX_CONSTANT))) : void();

		Term term = Term(coeff, power, coeffIsConstant);
		poly.AddTerm(term);

		//If second constant is found then ignore
		if (coeffIsConstant)
			break;
	}
}

int ProcessExprForward::CheckSign(m_StrIndex* strIndex)
{
	int sign = 1;
	if (*strIndex->str == '-')
	{
		sign = -1;
		strIndex->str++;
	}
	else if (*strIndex->str == '+')
		strIndex->str++;

	return sign;
}

int ProcessExprForward::CheckExponent(m_StrIndex* strIndex, bool& coeffIsConstant)
{
	int power = 0;
	if (*strIndex->str == 'x' || *strIndex->str == 'X')
	{
		power = 1;
		strIndex->str++;
		if (*strIndex->str == '^')
		{
			strIndex->str++;
			Utils::GetNumberFromString(&strIndex->str, power);
		}
	}
	else
		coeffIsConstant = true;

	return power;
}

void ProcessExprForward::AskSaveFile()
{
	std::cout << "\n\nSave the Output Set in a file? Enter Y/N\nYour Answer: ";
	std::cin.ignore();
	char saveChar; std::cin >> saveChar;

	//std::string fileName("OutputSet.txt");
	switch (saveChar)
	{
		case 'y':
		case 'Y':
		{
			FileHandler fh = FileHandler();
			fh.SaveFile(m_OutputSet);
			break;		
		}

		case 'n':
		case 'N':
		default:
			return;
	}
}

void ProcessExprForward::Process()
{
	system("cls");
	std::string polyStr("");
	InputStringExpression(polyStr);

	Poly poly = Poly();
	strIndexer.str = polyStr.c_str();

	try { ParsePoly(&strIndexer, poly); }
	catch (const std::invalid_argument& e)
	{
		std::cout << "\nException occured: " << e.what();
		return;
	}

	InputRangeAndCalc(poly);
	AskSaveFile();
}