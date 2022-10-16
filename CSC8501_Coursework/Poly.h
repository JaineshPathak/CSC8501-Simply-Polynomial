#pragma once
#include <vector>
#include "Term.h"

class Poly
{
private:
	std::vector<Term> m_termsList;

public:
	void addTerm(const Term& T);
};