#pragma once
#include <vector>
#include "Term.h"

class Poly
{
public:
	void AddTerm(const Term& T);
	void CalculatePoly(const int &start, const int &end, std::vector<int>& v);

	friend std::ostream& operator<<(std::ostream& os, const Poly& P);

private:
	std::vector<Term> m_TermsList;
};