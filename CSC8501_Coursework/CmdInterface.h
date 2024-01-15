#pragma once
#include <iostream>
#include "ProcessExprForward.h"
#include "ProcessExprReverse.h"

class CmdInterface
{
public:
	CmdInterface();
	~CmdInterface();

	bool IsRunning() const;
	void Update();

private:
	void ShowMainMenu();
	void AskToContinue(int toState);

	//0 - Main Menu, 1 - Generate Output Set, 2 - Show Output Sets, 3 - Derive Expression, 4 - Derive Expression (batch), 5 - Exit
	int m_State;
	bool m_IsRunning;
};
