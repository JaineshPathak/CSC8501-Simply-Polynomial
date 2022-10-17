#include "CmdInterface.h"

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

int main()
{
	CmdInterface cmdInterface = CmdInterface();
	while (cmdInterface.isRunning())
		cmdInterface.update();

	return 0;
}