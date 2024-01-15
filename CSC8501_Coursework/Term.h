#pragma once
#include <iostream>
#include <math.h>
#include <string>

class Term
{
public:
	Term() : m_Coeff(1), m_Power(1), m_CoeffIsConstant(false)
	{
	}

	Term(int _c, int _p) : m_Coeff(_c), m_Power(_p), m_CoeffIsConstant(false)
	{
	}

	Term(int _c, int _p, bool _coeffIsConstant) : m_Coeff(_c), m_Power(_p), m_CoeffIsConstant(_coeffIsConstant)
	{
	}

	Term(const Term& term)
	{
		m_Coeff = term.m_Coeff;
		m_Power = term.m_Power;

		m_CoeffIsConstant = term.m_CoeffIsConstant;
	}

	friend std::ostream& operator<<(std::ostream& os, const Term& T);

private:
	int m_Coeff;
	int m_Power;

	bool m_CoeffIsConstant;

public:
	int GetCalculatedVal(const int& _v);

	int GetCoeff() const { return m_Coeff; }
	int GetPower() const { return m_Power; }
	bool IsConstant() const { return m_CoeffIsConstant; }
};