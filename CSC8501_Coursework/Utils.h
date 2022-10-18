#pragma once
#include <string>

namespace Utils
{
	static void printVector(const std::vector<int>& v)
	{
		std::cout << "\nSize: " << v.size() << "\n";
		for (int i : v)
			std::cout << i << " ";
	}

	static bool isVectorConstant(const std::vector<int>& v)
	{
		if (v.size() <= 0)
			return false;

		for (int i = 0; i < v.size(); i++)
		{
			if (v[i] != v[0])
				return false;
		}

		return true;
	}

	static std::vector<int> getDifferentiateVector(const std::vector<int> v, const int n)
	{
		std::vector<int> deltaVect;

		for (int i = 1; i < n; i++)
			deltaVect.push_back(v[i] - v[i - 1]);

		return deltaVect;
	}

	static int factorial(int n)
	{
		return (n > 1) ? n * factorial(n - 1) : 1;
	}

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