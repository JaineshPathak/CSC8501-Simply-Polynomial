#pragma once
#include <string>

namespace ParserUtils
{
	static int getNumberFromString(const char** str)
	{
		char* end;
		int n = std::strtol(*str, &end, 10);

		if (*str == end)
			n = 1;

		*str = end;

		return n;
	}

	static int getNumberFromString(const char** str, int& n)
	{
		char* end;
		n = std::strtol(*str, &end, 10);

		if (*str == end)
			n = 1;

		*str = end;

		return n;
	}
};