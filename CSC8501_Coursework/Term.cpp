#include "Term.h"

int Term::getCoeff() { return m_coeff; }

int Term::getPower() { return m_power; }

bool Term::isConstant() { return m_coeffIsConstant; }

int Term::getCalculatedVal(int _v) const
{
	if (m_power < 0)
		return 0;

	return m_coeff * pow(_v, m_power);
}

std::ostream& operator<<(std::ostream& os, const Term& T)
{
	if(!T.m_coeffIsConstant)
		os << T.m_coeff << "x" << "^" << T.m_power;
	else
		os << T.m_coeff;
	return os;
}

int Term::parseCoefficient(const char* str)
{
	int c = getNumberDigit(str);
	int sign = getSign(str);

	return c * sign;
}

int Term::parseExponent(const char* str)
{
	int e = 1;

	if (*str == 'x')
	{
		str++;
		if (*str == '^')
		{
			str++;
			e = getNumberDigit(str);
		}
	}

	return e;
}

int Term::getSign(const char* str)
{
	int n = 1;

	if (*str == '-')
	{
		n = -1;
		str++;
	}
	else if (*str == '+')
		str++;

	return n;
}

int Term::getNumberDigit(const char* str)
{
	char* end;
	int n = strtol(str, &end, 10);

	if (str == end)
		n = 1;

	str = end;

	return n;
}