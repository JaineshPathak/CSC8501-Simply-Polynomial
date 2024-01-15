#include "FileHandler.h"

FileHandler::FileHandler()
{
}

FileHandler::FileHandler(std::vector<std::string>& outputSetStr)
{
	ReadOutputSetFile(outputSetStr);
}

FileHandler::~FileHandler()
{
}

bool FileHandler::ReadOutputSetFile(std::vector<std::string>& outputSetStr)
{
	bool success{ true };

	std::ifstream fileReader(m_OutputSetFilename, std::ios::in);
	fileReader.exceptions(std::ifstream::badbit);
	try
	{
		if (!fileReader.good())
		{
			success = false;
			throw std::ifstream::failure("Probably file doesn't exists or badbit Error");
		}

		std::string line/*, finalLine*/;
		while (std::getline(fileReader, line, '\n'))
		{
			line.erase(remove(line.begin(), line.end(), ','), line.end());
			outputSetStr.push_back(line);
		}
		fileReader.close();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "\nException Occured: Failed reading file: " << m_OutputSetFilename << "\nMessage: " << e.what();
	}

	return success;
}

void FileHandler::SaveFile(const std::vector<int>& outputSet)
{
	std::ofstream fileWriter(m_OutputSetFilename, std::ios::app);
	fileWriter.exceptions(std::ofstream::badbit | std::ofstream::failbit);
	try
	{
		for (size_t i = 0; i < outputSet.size(); i++)
			(i == outputSet.size() - 1) ? fileWriter << outputSet[i] : fileWriter << outputSet[i] << ", ";
		fileWriter << "\n";
		fileWriter.close();
	}
	catch (std::ofstream::failure& e)
	{
		std::cout << "\nException Occured: Failed writing to file: " << m_OutputSetFilename << "\nMessage: " << e.what();
	}
	std::cout << "\nFile Saved: " << m_OutputSetFilename;
}

void FileHandler::SaveFile(const std::string& expressionStr)
{
	std::ofstream fileWriter(m_ExpressionFilename, std::ios::out);
	fileWriter.exceptions(std::ofstream::badbit | std::ofstream::failbit);
	try
	{
		fileWriter << expressionStr;
		fileWriter.close();
	}
	catch (std::ofstream::failure& e)
	{
		std::cout << "\nException Occured: Failed writing to file: " << m_ExpressionFilename << "\nMessage: " << e.what();
	}
	std::cout << "\nFile Saved: " << m_ExpressionFilename;
}