#pragma once
#include <vector>
#include "Term.h"

class Poly
{
private:
	std::vector<Term> m_termsList;

public:
	void addTerm(const Term& T);
	void calculatePoly(const int &start, const int &end, std::vector<int>& v);

	friend std::ostream& operator<<(std::ostream& os, const Poly& P);
};