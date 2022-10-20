#include "CmdInterface.h"

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

void CmdInterface::askToContinue(int toState)
{
	std::cout << "\n\nPlease any key to continue..." << std::endl;
	std::cin.ignore();
	std::cin.get();
	m_state = toState;
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