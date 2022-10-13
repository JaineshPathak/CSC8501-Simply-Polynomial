#pragma once
#include <iostream>
#include <math.h>
#include <string>

class Term
{
private:
	int m_coeff;
	int m_power;

public:
	Term() : m_coeff(1), m_power(1)
	{
	}

	Term(int _c, int _v, int _p) : m_coeff(_c), m_power(_p)
	{
	}

	Term(const Term& term)
	{
		m_coeff = term.m_coeff;
		m_power = term.m_power;
	}

	friend std::ostream& operator<<(std::ostream& os, const Term& T);

private:
	int parseCoefficient(const char* str);
	int parseExponent(const char* str);

	int getSign(const char* str);
	int getNumberDigit(const char* str);

public:
	int getCoeff();
	int getPower();
	int getCalculatedVal(int _v);

	void tryParsing(const char* str);
};