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