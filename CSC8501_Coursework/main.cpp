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

//5x^3 - 3x^2 + 8x - 100
void ParsePoly(const char* str, int str_size, Poly& poly)
{
	int i = 0;
	bool coeffIsNeg = false;
	//char* start = str;
	while (*str)
	{
		int coeff = 1;
		int power = 1;
		char* end;
		Term term;

		if (*str == '-')
		{
			coeffIsNeg = true;
			str++;
		}
		else if (*str == '+')
		{
			coeffIsNeg = false;
			str++;
		}

		coeff = strtol(str, &end, 10);
		if (str == end)	coeff = 1;
		coeff *= coeffIsNeg ? -1 : 1;
		str = end;

		if (*str == 'x')
		{
			str++;
			if (*str == '^')
			{
				str++;
				power = strtol(str, &end, 10);
				if (str == end)	power = 1;
				str = end;
			}
		}

		term = Term(coeff, power);
		poly.AddTerm(term);

		std::cout << "Term: " << term;
		std::cout << "\nCoeff: " << term.getCoeff();
		std::cout << "\nPower: " << term.getPower();
		std::cout << std::endl << "\n";
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

//void ParsePoly(const char* str, Poly& poly)
//{
//	parser_ctx_t ctx;
//	ctx.str = str;
//
//	while (*ctx.str)
//		poly.termsList.push_back(GetTerm(&ctx));
//}

int main()
{
	std::cout << "Enter the Expression: ";
	std::string polyStr("-5x^3 - 3x^2 + 8x - 100");
	std::getline(std::cin, polyStr);
	//cin >> polyStr;

	polyStr.erase(remove_if(polyStr.begin(), polyStr.end(), isspace), polyStr.end());

	std::cout << "\nYour Expression is: " << polyStr << std::endl;

	Poly poly = Poly();
	ParsePoly(polyStr.c_str(), polyStr.size(), poly);
	//ParsePoly(polyStr.c_str(), poly);
}