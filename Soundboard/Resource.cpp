#include "stdafx.h"
#include "Resource.h"
#include <iostream>
#include <string>
#include "FileIO.h"
#include "Log.h"
#include "SOIL.h"
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "Texture.h"
#include "Assets.h"
#include <math.h>
#include "FBO.h"
#include "GFX.h"
Resource::Resource()
{
}


Resource::~Resource()
{
}
static bool logShaders = true;
void Resource::loadAllResources()
{
	Log::out("Loader", "Start", YELLOW);
	Log::out("Loader", "Loading textures", YELLOW);
	loadAllTextures();
	Log::out("Loader", "Finish", YELLOW);

	//std::vector<std::string> files = FileIO::listDirectory("D:\\");
}

void Resource::loadAllTextures()
{
	std::vector<std::string> textures = FileIO::listDirectory("C:\\Auravyx\\x64\\Release\\Assets\\Boot", "png");
	std::vector<int> texList;
	std::string png = "png";

	for (auto &texture : textures)
	{
		unsigned int tex = SOIL_load_OGL_texture(texture.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
		int width, height;
		glBindTexture(GL_TEXTURE_2D, tex);

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		Texture texData(tex, width, height);
		std::string textureName = FileIO::getFileName(texture);
		texData.name = textureName.substr(0, textureName.length() - 4);
		Log::out("Loader", textureName, YELLOW);
		Assets::addTexture(textureName.substr(0, textureName.length() - 4), texData);
		texList.emplace_back(texData.texture);
	}
	int tileSize = 16;
	int length = std::ceil(sqrt(texList.size()));
	int size = length * tileSize;
	FBO tileMap(100, 100);
	tileMap.create();
	tileMap.bind();
	int x = 0, y = 0;
	for (int i = 0; i < texList.size(); i++)
	{
		GFX::drawImage(x * tileSize, size - tileSize - y * tileSize, tileSize, tileSize, texList.at(i), size, size);
		x++;
		if (x > length)
		{
			x = 0;
			y++;
		}
	}
	tileMap.unbind();
	GFX::tileMap = tileMap.texture;
}

std::map<std::string, std::string> Resource::loadShaders()
{
	int pass = 0;
	int fail = 0;
	if (logShaders)
	{
		Log::out("GLSL Loader", "--- Loading all shaders ---", MAGENTA);
	}

	std::string GAME_DIR = "C:\\Users\\jason\\source\\repos\\Soundboard\\Soundboard\\Shaders";
	std::string extVert = "vert";
	std::string extFrag = "frag";
	std::vector<std::string> vertexShaders = FileIO::listDirectory(GAME_DIR, extVert);
	//std::vector<std::string> vertexShaders = FileIO::listDirectory(GAME_DIR + "Source\\Shaders\\", extVert);
	std::map<std::string, std::string> shaders;
	for (auto & i : vertexShaders)
	{
		std::string path = i;
		std::string shaderName = FileIO::getFileName(i);
		Log::out("GLSL Loader", "[Vertex] Loaded : " + shaderName, MAGENTA);
		shaders.emplace(shaderName, FileIO::readTextFile(path));
		pass++;
	}

	std::vector<std::string> fragmentShaders = FileIO::listDirectory(GAME_DIR, extFrag);
	for (auto & i : fragmentShaders)
	{
		std::string path = i;
		std::string shaderName = FileIO::getFileName(i);
		Log::out("GLSL Loader", "[Fragment] Loaded : " + shaderName, MAGENTA);
		shaders.emplace(shaderName, FileIO::readTextFile(path));
		pass++;
	}
	//Util::logNNL(Colour::MAGENTA, "GLSL Loader", "");
	//Util::logNNL(Colour::WHITE, "--- ");
	//Util::logNNL(Colour::GREEN, std::to_string(pass) + "");
	//Util::logNNL(Colour::WHITE, " succeeded, ");
	//Util::logNNL(Colour::RED, std::to_string(fail) + "");
	//Util::logNNL(Colour::WHITE, " failed. ---\n");
	return shaders;
}