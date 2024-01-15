#include "CmdInterface.h"

int main()
{
	CmdInterface cmdInterface = CmdInterface();

	while (cmdInterface.IsRunning())
		cmdInterface.Update();

	return 0;
}