#include "ProcessExprReverse.h"

ProcessExprReverse::ProcessExprReverse() :
	m_Mode(0),
	m_BatchProcessMode(false),
	m_MaxDegree(0),
	m_OutputSetNSize(0),
	m_MatrixRows(0), m_MatrixCols(0),
	m_FinalExpressionsStr("")
{
	Process();
}

ProcessExprReverse::ProcessExprReverse(const int& _mode) :
	m_Mode(_mode),
	m_BatchProcessMode(false),
	m_MaxDegree(0),
	m_OutputSetNSize(0),
	m_MatrixRows(0), m_MatrixCols(0),
	m_FinalExpressionsStr("")
{
	Process();
}

ProcessExprReverse::~ProcessExprReverse()
{
	delete[] m_FinalCoeffs;
}

void ProcessExprReverse::Process()
{
	system("cls");
	FileHandler fh = FileHandler(m_OutputSetS);
	PrintAllOutputSets();
	
	switch (m_Mode)
	{
	case 1:
		AskOutputIndex();
		break;
	case 2:
		BatchProcessAllSets();
		break;
	default:
		return;
	}
}

void ProcessExprReverse::PrintAllOutputSets()
{
	if (m_OutputSetS.size() == 0) return;

	int index = 0;
	std::cout << "Output Sets:\n[Index]\t[Sets]\n";
	for (size_t i = 0; i < m_OutputSetS.size(); i++)
		std::cout << index++ << "\t" << m_OutputSetS[i] << std::endl;
}

void ProcessExprReverse::AskOutputIndex()
{
	std::cout << "\nEnter the [Index] to select the output set: ";
	int index; std::cin.ignore(); std::cin >> index;

	if (index < 0 || index > (int)m_OutputSetS.size() - 1)
	{
		std::cout << "\nInvalid [Index] entered!";
		return;
	}

	ParseOutputSetString(m_OutputSetS[index]);
}

void ProcessExprReverse::ParseOutputSetString(const std::string& strSet)
{
	if (m_BatchProcessMode) m_OutputSetN.clear();

	int num = 0;
	std::stringstream ss(strSet);
	while (ss >> num)
		m_OutputSetN.push_back(num);

	StartDifferentiateProcess();
}

void ProcessExprReverse::StartDifferentiateProcess()
{
	m_MaxDegree = 0;
	m_OutputSetNSize = m_OutputSetN.size();
	std::vector<int> deltaSet, prevDeltaSet = m_OutputSetN;
	do
	{
		m_MaxDegree++; m_OutputSetNSize--;
		deltaSet = Utils::GetDifferentiateVector(prevDeltaSet, m_OutputSetNSize);
		//Utils::printVector(deltaSet);
		prevDeltaSet = deltaSet;
	} while (!Utils::IsVectorConstant(deltaSet));

	PrepareMatrixProcess();
}

void ProcessExprReverse::PrepareMatrixProcess()
{
	if (m_BatchProcessMode) Utils::ClearMatrixVector(m_Matrix, m_MatrixRows);

	m_MatrixRows = m_MaxDegree + 1; 
	m_MatrixCols = m_MaxDegree + 2;
	Utils::MorphMatrixVect(m_Matrix, m_MatrixRows, m_MatrixCols);
	for (int i = 0; i < m_MatrixRows; i++)
	{
		int matPower = m_MaxDegree;
		for (int j = 0; j < m_MatrixCols; j++)
		{
			if (j >= 0 && j < m_MatrixCols - 3)
			{
				m_Matrix[i][j] = 1 * pow(i, matPower);
				matPower--;
			}
			else if (j == m_MatrixCols - 2)
				m_Matrix[i][j] = 1;
			else if (j == m_MatrixCols - 1)
				m_Matrix[i][j] = m_OutputSetN[i];
			else
				m_Matrix[i][j] = i;
		}
	}

	StartMatrixProcess();
}

void ProcessExprReverse::StartMatrixProcess()
{
	int rowsIgnored = 0;
	std::vector<std::vector<int>> matrixCopy;

	for (int k = 0; k < m_MaxDegree; k++)
	{
		matrixCopy = m_Matrix;
		for (int i = rowsIgnored; i < m_MatrixRows; i++)
		{
			if (i == rowsIgnored)
				continue;

			for (int j = 0; j < m_MatrixCols; j++)
				m_Matrix[i][j] = matrixCopy[i][j] - matrixCopy[i - 1][j];
		}
		rowsIgnored++;
	}

	StartCoefficientsHunt();
}

void ProcessExprReverse::StartCoefficientsHunt()
{
	m_FinalCoeffs = new int[m_MatrixRows] {0};

	int termToLook = 1;
	m_FinalCoeffs[0] = m_Matrix[m_MatrixRows - 1][m_MatrixCols - 1] / m_Matrix[m_MatrixRows - 1][0];	//1st Coeff or 'a'
	for (int i = m_MatrixRows - 2; i >= 0; i--)
	{
		int toFind = m_Matrix[i][termToLook];
		for (int t = 0; t < termToLook; t++)
			m_Matrix[i][t] *= m_FinalCoeffs[t];
		for (int j = 0; j < m_MatrixCols; j++)
		{
			if (j != m_MatrixCols - 1 && j != termToLook)
				m_Matrix[i][j] *= -1;
		}

		int sum = m_Matrix[i][m_MatrixCols - 1];
		for (int k = 0; k < termToLook; k++)
			sum += m_Matrix[i][k];

		m_FinalCoeffs[termToLook] = sum / toFind;
		termToLook++;
		if (i == 0 && termToLook == m_MatrixCols - 2)
		{
			m_FinalCoeffs[termToLook] = m_Matrix[i][m_MatrixCols - 1];
			break;
		}
	}
	m_BatchProcessMode ? PrintDerivedExpressionBatch() : PrintDerivedExpression();
}

void ProcessExprReverse::PrintDerivedExpression()
{
	int power = m_MaxDegree;
	std::cout << "\n\nDerived Expression: ";
	Poly poly = Poly();
	for (int i = 0; i < m_MatrixRows; i++)
	{
		Term term = Term(m_FinalCoeffs[i], power, i == m_MatrixRows - 1);
		poly.AddTerm(term);
		power--;
	}
	std::cout << poly;
}

void ProcessExprReverse::PrintDerivedExpressionBatch()
{
	int power = m_MaxDegree;
	for (int i = 0; i < m_MatrixRows; i++)
	{
		if (m_FinalCoeffs[i] > 0 && i != 0)
			m_FinalExpressionsStr += "+";

		if (m_FinalCoeffs[i] != 0)
		{
			if (m_FinalCoeffs[i] == 1)
				m_FinalExpressionsStr += (i == m_MatrixRows - 1) ? "1" : "x";
			else if(m_FinalCoeffs[i] == -1 && i != m_MatrixRows - 1)
				m_FinalExpressionsStr += "-x";
			else
			{
				m_FinalExpressionsStr += std::to_string(m_FinalCoeffs[i]);
				if (i != m_MatrixRows - 1)
					m_FinalExpressionsStr += "x";
			}
		}
		if (power > 1 && m_FinalCoeffs[i] != 0)
			m_FinalExpressionsStr += "^" + std::to_string(power);
		power--;
	}
	m_FinalExpressionsStr += "\n";
}

void ProcessExprReverse::BatchProcessAllSets()
{
	if (m_OutputSetS.size() == 0) return;
	
	m_BatchProcessMode = true;
	m_FinalExpressionsStr.clear();

	std::cout << "\n\nExpressions:\n";
	for (size_t i = 0; i < m_OutputSetS.size(); i++)
		ParseOutputSetString(m_OutputSetS[i]);

	std::cout << m_FinalExpressionsStr << "\n";

	FileHandler fh = FileHandler();
	fh.SaveFile(m_FinalExpressionsStr);

	m_BatchProcessMode = false;
}