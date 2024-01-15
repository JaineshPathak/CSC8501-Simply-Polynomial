#pragma once
#include "ProcessExprBase.h"
#include "Poly.h"
#include "Utils.h"

class ProcessExprReverse : public ProcessExprBase
{
public:
	ProcessExprReverse();
	ProcessExprReverse(const int& _mode);
	~ProcessExprReverse();

public:
	virtual void Process() override;

protected:
	void PrintAllOutputSets();
	void AskOutputIndex();

	void ParseOutputSetString(const std::string& strSet);
	void StartDifferentiateProcess();

	void PrepareMatrixProcess();
	void StartMatrixProcess();
	
	void StartCoefficientsHunt();
	
	void PrintDerivedExpression();
	void PrintDerivedExpressionBatch();
	
	void BatchProcessAllSets();

private:
	int m_Mode = 0;		//1 - Single Expression, 2 - Batch Expression
	bool m_BatchProcessMode;

	std::vector<std::string> m_OutputSetS;
	std::vector<int> m_OutputSetN;

	std::vector<std::vector<int>> m_Matrix;
	int m_MaxDegree;
	int m_OutputSetNSize;
	int m_MatrixRows, m_MatrixCols;
	
	int* m_FinalCoeffs;

	std::string m_FinalExpressionsStr;
};