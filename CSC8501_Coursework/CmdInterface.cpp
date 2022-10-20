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
	{
		//processExpression();
		ProcessExprForward forwardProcess = ProcessExprForward();
		askToContinue(0);
		break;
	}
	case 2:
	{
		//readFile();
		ProcessExprReverse reverseProcess = ProcessExprReverse();
		askToContinue(0);
		break;
	}
	case 3:
	{
		//readFile(true);
		ProcessExprReverse reverseProcess = ProcessExprReverse(true);
		askToContinue(0);
		break;
	}
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
		(power > Rules::MAX_DEGREE) ? throw std::invalid_argument(std::string("Invalid Exponent/Degree: " + std::to_string(power) + " in the term. Must be less or equal to " + std::to_string(Rules::MAX_DEGREE))) : void();

		(!coeffIsConstant && std::abs(coeff) > Rules::MAX_COEFFICIENT) ? throw std::invalid_argument(std::string("Invalid Coefficient: " + std::to_string(coeff) + " in the term. Must be less or equal to ") + std::to_string(Rules::MAX_COEFFICIENT)) : void();
		(coeffIsConstant && std::abs(coeff) > Rules::MAX_CONSTANT) ? throw std::invalid_argument(std::string("Invalid Constant: " + std::to_string(coeff) + " in the term. Must be less or equal to " + std::to_string(Rules::MAX_CONSTANT))) : void();

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

	//std::string fileName("OutputSet.txt");
	switch (saveChar)
	{
		case 'y':
		case 'Y':
		{
			FileHandler f = FileHandler();
			f.saveOutputSetFile(outputSet);
			break;
			/*std::cout << "\nEnter Filename: ";
			std::cin.ignore();
			std::cin >> fileName;*/
			//saveSetToFile(fileName, outputSet);
		}

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
		for (size_t i = 0; i < outputSet.size(); i++)
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
	std::cout << "\nEnter the [Index] to select the output set: ";
	int index; std::cin.ignore(); std::cin >> index;
	if (index < 0 || index > outputLinesV.size() - 1)
	{
		std::cout << "\nInvalid [Index] entered!";
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
	int degreeRound = 0, size = outputSet.size();
	std::vector<int> deltaSet, prevDeltaSet = outputSet;
	do
	{
		degreeRound++; size--;
		deltaSet = Utils::getDifferentiateVector(prevDeltaSet, size);
		Utils::printVector(deltaSet);
		prevDeltaSet = deltaSet;
	} while (!Utils::isVectorConstant(deltaSet));

	std::cout << "\nMax Degree: " << degreeRound;

	int rows = degreeRound + 1, cols = degreeRound + 2;
	std::vector<std::vector<int>> matrix;
	Utils::morphMatrixVect(matrix, rows, cols);
	for (int i = 0; i < rows; i++)
	{
		int matPower = degreeRound;
		for (int j = 0; j < cols; j++)
		{
			if (j >= 0 && j < cols - 3)
			{
				matrix[i][j] = 1 * pow(i, matPower);
				matPower--;
			}
			else if (j == cols - 2)
				matrix[i][j] = 1;
			else if (j == cols - 1)
				matrix[i][j] = outputSet[i];
			else
				matrix[i][j] = i;
		}
	}
	Utils::printMatrixVector(matrix, rows, cols);

	/*std::cout << "\n";
	int i = rows - 1, j = cols - 1;
	std::cout << matrix[i][j] << "\n";
	std::cout << matrix[i - 1][j] << "\n";
	std::cout << matrix[i - 2][j] << "\n";*/
	int rowsIgnored = 0;
	std::vector<std::vector<int>> matrixCopy;
	std::cout << "\nRows: " << rows << " | Cols: " << cols;
	for (int k = 0; k < degreeRound; k++)
	{
		matrixCopy = matrix;
		
		#pragma region Reverse Iterate (Works not)
		//for (int i = rows - 1; i >= 1; i--)
		//{
		//	if (i == rowsIgnored)
		//		continue;

		//	for (int j = cols - 1; j >= 0; j--)
		//	{
		//		matrix[i][j] = matrixCopy[i][j] - matrixCopy[i - 1][j];
		//		//std::cout << matrix[i][j] << "\t";
		//	}
		//	//std::cout << "\n";
		//	rowsIgnored++;
		//}  
#pragma endregion

		for (int i = rowsIgnored; i < rows; i++)
		{
			if (i == rowsIgnored)
				continue;

			for (int j = 0; j < cols; j++)
				matrix[i][j] = matrixCopy[i][j] - matrixCopy[i - 1][j];
		}
		rowsIgnored++;
		Utils::printMatrixVector(matrix, rows, cols);
	}
	
	std::cout << "\n";
	int* finalCoeffs = new int[rows] {0};

	int termToLook = 0;
	finalCoeffs[0] = matrix[rows - 1][cols - 1] / matrix[rows - 1][0];	//1st Coeff or 'a'
	termToLook++;
	//finalCoeffs[rows - 1] = matrix[0][cols - 1];						//last constant - d/e etc

	//std::vector<std::vector<int>> matrixFinal = matrix;
	for (int i = rows - 2; i >= 0; i--)
	{
		int toFind = matrix[i][termToLook];
		for (int t = 0; t < termToLook; t++)
			matrix[i][t] *= finalCoeffs[t];
		for (int j = 0; j < cols; j++)
		{
			if (j != cols - 1 && j != termToLook)
				matrix[i][j] *= -1;
		}

		int sum = matrix[i][cols - 1];
		for (int k = 0; k < termToLook; k++)
			sum += matrix[i][k];

		finalCoeffs[termToLook] = sum / toFind;
		termToLook++;
		if (i == 0 && termToLook == cols - 2)
		{
			finalCoeffs[termToLook] = matrix[i][cols - 1];
			break;
		}

		//Utils::printMatrixVector(matrixFinal, rows, cols);
	}

	//Utils::printMatrixVector(matrixFinal, rows, cols);
	Utils::printArray(finalCoeffs, rows);

	int power = degreeRound;
	std::cout << "\n\nYour Expression is: ";
	for (int i = 0; i < rows; i++)
	{
		if (finalCoeffs[i] != 0)
		{
			if (finalCoeffs[i] > 0 && i > 0)
				std::cout << "+";			

			if(finalCoeffs[i] != 1)
				std::cout << finalCoeffs[i];
			if (i != rows - 1)
				std::cout << "x";
			if (power > 0 && power != 1)
				std::cout << "^" << power;
		}
		power--;
	}

#pragma region DRYRUNCOEFFS
	//int* finalCoeffs = new int[rows];

////a
//int lastElement = matrix[rows - 1][cols - 1];
//std::cout << "\nmatrix[rows - 1][cols - 1] = " << lastElement;
//std::cout << "\nmatrix[rows - 1][0] = " << matrix[rows - 1][0];
//finalCoeffs[0] = (lastElement != 0 && matrix[rows - 1][0] != 0) ? lastElement / matrix[rows - 1][0] : 0;
//std::cout << "\na = " << finalCoeffs[0];

////b
//std::cout << "\n\nmatrix[rows - 2][0] = " << matrix[rows - 2][0];
//std::cout << "\nmatrix[rows - 2][1] = " << matrix[rows - 2][1];
//std::cout << "\nmatrix[rows - 2][2] = " << matrix[rows - 2][2];
//std::cout << "\nmatrix[rows - 2][3] = " << matrix[rows - 2][3];
//std::cout << "\nmatrix[rows - 2][4] = " << matrix[rows - 2][4];

//int* secondLast = new int[cols];
//std::cout << "\n";
//for (size_t i = 0; i < cols; i++)
//{
//	secondLast[i] = matrix[rows - 2][i];
//	if (i != 1 && i != cols - 1)
//		secondLast[i] *= finalCoeffs[0] * -1;
//	std::cout << secondLast[i] << "\t";
//}

//finalCoeffs[1] = (secondLast[cols - 1] + secondLast[0]) / secondLast[1];
//std::cout << "\nb = " << finalCoeffs[1];
//std::cout << "\n";
//
//int* thirdLast = new int[cols];
//for (size_t i = 0; i < cols; i++)
//	thirdLast[i] = matrix[rows - 3][i];
//thirdLast[0] *= finalCoeffs[0] * -1;
//thirdLast[1] *= finalCoeffs[1] * -1;

//for (size_t i = 0; i < cols; i++)
//	std::cout << thirdLast[i] << "\t";

//finalCoeffs[2] = thirdLast[cols - 1] + thirdLast[0] + thirdLast[1] / thirdLast[2];
//std::cout << "\nc = " << finalCoeffs[2];
//std::cout << "\n";

//finalCoeffs[3] = matrix[0][cols - 1];
//std::cout << "\nd = " << finalCoeffs[3];
//std::cout << "\n";  
#pragma endregion
}

#pragma region DRY RUN
	//int a0 = deltaSet[0] / Utils::factorial(degreeRound);
	//std::cout << "\n\nPolynomial has max degree - " << degreeRound;
	//std::cout << "\na = " << a0;

	//int* f0 = new int[degreeRound + 2];
	//f0[0] = 1 * pow(0, degreeRound);		//ax^3
	//f0[1] = 1 * pow(0, degreeRound - 1);	//bx^2
	//f0[2] = 1 * pow(0, degreeRound - 2);	//cx
	//f0[3] = 1;								//d
	//f0[4] = outputSet[0];

	//int* f1 = new int[degreeRound + 2];
	//f1[0] = 1 * pow(1, degreeRound);		//ax^3
	//f1[1] = 1 * pow(1, degreeRound - 1);	//bx^2
	//f1[2] = 1 * pow(1, degreeRound - 2);	//cx
	//f1[3] = 1;								//d
	//f1[4] = outputSet[1];

	//int* f2 = new int[degreeRound + 2];
	//f2[0] = 1 * pow(2, degreeRound);		//ax^3
	//f2[1] = 1 * pow(2, degreeRound - 1);	//bx^2
	//f2[2] = 1 * pow(2, degreeRound - 2);	//cx
	//f2[3] = 1;								//d
	//f2[4] = outputSet[2];

	//int* f3 = new int[degreeRound + 2];
	//f3[0] = 1 * pow(3, degreeRound);		//ax^3
	//f3[1] = 1 * pow(3, degreeRound - 1);	//bx^2
	//f3[2] = 1 * pow(3, degreeRound - 2);	//cx
	//f3[3] = 1;								//d
	//f3[4] = outputSet[3];

	//Utils::printArray(f0, 5);
	//Utils::printArray(f1, 5);
	//Utils::printArray(f2, 5);
	//Utils::printArray(f3, 5);

	//std::cout << "\n";

	//int* f5 = new int[degreeRound + 2];
	//for (int i = 0; i < 5; i++)
	//	f5[i] = f1[i] - f0[i];
	//Utils::printArray(f5, 5);

	//int* f6 = new int[degreeRound + 2];
	//for (int i = 0; i < 5; i++)
	//	f6[i] = f2[i] - f1[i];
	//Utils::printArray(f6, 5);

	//int* f7 = new int[degreeRound + 2];
	//for (int i = 0; i < 5; i++)
	//	f7[i] = f3[i] - f2[i];
	//Utils::printArray(f7, 5);

	//std::cout << "\n";

	//int* f9 = new int[degreeRound + 2];
	//for (int i = 0; i < 5; i++)
	//	f9[i] = f6[i] - f5[i];
	//Utils::printArray(f9, 5);

	//int* f10 = new int[degreeRound + 2];
	//for (int i = 0; i < 5; i++)
	//	f10[i] = f7[i] - f6[i];
	//Utils::printArray(f10, 5);

	//std::cout << "\n";

	//int* f11 = new int[degreeRound + 2];
	//for (int i = 0; i < 5; i++)
	//	f11[i] = f10[i] - f9[i];
	//Utils::printArray(f11, 5);

	//int a = (f11[4] > 0 && f11[0] > 0) ? f11[4] / f11[0] : 0;
	//int b = (f11[4] > 0 && f11[1] > 0) ? f11[4] / f11[1] : 0;
	//int c = (f11[4] > 0 && f11[2] > 0) ? f11[4] / f11[2] : 0;
	//int d = (f11[4] > 0 && f11[3] > 0) ? f11[4] / f11[3] : 0;

	//std::cout << "\n\n";
	//std::cout << a << "x^" << degreeRound << " + " << b << "x^" << degreeRound - 1 << " + " << c << "x^" << degreeRound - 2 << " + " << d;
#pragma endregion

#pragma region OLD CODE
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
#pragma endregion