#include "CmdInterface.h"

void inputStringExpression(std::string& polyStr)
{
	std::cout << "Enter the Expression: ";
	std::cin.ignore();
	std::getline(std::cin, polyStr);

	polyStr.erase(remove_if(polyStr.begin(), polyStr.end(), isspace), polyStr.end());
}

void inputRangeAndCalc(int& start, int& end, Poly& poly, std::vector<int>& outputSet)
{
	std::cout << "\nEnter First and Finish Number: ";
	std::cin >> start >> end;

	poly.calculatePoly(start, end, outputSet);

	std::cout << "\nOutput Set: ";
	for (int i : outputSet)
		std::cout << i << " ";
}

struct CmdInterface::strIndex
{
	const char* str;
} strIndexer;

CmdInterface::CmdInterface()
{
	m_state = 0;
	m_isRunning = true;
}

CmdInterface::~CmdInterface()
{
	m_state = -1;
	m_isRunning = false;
}

//5x^3 - 3x^2 + 8x - 100
void CmdInterface::parsePoly(strIndex* strIndex, int str_size, Poly& poly)
{
	while (*strIndex->str)
	{
		int coeff = 1, power = 1;
		bool coeffIsConstant = false;

		int sign = checkSign(strIndex);
		ParserUtils::getNumberFromString(&strIndex->str, coeff);
		coeff *= sign;

		power = checkExponent(strIndex, coeffIsConstant);
		(power > MAX_DEGREE) ? throw std::invalid_argument(std::string("Invalid Exponent/Degree: " + std::to_string(power) + " in the term. Must be less or equal to " + std::to_string(MAX_DEGREE))) : void();

		(!coeffIsConstant && std::abs(coeff) > MAX_COEFFICIENT) ? throw std::invalid_argument(std::string("Invalid Coefficient: " + std::to_string(coeff) + " in the term. Must be less or equal to ") + std::to_string(MAX_COEFFICIENT)) : void();
		(coeffIsConstant && std::abs(coeff) > MAX_CONSTANT) ? throw std::invalid_argument(std::string("Invalid Constant: " + std::to_string(coeff) + " in the term. Must be less or equal to " + std::to_string(MAX_CONSTANT))) : void();

		Term term = Term(coeff, power, coeffIsConstant);
		poly.addTerm(term);		

		//If second constant is found then ignore
		if (coeffIsConstant)
			break;
	}
}

int CmdInterface::checkSign(strIndex* strIndex)
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

int CmdInterface::checkExponent(strIndex* strIndex, bool& coeffIsConstant)
{
	int power = 0;
	if (*strIndex->str == 'x' || *strIndex->str == 'X')
	{
		power = 1;
		strIndex->str++;
		if (*strIndex->str == '^')
		{
			strIndex->str++;
			ParserUtils::getNumberFromString(&strIndex->str, power);
		}
	}
	else
		coeffIsConstant = true;

	return power;
}

void CmdInterface::askToContinue(int toState)
{
	std::cout << "\n\nPlease any key to continue..." << std::endl;
	std::cin.ignore();
	std::cin.get();
	m_state = toState;
}

void CmdInterface::askSaveFile(const std::vector<int>& outputSet)
{
	std::cout << "\nSave the Output Set in a file? Enter Y/N\nYour Answer: ";
	std::cin.ignore();
	char saveChar; std::cin >> saveChar;

	std::string fileName;
	switch (saveChar)
	{
	case 'y':
		std::cout << "\nEnter Filename: ";
		std::cin.ignore();
		std::cin >> fileName;
		saveSetToFile(fileName, outputSet);
		break;

	case 'n':
	default:
		return;
	}
}

bool CmdInterface::isRunning() const { return m_isRunning; }

void CmdInterface::update()
{
	switch (m_state)
	{
	case 0:
		showMainMenu();		
		break;
	case 1:		
		enterExpression();
		break;
	case 2:
		break;
	case 3:
		m_isRunning = false;
		break;

	default:
		std::cout << "Invalid number!" << std::endl;
		askToContinue(0);
		break;
	}
}

void CmdInterface::showMainMenu()
{
	system("cls");
	std::cout << "Enter Numbers to initiate commands: " << std::endl;
	std::cout << "1. Enter Expression\n";
	std::cout << "2. Derive Expression\n";
	std::cout << "3. Exit\n";

	std::cout << "\nChoose: ";
	std::cin >> m_state;
}

//State = 1
void CmdInterface::enterExpression()
{
	system("cls");

	std::string polyStr("");
	inputStringExpression(polyStr);

	Poly poly = Poly();
	strIndexer.str = polyStr.c_str();

	try { parsePoly(&strIndexer, polyStr.size(), poly); }
	catch (const std::invalid_argument& e)
	{
		std::cout << "Exception occured: " << e.what();
		askToContinue(0);
		return;
	}

	int startNum = 0, finishNum = 0;
	std::vector<int> outputSet;
	inputRangeAndCalc(startNum, finishNum, poly, outputSet);

	askSaveFile(outputSet);

	askToContinue(0);
}

void CmdInterface::saveSetToFile(const std::string& fileName, const std::vector<int>& outputSet)
{
	std::ofstream fileWriter(fileName);
	fileWriter.exceptions(std::ofstream::badbit | std::ofstream::failbit);
	try 
	{
		for (int i = 0; i < outputSet.size(); i++)
		{
			if(i == outputSet.size() - 1)
				fileWriter << outputSet[i];
			else
				fileWriter << outputSet[i] << ", ";
		}
	}
	catch (std::ofstream::failure& e)
	{
		std::cout << "Exception Occured: Failed writing to file: " << fileName << " Message: " << e.what();
	}
}

void CmdInterface::readSetFromFile(std::string fileName)
{

}