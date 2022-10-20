#pragma once
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

class FileHandler
{
private:
	const std::string m_outputSetFilename = "OutputSet.txt";
	const std::string m_expressionFilename = "Expression.txt";

public:
	FileHandler();
	FileHandler(std::vector<std::string>& outputSetStr);
	~FileHandler();

	void readOutputSetFile(std::vector<std::string>& outputSetStr);
	void saveFile(const std::vector<int>& outputSet);
	void saveFile(const std::string& expressionStr);
};