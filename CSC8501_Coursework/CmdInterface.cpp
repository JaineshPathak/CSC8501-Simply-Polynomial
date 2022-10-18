#include "CmdInterface.h"

void inputStringExpression(std::string& polyStr)
{
	std::cout << "Enter Algebraic Expression, for example: 5x^3 + 2x^2 - x + 3\n";
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

bool CmdInterface::isRunning() const { return m_isRunning; }

void CmdInterface::update()
{
	switch (m_state)
	{
	case 0:
		showMainMenu();
		break;
	case 1:
		processExpression();
		break;
	case 2:
		readFile();
		break;
	case 3:
		readFile(true);
		break;
	case 4:
		m_isRunning = false;
		break;

	default:
		std::cout << "Invalid number!" << std::endl;
		askToContinue(0);
		break;
	}
}

//5x^3 - 3x^2 + 8x - 100
void CmdInterface::parsePoly(strIndex* strIndex, int str_size, Poly& poly)
{
	while (*strIndex->str)
	{
		int coeff = 1, power = 1;
		bool coeffIsConstant = false;

		int sign = checkSign(strIndex);
		Utils::getNumberFromString(&strIndex->str, coeff);
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
			Utils::getNumberFromString(&strIndex->str, power);
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
	std::cout << "\n\nSave the Output Set in a file? Enter Y/N\nYour Answer: ";
	std::cin.ignore();
	char saveChar; std::cin >> saveChar;

	std::string fileName("OutputSet.txt");
	switch (saveChar)
	{
	case 'y':
	case 'Y':
		/*std::cout << "\nEnter Filename: ";
		std::cin.ignore();
		std::cin >> fileName;*/
		saveSetToFile(fileName, outputSet);
		break;

	case 'n':
	case 'N':
	default:
		return;
	}
}

void CmdInterface::showMainMenu()
{
	system("cls");
	std::cout << "Enter Numbers to initiate commands: " << std::endl;
	std::cout << "1. Enter Expression and get Output Set\n";
	std::cout << "2. Read file and get Output Sets\n";
	std::cout << "3. Read Output Set and derive Expression\n";
	std::cout << "4. Exit\n";
	std::cout << "\nChoose: "; std::cin >> m_state;
}

void CmdInterface::processExpression()
{
	system("cls");
	std::string polyStr("");
	inputStringExpression(polyStr);

	Poly poly = Poly();
	strIndexer.str = polyStr.c_str();

	try { parsePoly(&strIndexer, polyStr.size(), poly); }
	catch (const std::invalid_argument& e)
	{
		std::cout << "\nException occured: " << e.what();
		askToContinue(0);
		return;
	}

	int startNum = 0, finishNum = 0;
	std::vector<int> outputSet;
	inputRangeAndCalc(startNum, finishNum, poly, outputSet);
	askSaveFile(outputSet);
	askToContinue(0);
}

void CmdInterface::readFile(bool withExpression)
{
	system("cls");
	std::ifstream fileReader("OutputSet.txt", std::ios::in);
	fileReader.exceptions(std::ifstream::badbit);
	try
	{
		if (!fileReader.good())
			throw std::ifstream("Probably file doesn't exists or badbit Error");

		std::string line/*, finalLine*/; int index = 0;
		std::vector<std::string> stringList;
		std::cout << "Output Sets:\n[Index]\t[Sets]\n";
		while (std::getline(fileReader, line, '\n'))
		{
			std::cout << index << "\t" << line << std::endl;
			index++;
			//finalLine += line;
			//finalLine += '\n';
			line.erase(remove(line.begin(), line.end(), ','), line.end());
			stringList.push_back(line);		
		}
		//std::cout << finalLine;
		if (withExpression)
			parseOutputSet(stringList);
		fileReader.close();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "\nException Occured: Failed reading file: OutputSet.txt" << " Message: " << e.what();
	}

	askToContinue(0);
}

void CmdInterface::saveSetToFile(const std::string& fileName, const std::vector<int>& outputSet)
{
	std::ofstream fileWriter(fileName.c_str(), std::ios::app);
	fileWriter.exceptions(std::ofstream::badbit | std::ofstream::failbit);
	try
	{
		for (int i = 0; i < outputSet.size(); i++)
			(i == outputSet.size() - 1) ? fileWriter << outputSet[i] : fileWriter << outputSet[i] << ", ";
		fileWriter << "\n";
		fileWriter.close();
	}
	catch (std::ofstream::failure& e)
	{
		std::cout << "\nException Occured: Failed writing to file: " << fileName << " Message: " << e.what();
	}

	std::cout << "\nFile Saved: " << fileName;
}

void CmdInterface::parseOutputSet(const std::vector<std::string>& outputLinesV)
{
	std::cout << "\nEnter the [Index] to select the set: ";
	int index; std::cin.ignore(); std::cin >> index;
	if (index < 0 || index > outputLinesV.size() - 1)
	{
		std::cout << "\nInvalid Index entered!";
		return;
	}
	getOutputSet(outputLinesV[index]);
}

void CmdInterface::getOutputSet(const std::string& strSet)
{
	int num = 0;
	std::vector<int> intSet;
	std::stringstream ss(strSet);
	while (ss >> num)
		intSet.push_back(num);

	deriveExpression(intSet);
}

void CmdInterface::deriveExpression(const std::vector<int> outputSet)
{
	int degreeRound = 0, size = 11;
	std::vector<int> deltaSet, prevDeltaSet = outputSet;
	do
	{
		degreeRound++; size--;
		deltaSet = Utils::getDifferentiateVector(prevDeltaSet, size);
		//Utils::printVector(deltaSet);
		prevDeltaSet = deltaSet;
	} while (!Utils::isVectorConstant(deltaSet));

	std::cout << "\nPolynomial has " << degreeRound << " terms";
	std::cout << "\na = " << deltaSet[0] / Utils::factorial(degreeRound);
	/*for (int i = 1; i < size; i++)
		deltaSet.push_back(outputSet[i] - outputSet[i - 1]);

	Utils::printVector(deltaSet);
	if (!Utils::isVectorConstant(deltaSet))
	{
		deltaRound++; size--;
		std::vector<int> deltaSet2;
		for (int i = 1; i < size; i++)
			deltaSet2.push_back(deltaSet[i] - deltaSet[i - 1]);

		Utils::printVector(deltaSet2);
		if (!Utils::isVectorConstant(deltaSet2))
		{
			deltaRound++; size--;
			std::vector<int> deltaSet3;
			for (int i = 1; i < size; i++)
				deltaSet3.push_back(deltaSet2[i] - deltaSet2[i - 1]);

			Utils::printVector(deltaSet3);
			if (Utils::isVectorConstant(deltaSet3))
			{
				int coeff = deltaSet3[0] / (Utils::factorial(deltaRound));
				int power = deltaRound;

				std::cout << "\n\nCoeff: " << coeff << ", Power: " << power;
			}
		}
	}*/
}