#pragma once
#include <map>
#include "ImageShader.h"
#include "RectShader.h"
#include "FontShader.h"
class Shaders
{
public:

	static ImageShader* imageShader;
	static RectShader* rectShader;
	static FontShader* fontShader;
	Shaders();
	~Shaders();

	void init(std::map<std::string, std::string> shaders);
};

