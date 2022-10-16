#include "ParserUtils.h"
#include "Poly.h"
#include "Term.h"

//typedef struct parser_ctx_t 
//{
//	const char* str;
//} parser_ctx_t;
//
//int GetSign(parser_ctx_t* ctx)
//{
//	int s = 1;
//
//	if (*ctx->str == '+')
//		ctx->str++;
//	else if (*ctx->str == '-')
//	{
//		s = -1;
//		ctx->str++;
//	}
//
//	return s;
//}
//
//int GetDigit(parser_ctx_t* ctx)
//{
//	int d;
//	char* end;
//	d = std::strtol(ctx->str, &end, 10);
//
//	if (ctx->str == end)
//		d = 1;
//
//	ctx->str = end;
//
//	return d;
//}
//
//int GetCoeff(parser_ctx_t* ctx)
//{
//	int s = GetSign(ctx);
//	int c = GetDigit(ctx);
//
//	return s * c;
//}
//
//int GetExpo(parser_ctx_t* ctx)
//{
//	int e = 1;
//	if (*ctx->str == 'x')
//	{
//		ctx->str++;
//		if (*ctx->str == '^')
//		{
//			ctx->str++;
//			e = GetDigit(ctx);
//		}
//	}
//
//	return e;
//}
//
//Term GetTerm(parser_ctx_t* ctx)
//{
//	Term term;
//
//	int c = GetCoeff(ctx);
//	int e = GetExpo(ctx);
//
//	term = Term(c, e);
//
//	std::cout << "Term: " << term;
//	std::cout << "\nCoeff: " << term.getCoeff();
//	std::cout << "\nPower: " << term.getPower();
//	std::cout << std::endl << "\n";
//
//	return term;
//}

struct strIndex
{
	const char* str;
};

void parsePoly(strIndex* strIndex, int str_size, Poly& poly);
int checkSign(strIndex* strIndex);
int checkExponent(strIndex* strIndex, bool& coeffIsConstant);

//5x^3 - 3x^2 + 8x - 100
void parsePoly(strIndex* strIndex, int str_size, Poly& poly)
{
	while (*strIndex->str)
	{
		int coeff = 1, power = 1;
		bool coeffIsConstant = false;

		int sign = checkSign(strIndex);
		ParserUtils::getNumberFromString(&strIndex->str, coeff);
		coeff *= sign;

		power = checkExponent(strIndex, coeffIsConstant);

		Term term = Term(coeff, power, coeffIsConstant);
		poly.addTerm(term);

		std::cout << "Term: " << term;
		std::cout << "\nCoeff: " << term.getCoeff();
		std::cout << "\nPower: " << term.getPower();
		std::cout << "\nConstant?: " << term.isConstant();
		std::cout << std::endl << "\n";

		if (coeffIsConstant)
			break;
	}
#pragma region OLD
#if 0
	while (0)
	{
		int coeff = 1;
		int power = 1;
		char* end;

		Term term;

		if (isdigit(str[i]) && str[i + 1] == 'x')
		{
			coeff = str[i] - '0';					//5
			if (coeffIsNeg)
				coeff *= -1;

			i++;
			if (str[i] == 'x')						//5x
			{
				i++;
				if (str[i] == '^')					//5x^
				{
					i++;
					if (isdigit(str[i]))
						power = str[i] - '0';		//5x^3
				}
			}

			term = Term(coeff, power);
			poly.termsList.push_back(term);

			std::cout << "Term: " << term;
			std::cout << "\nCoeff: " << term.getCoeff();
			std::cout << "\nPower: " << term.getPower();
			std::cout << std::endl << "\n";
		}  
		if (str[i] == '-')
		{
			coeffIsNeg = true;
			i++;
		}
		else if (str[i] == '+')
		{
			coeffIsNeg = false;
			i++;
		}
		else
			i++;

		//coeff = std::strtol()
	}
#endif
#pragma endregion
}

int checkSign(strIndex* strIndex)
{
	int sign = 1;

	if (*strIndex->str == '-')
	{
		sign = -1;
		strIndex->str++;
	}
	else if (*strIndex->str == '+')
		strIndex->str++;

	return sign;
}

int checkExponent(strIndex* strIndex, bool& coeffIsConstant)
{
	int power = 0;
	if (*strIndex->str == 'x')
	{
		power = 1;
		strIndex->str++;
		if (*strIndex->str == '^')
		{
			strIndex->str++;
			ParserUtils::getNumberFromString(&strIndex->str, power);
		}
	}
	else
		coeffIsConstant = true;

	return power;
}

int main()
{
	std::cout << "Enter the Expression: ";
	std::string polyStr("-5x^3 - 3x^2 + 8x - 100");
	std::getline(std::cin, polyStr);
	//cin >> polyStr;

	polyStr.erase(remove_if(polyStr.begin(), polyStr.end(), isspace), polyStr.end());

	std::cout << "\nYour Expression is: " << polyStr << std::endl;

	Poly poly = Poly();
	strIndex strIndexer;
	strIndexer.str = polyStr.c_str();

	parsePoly(&strIndexer, polyStr.size(), poly);

	int startNum = 0, lastNum = 0;
	std::cout << "Enter First and Last Num: ";
	std::cin >> startNum >> lastNum;
	//ParsePoly(polyStr.c_str(), poly);
}