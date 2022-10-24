#include <numeric>
#include "Poly.h"

void Poly::addTerm(const Term& T)
{
	m_termsList.push_back(T);
}

void Poly::calculatePoly(const int& start, const int& end, std::vector<int>& v)
{
	if (m_termsList.size() <= 0)
		return;

	for (int i = start; i <= end; i++)
	{
		/*int val = std::accumulate(m_termsList.begin(), m_termsList.end(), 0,
			[i, val](int j, const Term& T)
		{
				return T.getCalculatedVal(i) + val;
		});*/

		int val = 0;
		for (int j = 0; j < m_termsList.size(); j++)
			val += m_termsList[j].getCalculatedVal(i);

		v.push_back(val);
	}
}

std::ostream& operator<<(std::ostream& os, const Poly& P)
{
	for (size_t i = 0; i < P.m_termsList.size(); i++)
	{
		if (P.m_termsList[i].getCoeff() > 0 && i != 0)
			os << "+" << P.m_termsList[i];
		else
			os << P.m_termsList[i];
	}
	return os;
}

std::string Poly::to_str()
{
	if (m_termsList.size() == 0) return std::string();
	
	std::string pStr;
	for (size_t i = 0; i < m_termsList.size(); i++)
		pStr += (m_termsList[i].getCoeff() > 0 && i != 0) ? "+" + m_termsList[i].to_str() : m_termsList[i].to_str();

	return pStr;
}