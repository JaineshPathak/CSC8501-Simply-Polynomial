#include "Term.h"

std::ostream& operator<<(std::ostream& os, const Term& T)
{
	//os << " ";
	if (!T.m_CoeffIsConstant)
	{
		if (T.m_Coeff != 0)
		{
			if (T.m_Coeff == 1)
				os << "x";
			else if (T.m_Coeff == -1)
				os << "-x";
			else
				os << T.m_Coeff << "x";
		}

		if (T.m_Power > 1 && T.m_Coeff != 0)
			os << "^" << T.m_Power;
		//os << T.m_coeff << "x" << "^" << T.m_power;
	}
	else if(T.m_CoeffIsConstant && T.m_Coeff != 0)
		os << T.m_Coeff;

	return os;
}

int Term::GetCalculatedVal(const int& _v)
{
	if (m_Power < 0) return 0;

	return m_Coeff * (int)pow(_v, m_Power);
}