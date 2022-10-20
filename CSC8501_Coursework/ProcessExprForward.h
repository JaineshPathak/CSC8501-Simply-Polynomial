#pragma once
#include "ProcessExprBase.h"
#include "Poly.h"
#include "Utils.h"
#include "Rules.h"

class ProcessExprForward : public ProcessExprBase
{
private:
	struct m_strIndex;
	std::vector<int> m_outputSet;

public:
	ProcessExprForward();
	~ProcessExprForward();

private:
	void inputStringExpression(std::string& polyStr);
	void inputRangeAndCalc(Poly& poly);

	void parsePoly(m_strIndex* strIndex, Poly& poly);
	int checkSign(m_strIndex* strIndex);
	int checkExponent(m_strIndex* strIndex, bool& coeffIsConstant);

	void askSaveFile();

public:
	void process() override;
};