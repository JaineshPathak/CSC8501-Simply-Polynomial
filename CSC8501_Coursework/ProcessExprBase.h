#pragma once
#include <iostream>
#include "FileHandler.h"

class ProcessExprBase
{
public:
	ProcessExprBase() {};
	virtual ~ProcessExprBase() {};

	virtual void Process() = 0;
};