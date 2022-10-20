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

void FileHandler::saveOutputSetFile(const std::vector<int>& outputSet)
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
	catch (std::ofstream::failure& e)
	{
		std::cout << "\nException Occured: Failed writing to file: " << m_outputSetFilename << " Message: " << e.what();
	}
	std::cout << "\nFile Saved: " << m_outputSetFilename;
}

void FileHandler::readOutputSetFile(std::vector<std::string>& outputSetStr)
{
	std::ifstream fileReader(m_outputSetFilename, std::ios::in);
	fileReader.exceptions(std::ifstream::badbit);
	try
	{
		if (!fileReader.good())
			throw std::ifstream("Probably file doesn't exists or badbit Error");

		std::string line/*, finalLine*/;
		while (std::getline(fileReader, line, '\n'))
		{
			line.erase(remove(line.begin(), line.end(), ','), line.end());
			outputSetStr.push_back(line);
		}
		fileReader.close();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "\nException Occured: Failed reading file: " << m_outputSetFilename << " Message: " << e.what();
	}
}