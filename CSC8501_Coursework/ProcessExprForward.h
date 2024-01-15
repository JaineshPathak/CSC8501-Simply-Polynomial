#pragma once
#include "ProcessExprBase.h"
#include "Poly.h"
#include "Utils.h"
#include "Rules.h"

class ProcessExprForward : public ProcessExprBase
{
public:
	ProcessExprForward();
	~ProcessExprForward();

private:
	struct m_StrIndex;

protected:
	void InputStringExpression(std::string& polyStr);
	void InputRangeAndCalc(Poly& poly);

	void ParsePoly(m_StrIndex* strIndex, Poly& poly);
	int CheckSign(m_StrIndex* strIndex);
	int CheckExponent(m_StrIndex* strIndex, bool& coeffIsConstant);

	void AskSaveFile();

public:
	void Process() override;

private:
	std::vector<int> m_OutputSet;
};