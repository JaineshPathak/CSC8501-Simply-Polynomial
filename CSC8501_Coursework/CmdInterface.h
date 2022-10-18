#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "Rules.h"
#include "Poly.h"
#include "Utils.h"

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
	void processExpression();
	void deriveExpression(const std::vector<int> outputSet);

	void readFile(bool withExpression = false);
	void saveSetToFile(const std::string& fileName, const std::vector<int>& outputSet);

	void parseOutputSet(const std::vector<std::string>& outputLinesV);
	void getOutputSet(const std::string& strSet);
};

void inputStringExpression(std::string& polyStr);
void inputRangeAndCalc(int& start, int& end, Poly& poly, std::vector<int>& outputSet);
