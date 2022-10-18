#include "CmdInterface.h"

int main()
{
	CmdInterface cmdInterface = CmdInterface();
	while (cmdInterface.isRunning())
		cmdInterface.update();

	return 0;
}