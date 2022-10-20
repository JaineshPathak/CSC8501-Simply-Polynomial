#include "ProcessExprReverse.h"

ProcessExprReverse::~ProcessExprReverse()
{
	delete[] m_finalCoeffs;
}

void ProcessExprReverse::printAllOutputSets()
{
	if (m_outputSetS.size() == 0) return;

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

void ProcessExprReverse::parseOutputSetString(const std::string& strSet, const bool batchMode)
{
	if (batchMode) m_outputSetN.clear();

	int num = 0;
	std::stringstream ss(strSet);
	while (ss >> num)
		m_outputSetN.push_back(num);

	startDifferentiateProcess(batchMode);
}

void ProcessExprReverse::startDifferentiateProcess(const bool batchMode)
{
	m_maxDegree = 0;
	m_outputSetNSize = m_outputSetN.size();
	std::vector<int> deltaSet, prevDeltaSet = m_outputSetN;
	do
	{
		m_maxDegree++; m_outputSetNSize--;
		deltaSet = Utils::getDifferentiateVector(prevDeltaSet, m_outputSetNSize);
		//Utils::printVector(deltaSet);
		prevDeltaSet = deltaSet;
	} while (!Utils::isVectorConstant(deltaSet));
	prepareMatrixProcess(batchMode);
}

void ProcessExprReverse::prepareMatrixProcess(const bool batchMode)
{
	if (batchMode) Utils::clearMatrixVector(m_matrix, m_matrixRows);

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
	startMatrixProcess(batchMode);
}

void ProcessExprReverse::startMatrixProcess(const bool batchMode)
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
	startCoefficientsHunt(batchMode);
}

void ProcessExprReverse::startCoefficientsHunt(const bool batchMode)
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
	batchMode ? printDerivedExpressionBatch() : printDerivedExpression();
}

void ProcessExprReverse::printDerivedExpression()
{
	int power = m_maxDegree;
	std::cout << "\n\nDerived Expression: ";
	Poly poly = Poly();
	for (int i = 0; i < m_matrixRows; i++)
	{
		Term term = Term(m_finalCoeffs[i], power, i == m_matrixRows - 1);
		poly.addTerm(term);
		power--;
	}
	std::cout << poly;
}

void ProcessExprReverse::printDerivedExpressionBatch()
{
	int power = m_maxDegree;
	for (int i = 0; i < m_matrixRows; i++)
	{
		if (m_finalCoeffs[i] > 0 && i != 0)
			m_finalExpressionsStr += "+";

		if (m_finalCoeffs[i] != 0)
		{
			if (m_finalCoeffs[i] == 1)
				m_finalExpressionsStr += (i == m_matrixRows - 1) ? "1" : "x";
			else if(m_finalCoeffs[i] == -1 && i != m_matrixRows - 1)
				m_finalExpressionsStr += "-x";
			else
			{
				m_finalExpressionsStr += std::to_string(m_finalCoeffs[i]);
				if (i != m_matrixRows - 1)
					m_finalExpressionsStr += "x";
			}
		}
		if (power > 1 && m_finalCoeffs[i] != 0)
			m_finalExpressionsStr += "^" + std::to_string(power);
		power--;
	}
	m_finalExpressionsStr += "\n";
}

void ProcessExprReverse::batchProcessAllSets()
{
	if (m_outputSetS.size() == 0) return;
	
	m_finalExpressionsStr.clear();
	std::cout << "\n\nExpressions:\n";
	for (size_t i = 0; i < m_outputSetS.size(); i++)
		parseOutputSetString(m_outputSetS[i], true);

	std::cout << m_finalExpressionsStr << "\n";

	FileHandler fh = FileHandler();
	fh.saveFile(m_finalExpressionsStr);
}

void ProcessExprReverse::process()
{
	system("cls");
	FileHandler fh = FileHandler(m_outputSetS);
	printAllOutputSets();
	switch (m_mode)
	{
		case 1:
			askOutputIndex();
			break;
		case 2:
			batchProcessAllSets();
			break;
		default:
			return;
	}
}