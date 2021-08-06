#pragma once
#include <map>
#include <string>
class Resource
{
public:
	Resource();
	~Resource();

	static void loadAllResources();

	static std::map<std::string, std::string> loadShaders();

private:

	static void loadAllTextures();
};

