#pragma once
#include "ProcessExprBase.h"
#include "Poly.h"
#include "Utils.h"

class ProcessExprReverse : public ProcessExprBase
{
private:
	int m_mode = 0;		//1 - Single Expression, 2 - Batch Expression

	std::vector<std::string> m_outputSetS;
	std::vector<int> m_outputSetN;
	std::vector<std::vector<int>> m_matrix;
	int m_maxDegree;
	int m_outputSetNSize;
	int m_matrixRows, m_matrixCols;
	int* m_finalCoeffs;

	std::string m_finalExpressionsStr;

public:
	ProcessExprReverse() : m_mode(0) { process(); }
	ProcessExprReverse(const int& _mode) : m_mode(_mode) { process(); }
	~ProcessExprReverse();

private:
	void printAllOutputSets();
	void askOutputIndex();
	void parseOutputSetString(const std::string& strSet, const bool batchMode = false);
	void startDifferentiateProcess(const bool batchMode = false);
	void prepareMatrixProcess(const bool batchMode = false);
	void startMatrixProcess(const bool batchMode = false);
	void startCoefficientsHunt(const bool batchMode = false);
	void printDerivedExpression(const bool batchMode = false);
	//void printDerivedExpressionBatch();
	void batchProcessAllSets();

public:
	void process() override;
};