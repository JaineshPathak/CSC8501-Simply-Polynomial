#pragma once
#include "ProcessExprBase.h"
#include "Utils.h"

class ProcessExprReverse : public ProcessExprBase
{
private:
	bool m_forExpression;
	std::vector<std::string> m_outputSetS;
	std::vector<int> m_outputSetN;
	std::vector<std::vector<int>> m_matrix;
	int m_maxDegree;
	int m_outputSetNSize;
	int m_matrixRows, m_matrixCols;
	int* m_finalCoeffs;

public:
	ProcessExprReverse();
	ProcessExprReverse(const bool _forExpression);
	~ProcessExprReverse();

private:
	void printAllOutputSets();
	void askOutputIndex();
	void parseOutputSetString(const std::string& strSet);
	void startDifferentiateProcess();
	void prepareMatrixProcess();
	void startMatrixProcess();
	void startCoefficientsHunt();
	void printDerivedExpression();

public:
	void process() override;
};