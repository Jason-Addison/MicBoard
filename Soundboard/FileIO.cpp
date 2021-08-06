#include "stdafx.h"
#include "FileIO.h"
#include <filesystem>
#include <iostream>
#include "FileIO.h"
#include <Windows.h>
#include "StringUtil.h"
#include <sstream>
#include "Log.h"
namespace fs = std::filesystem;
#define FOLDER 0
#define FILE 1
FileIO::FileIO()
{
}


FileIO::~FileIO()
{
}

std::vector<std::string> FileIO::listDirectory(std::string directory, std::string fileType)
{
	std::vector<std::string> list;
	std::vector<std::string> files = listDirectory(directory);
	for (auto & i : files)
	{
		std::string fileEnding = ".";
		fileEnding += fileType;
		if (StringUtil::endsWith(i, fileEnding))
		{
			list.emplace_back(i);
		}
		if (FileIO::typeOfFile(i) == FOLDER)
		{
			std::vector<std::string> subfolder = listDirectory(i, fileType);
			list.insert(list.begin(), subfolder.begin(), subfolder.end());
		}
	}

	return list;
}

std::vector<std::string> FileIO::listDirectory(std::string directory)
{
	std::vector<std::string> items;
	for (auto& p : std::filesystem::directory_iterator(directory))
	{
		std::ostringstream oss;
		oss << absolute(p.path()).string();
		items.emplace_back(oss.str());
	}
	return items;
}

int FileIO::typeOfFile(std::string path)
{
	struct stat s;
	if (stat(path.c_str(), &s) == 0)
	{
		if (s.st_mode & S_IFDIR)
		{
			return FOLDER;
		}
		else if (s.st_mode & S_IFREG)
		{
			return FILE;
		}
		else
		{
			return 3;
		}
	}
	else
	{
		return -1;
	}
}

std::string FileIO::getFileName(std::string file)
{
	char sep = '\\';

	int os = 0;
	if (os)
	{
		sep = '\\';
	}

	unsigned long long k = file.rfind(sep, file.length());
	if (k != std::string::npos)
	{
		file = file.substr(k + 1, file.length() - k);
	}
	return file;
}

std::string FileIO::getFileNameNoEXT(std::string file)
{
	std::string s = getFileName(file);
	s = s.substr(0, s.length() - 4);
	return s;
}

std::string FileIO::readTextFile(std::string location)
{
	std::ifstream inStream(location, std::ifstream::in);
	std::stringstream stream;
	stream << inStream.rdbuf();

	return stream.str();
}

void FileIO::writeToFile(std::string dir, std::string data)
{
	std::ofstream file;
	file.open(dir);
	file << data;
	file.close();
}