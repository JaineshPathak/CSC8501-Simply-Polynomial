#pragma once
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

class FileHandler
{
public:
	FileHandler();
	FileHandler(std::vector<std::string>& outputSetStr);
	~FileHandler();

	void ReadOutputSetFile(std::vector<std::string>& outputSetStr);
	void SaveFile(const std::vector<int>& outputSet);
	void SaveFile(const std::string& expressionStr);

private:
	const std::string m_OutputSetFilename = "OutputSet.txt";
	const std::string m_ExpressionFilename = "Expression.txt";
};