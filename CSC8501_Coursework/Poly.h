#pragma once
#include <vector>
#include "Term.h"

class Poly
{
private:
	std::vector<Term> m_termsList;

public:
	void AddTerm(const Term& T);
};