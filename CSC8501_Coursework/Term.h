#pragma once
#include <iostream>
#include <math.h>
#include <string>

class Term
{
private:
	int m_coeff;
	int m_power;

	bool m_coeffIsConstant;

public:
	Term() : m_coeff(1), m_power(1), m_coeffIsConstant(false)
	{
	}

	Term(int _c, int _p) : m_coeff(_c), m_power(_p), m_coeffIsConstant(false)
	{
	}

	Term(int _c, int _p, bool _coeffIsConstant) : m_coeff(_c), m_power(_p), m_coeffIsConstant(_coeffIsConstant)
	{
	}

	Term(const Term& term)
	{
		m_coeff = term.m_coeff;
		m_power = term.m_power;

		m_coeffIsConstant = term.m_coeffIsConstant;
	}

	friend std::ostream& operator<<(std::ostream& os, const Term& T);

public:
	int getCoeff() const;
	int getPower() const;
	bool isConstant() const;
	int getCalculatedVal(const int _v) const;
};