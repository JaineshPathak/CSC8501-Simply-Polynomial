#pragma once
#include <iostream>
#include <cmath>
#include <thread>
#include <fstream>
#include "Rules.h"
#include "Poly.h"
#include "ParserUtils.h"

class CmdInterface
{
private:
	int m_state;		//0 - Main Menu, 1 - Generate Output Sets, 2 - Derive Expression, 3 - Exit
	bool m_isRunning;

public:
	CmdInterface();
	~CmdInterface();

	bool isRunning() const;
	void update();

private:
	struct strIndex;

	void parsePoly(strIndex* strIndex, int str_size, Poly& poly);
	int checkSign(strIndex* strIndex);
	int checkExponent(strIndex* strIndex, bool& coeffIsConstant);

	void askToContinue(int toState);
	void askSaveFile(const std::vector<int>& outputSet);

	void showMainMenu();
	void enterExpression();
	void deriveExpression();

	void saveSetToFile(const std::string& fileName, const std::vector<int>& outputSet);
	void readSetFromFile(std::string fileName);
};

void inputStringExpression(std::string& polyStr);
void inputRangeAndCalc(int& start, int& end, Poly& poly, std::vector<int>& outputSet);