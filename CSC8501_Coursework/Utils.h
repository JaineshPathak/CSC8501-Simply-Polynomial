#pragma once
#include <string>

namespace Utils
{
	static void PrintVector(const std::vector<int>& v)
	{
		std::cout << "\nSize: " << v.size() << "\n";
		for (const int& i : v)
			std::cout << i << " ";
	}

	static void PrintMatrixVector(const std::vector<std::vector<int>>& matrix, const int& rows, const int& cols)
	{
		std::cout << "\n";
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
				std::cout << matrix[i][j] << "\t";
			
			std::cout << "\n";
		}
	}

	static void ClearMatrixVector(std::vector<std::vector<int>>& matrix, const int& rows)
	{
		for (int i = 0; i < rows; i++)
			matrix[i].clear();

		matrix.clear();
	}

	static bool IsVectorConstant(const std::vector<int>& v)
	{
		if (v.size() <= 0)
			return false;

		for (size_t i = 0; i < v.size(); i++)
			if (v[i] != v[0])
				return false;

		return true;
	}

	static std::vector<int> GetDifferentiateVector(const std::vector<int> v, const int n)
	{
		std::vector<int> deltaVect;
		for (int i = 1; i < n; i++)
			deltaVect.push_back(v[i] - v[i - 1]);

		return deltaVect;
	}

	static void MorphMatrixVect(std::vector<std::vector<int>>& matrix, const int& rows, const int& cols)
	{
		matrix.resize(rows);
		for (int i = 0; i < rows; i++)
			matrix[i].resize(cols);
	}

	static int Factorial(int n)
	{
		return (n > 1) ? n * Factorial(n - 1) : 1;
	}

	static void PrintArray(int* arr, int n)
	{
		std::cout << "\n";
		for (int i = 0; i < n; i++)
			std::cout << arr[i] << "\t";
	}

	static int GetNumberFromString(const char** str)
	{
		char* end;
		int n = std::strtol(*str, &end, 10);

		if (*str == end)
			n = 1;

		*str = end;

		return n;
	}

	static int GetNumberFromString(const char** str, int& n)
	{
		char* end;
		n = std::strtol(*str, &end, 10);

		if (*str == end)
			n = 1;

		*str = end;

		return n;
	}
};