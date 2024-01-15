#include <numeric>
#include "Poly.h"

void Poly::AddTerm(const Term& T)
{
	m_TermsList.push_back(T);
}

void Poly::CalculatePoly(const int& start, const int& end, std::vector<int>& v)
{
	if (m_TermsList.size() <= 0)
		return;

	for (int i = start; i <= end; i++)
	{
		/*int val = std::accumulate(m_termsList.begin(), m_termsList.end(), 0,
			[i, val](int j, const Term& T)
		{
				return T.getCalculatedVal(i) + val;
		});*/

		int val = 0;
		for (int j = 0; j < (int)m_TermsList.size(); j++)
			val += m_TermsList[j].GetCalculatedVal(i);

		v.push_back(val);
	}
}

std::ostream& operator<<(std::ostream& os, const Poly& P)
{
	for (size_t i = 0; i < P.m_TermsList.size(); i++)
	{
		if (P.m_TermsList[i].GetCoeff() > 0 && i != 0)
			os << "+" << P.m_TermsList[i];
		else
			os << P.m_TermsList[i];
	}

	return os;
}
