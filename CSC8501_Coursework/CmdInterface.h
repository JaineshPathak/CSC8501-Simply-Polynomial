#pragma once
#include <iostream>
#include "ProcessExprForward.h"
#include "ProcessExprReverse.h"

class CmdInterface
{
private:
	char m_state;		//0 - Main Menu, 1 - Generate Output Set, 2 - Show Output Sets, 3 - Derive Expression, 4 - Derive Expression (batch), 5 - Exit
	bool m_isRunning;

public:
	CmdInterface();
	~CmdInterface();

	bool isRunning() const;
	void update();

private:
	void showMainMenu();
	void askToContinue(char toState);
};
