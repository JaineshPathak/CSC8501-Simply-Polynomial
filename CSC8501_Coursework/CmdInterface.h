#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "ProcessExprForward.h"
#include "ProcessExprReverse.h"
#include "Rules.h"
#include "Poly.h"
#include "Utils.h"
#include "FileHandler.h"

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
	void showMainMenu();
	void askToContinue(int toState);
};
