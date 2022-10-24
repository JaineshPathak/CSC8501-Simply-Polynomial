#include "Term.h"

int Term::getCoeff() const { return m_coeff; }

int Term::getPower() const { return m_power; }

bool Term::isConstant() const { return m_coeffIsConstant; }

std::ostream& operator<<(std::ostream& os, const Term& T)
{
	//os << " ";
	if (!T.m_coeffIsConstant)
	{
		if (T.m_coeff != 0)
		{
			if (T.m_coeff == 1)
				os << "x";
			else if (T.m_coeff == -1)
				os << "-x";
			else
				os << T.m_coeff << "x";
		}

		if (T.m_power > 1 && T.m_coeff != 0)
			os << "^" << T.m_power;
		//os << T.m_coeff << "x" << "^" << T.m_power;
	}
	else if(T.m_coeffIsConstant && T.m_coeff != 0)
		os << T.m_coeff;
	return os;
}

int Term::getCalculatedVal(const int _v) const
{
	if (m_power < 0)
		return 0;

	return m_coeff * pow(_v, m_power);
}

std::string Term::to_str()
{
	std::string tStr;
	if (!m_coeffIsConstant)
	{
		if (m_coeff != 0)
		{
			if (m_coeff == 1)
				tStr += "x";
			else if (m_coeff == -1)
				tStr += "-x";
			else
				tStr += std::to_string(m_coeff) + "x";
		}

		if (m_power > 1 && m_coeff != 0)
			tStr += "^" + std::to_string(m_power);
	}
	else if (m_coeffIsConstant && m_coeff != 0)
		tStr += std::to_string(m_coeff);

	return tStr;
}