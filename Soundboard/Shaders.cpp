#include "stdafx.h"
#include "Shaders.h"


Shaders::Shaders()
{
}


Shaders::~Shaders()
{
}

ImageShader* Shaders::imageShader = new ImageShader();
RectShader* Shaders::rectShader = new RectShader();
FontShader* Shaders::fontShader = new FontShader();

void Shaders::init(std::map<std::string, std::string> shaders)
{
	imageShader->createShader(shaders);
	rectShader->createShader(shaders);
	fontShader->createShader(shaders);
}