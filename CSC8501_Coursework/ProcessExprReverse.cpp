#include "ProcessExprReverse.h"

ProcessExprReverse::ProcessExprReverse()
{
	m_forExpression = false;
	process();
}

ProcessExprReverse::ProcessExprReverse(const bool _forExpression)
{
	m_forExpression = _forExpression;
	process();
}

ProcessExprReverse::~ProcessExprReverse()
{
	delete[] m_finalCoeffs;
}

void ProcessExprReverse::printAllOutputSets()
{
	if (m_outputSetS.size() == 0)
		return;

	int index = 0;
	std::cout << "Output Sets:\n[Index]\t[Sets]\n";
	for (size_t i = 0; i < m_outputSetS.size(); i++, index++)
		std::cout << index << "\t" << m_outputSetS[i] << std::endl;
}

void ProcessExprReverse::askOutputIndex()
{
	std::cout << "\nEnter the [Index] to select the output set: ";
	int index; std::cin.ignore(); std::cin >> index;
	if (index < 0 || index > m_outputSetS.size() - 1)
	{
		std::cout << "\nInvalid [Index] entered!";
		return;
	}
	parseOutputSetString(m_outputSetS[index]);
}

void ProcessExprReverse::parseOutputSetString(const std::string& strSet)
{
	int num = 0;
	std::stringstream ss(strSet);
	while (ss >> num)
		m_outputSetN.push_back(num);

	startDifferentiateProcess();
}

void ProcessExprReverse::startDifferentiateProcess()
{
	m_outputSetNSize = m_outputSetN.size();
	std::vector<int> deltaSet, prevDeltaSet = m_outputSetN;
	do
	{
		m_maxDegree++; m_outputSetNSize--;
		deltaSet = Utils::getDifferentiateVector(prevDeltaSet, m_outputSetNSize);
		Utils::printVector(deltaSet);
		prevDeltaSet = deltaSet;
	} while (!Utils::isVectorConstant(deltaSet));
	prepareMatrixProcess();
}

void ProcessExprReverse::prepareMatrixProcess()
{
	m_matrixRows = m_maxDegree + 1; m_matrixCols = m_maxDegree + 2;
	Utils::morphMatrixVect(m_matrix, m_matrixRows, m_matrixCols);
	for (int i = 0; i < m_matrixRows; i++)
	{
		int matPower = m_maxDegree;
		for (int j = 0; j < m_matrixCols; j++)
		{
			if (j >= 0 && j < m_matrixCols - 3)
			{
				m_matrix[i][j] = 1 * pow(i, matPower);
				matPower--;
			}
			else if (j == m_matrixCols - 2)
				m_matrix[i][j] = 1;
			else if (j == m_matrixCols - 1)
				m_matrix[i][j] = m_outputSetN[i];
			else
				m_matrix[i][j] = i;
		}
	}
	startMatrixProcess();
}

void ProcessExprReverse::startMatrixProcess()
{
	int rowsIgnored = 0;
	std::vector<std::vector<int>> matrixCopy;
	for (int k = 0; k < m_maxDegree; k++)
	{
		matrixCopy = m_matrix;
		for (int i = rowsIgnored; i < m_matrixRows; i++)
		{
			if (i == rowsIgnored)
				continue;

			for (int j = 0; j < m_matrixCols; j++)
				m_matrix[i][j] = matrixCopy[i][j] - matrixCopy[i - 1][j];
		}
		rowsIgnored++;
	}
	startCoefficientsHunt();
}

void ProcessExprReverse::startCoefficientsHunt()
{
	m_finalCoeffs = new int[m_matrixRows] {0};

	int termToLook = 1;
	m_finalCoeffs[0] = m_matrix[m_matrixRows - 1][m_matrixCols - 1] / m_matrix[m_matrixRows - 1][0];	//1st Coeff or 'a'
	for (int i = m_matrixRows - 2; i >= 0; i--)
	{
		int toFind = m_matrix[i][termToLook];
		for (int t = 0; t < termToLook; t++)
			m_matrix[i][t] *= m_finalCoeffs[t];
		for (int j = 0; j < m_matrixCols; j++)
		{
			if (j != m_matrixCols - 1 && j != termToLook)
				m_matrix[i][j] *= -1;
		}

		int sum = m_matrix[i][m_matrixCols - 1];
		for (int k = 0; k < termToLook; k++)
			sum += m_matrix[i][k];

		m_finalCoeffs[termToLook] = sum / toFind;
		termToLook++;
		if (i == 0 && termToLook == m_matrixCols - 2)
		{
			m_finalCoeffs[termToLook] = m_matrix[i][m_matrixCols - 1];
			break;
		}
	}
	printDerivedExpression();
}

void ProcessExprReverse::printDerivedExpression()
{
	int power = m_maxDegree;
	std::cout << "\n\nDerived Expression is: ";
	for (int i = 0; i < m_matrixRows; i++)
	{
		if (m_finalCoeffs[i] != 0)
		{
			if (m_finalCoeffs[i] > 0 && i > 0)
				std::cout << "+";

			if (m_finalCoeffs[i] != 1)
				std::cout << m_finalCoeffs[i];
			if (i != m_matrixRows - 1)
				std::cout << "x";
			if (power > 0 && power != 1)
				std::cout << "^" << power;
		}
		power--;
	}
}

void ProcessExprReverse::process()
{
	system("cls");
	FileHandler fh = FileHandler(m_outputSetS);
	printAllOutputSets();

	if (m_forExpression)
		askOutputIndex();
}