#pragma once
#include <vector>
#include <sstream>
#include <fstream>
class FileIO
{
public:
	FileIO();
	~FileIO();
	static std::vector<std::string> listDirectory(std::string directory);

	static std::vector<std::string> listDirectory(std::string directory, std::string fileType);

	static int typeOfFile(std::string path);

	static std::string getFileName(std::string file);

	static std::string getFileNameNoEXT(std::string file);

	static std::string readTextFile(std::string location);

	static void writeToFile(std::string dir, std::string data);
};

