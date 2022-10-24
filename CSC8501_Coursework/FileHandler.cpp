#include "FileHandler.h"

FileHandler::FileHandler()
{
}

FileHandler::FileHandler(std::vector<std::string>& outputSetStr)
{
	readOutputSetFile(outputSetStr);
}

FileHandler::~FileHandler()
{
}

void FileHandler::readOutputSetFile(std::vector<std::string>& outputSetStr)
{
	std::ifstream fileReader(m_outputSetFilename, std::ios::in);
	fileReader.exceptions(std::ifstream::badbit);
	try
	{
		if (!fileReader.good())	throw std::ifstream::failure("Probably file doesn't exists or Badbit Error");
		if (fileReader.peek() == EOF) throw std::ifstream::failure("File is Empty!");

		std::string line/*, finalLine*/;
		while (std::getline(fileReader, line, '\n'))
		{
			line.erase(remove(line.begin(), line.end(), ','), line.end());
			outputSetStr.push_back(line);
		}
		fileReader.close();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "\nException Occured: Failed reading file: " << m_outputSetFilename << "\nMessage: " << e.what();
	}
}

void FileHandler::saveFile(const std::vector<int>& outputSet)
{
	std::ofstream fileWriter(m_outputSetFilename, std::ios::app);
	fileWriter.exceptions(std::ofstream::badbit | std::ofstream::failbit);
	try
	{
		for (size_t i = 0; i < outputSet.size(); i++)
			(i == outputSet.size() - 1) ? fileWriter << outputSet[i] : fileWriter << outputSet[i] << ", ";
		fileWriter << "\n";
		fileWriter.close();
	}
	catch (std::ofstream::failure& e) {
		std::cout << "\nException Occured: Failed writing to file: " << m_outputSetFilename << "\nMessage: " << e.what();
	}
	std::cout << "\nFile Saved: " << m_outputSetFilename;
}

void FileHandler::saveFile(const std::string& expressionStr)
{
	std::ofstream fileWriter(m_expressionFilename, std::ios::out);
	fileWriter.exceptions(std::ofstream::badbit | std::ofstream::failbit);
	try
	{
		fileWriter << expressionStr;
		fileWriter.close();
	}
	catch (std::ofstream::failure& e)
	{
		std::cout << "\nException Occured: Failed writing to file: " << m_expressionFilename << "\nMessage: " << e.what();
	}
	std::cout << "\nFile Saved: " << m_expressionFilename;
}