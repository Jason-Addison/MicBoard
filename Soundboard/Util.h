#pragma once
#pragma comment(lib, "rpcrt4.lib")
#include <string>
#include <vector>
#include <iostream>
#include <string>
#include <iostream>
#include <io.h>
#include <Windows.h>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <sys/stat.h>
#include <shobjidl.h>
#include <atlstr.h>

#define FOLDER 0
#define FILE 1

class Util
{
public:

	static void logNNL(int colour, std::string text);

	static void logNNL(int colour, std::string who, std::string message);

	static void log(int colour, std::string text);

	static void log(std::string text);

	static void log(int out);

	static void log(float out);

	static void log(int colour, std::string who, std::string message);

	static int typeOfFile(std::string path);

	static std::vector<std::string> listDirectory(std::string dir);

	static std::string readTextFile(std::string location);

	static void writeToFile(std::string dir, std::string data);

	static int createFolder(std::string dir);

	static std::string removeFromString(std::string string, std::string remove, std::string replace);

	static bool endsWith(std::string& fullString, std::string& ending);

	static bool startsWith(std::string string, std::string startsWith);

	static std::vector<std::string> splitString(std::string string, std::string splitter);

	static std::string createUUID();

	static std::string getFolder(LPCWSTR title, LPCWSTR dir);

	static std::string getFile(COMDLG_FILTERSPEC pFilter, LPCWSTR title, LPCWSTR defaultExtension, LPCWSTR dir);

	static std::string getFile(COMDLG_FILTERSPEC pFilter, LPCWSTR title, LPCWSTR defaultExtension, LPCWSTR dir, int mode);

	static bool saveFile();

	static std::string replaceAll(std::string str, std::string a, std::string b);

	static std::string removeAll(std::string str, char a);

	static std::string getFileNameNoEXT(std::string path, std::string ext);

	static bool pointAABB(float px, float py, float x, float y, float width, float height);
};