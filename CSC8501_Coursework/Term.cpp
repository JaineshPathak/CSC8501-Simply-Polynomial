#include "Term.h"

int Term::getCoeff() { return m_coeff; }

int Term::getPower() { return m_power; }

bool Term::isConstant() { return m_coeffIsConstant; }

std::ostream& operator<<(std::ostream& os, const Term& T)
{
	if(!T.m_coeffIsConstant)
		os << T.m_coeff << "x" << "^" << T.m_power;
	else
		os << T.m_coeff;
	return os;
}

int Term::getCalculatedVal(const int _v) const
{
	if (m_power < 0)
		return 0;

	return m_coeff * pow(_v, m_power);
}