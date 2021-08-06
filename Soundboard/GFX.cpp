#include "stdafx.h"
#include "GFX.h"
#include "Math.h"
#include "Shaders.h"
#include "WindowManager.h"
#include "FontChar.h"
#include "Font.h"
#include "Assets.h"

GFX::GFX()
{
}


GFX::~GFX()
{
}
Model GFX::quad = Model();

GLuint GFX::tileMap = 0;
void GFX::drawImage(float x, float y, float width, float height, int texture, int xScale, int yScale)
{
	glDisable(GL_DEPTH_TEST);
	Matrix4f transformation = Math::createTransformationMatrix(0, 0, 0, width / (float)xScale * 2, height / (float)yScale * 2, 1, 0, 0, 0);
	transformation.translate(-1 + (x / (float)xScale * 2), -1 + (y / (float)yScale * 2), 0);
	Shaders::imageShader->start();
	Shaders::imageShader->loadTransformation(transformation);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBindVertexArray(quad.getVAO());
	glEnableVertexArrayAttrib(quad.getVAO(), 0);

	glDrawArrays(GL_TRIANGLES, 0, quad.getCount());
	glEnable(GL_DEPTH_TEST);
}

void GFX::drawString(std::string string, float x, float y, float size, float r, float g, float b, float a)
{
	Font font = *Assets::getFont("font");
	size *= 1 / (font.largestValue / size) * 2;
	glDisable(GL_DEPTH_TEST);

	//x * 2 + totalX, (int)(y * 2f + fontCharacter.getYOffset() * yScale * 2.5f / font.getSize() - yScale / 4), xScale * 2.5f / font.getSize(), -yScale * 2.5f / font.getSize()
	Matrix4f transformation;

	Shaders::fontShader->start();
	Shaders::fontShader->loadThickness(0.53, 0.5 / (0.5 * size));
	Shaders::fontShader->loadColour(r, g, b, a);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, font.texture.texture);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	float totalX = 0;
	for (int i = 0; i < string.size(); i++)
	{
		FontChar fchar = font.characters.at(string.at(i));
		//
		float newX = -1 + ((x + totalX) / WindowManager::width * 2);
		float newY = 1 - ((y + (fchar.yOffset - 12) * size / font.size) / WindowManager::height * 2);
		float newWidth = (size / font.size) / WindowManager::width * 2;
		float newHeight = (size / font.size) / WindowManager::height * 2;

		transformation = Math::createTransformationMatrix(newX, newY, 0, newWidth, newHeight, 1, 0, 0, 0);
		Shaders::fontShader->loadTransformation(transformation);
		totalX += fchar.xAdvance * font.size * size * 0.00014; //////////////////////////////////////////////////////////

		glBindVertexArray(fchar.vaoID);
		glEnableVertexArrayAttrib(fchar.vaoID, 0);
		glEnableVertexArrayAttrib(fchar.vaoID, 1);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	glEnable(GL_DEPTH_TEST);
}

void GFX::fillRect(float x, float y, float width, float height, float xScale, float yScale, float r, float g, float b, float a)
{
	glDisable(GL_DEPTH_TEST);
	Matrix4f transformation = Math::createTransformationMatrix(0, 0, 0, width / (float)xScale * 2, height / (float)yScale * 2, 1, 0, 0, 0);
	transformation.translate(-1 + (x / (float)xScale * 2), -1 + (y / (float)yScale * 2), 0);
	Shaders::rectShader->start();
	Shaders::rectShader->loadTransformation(transformation);
	Shaders::rectShader->loadColour(r, g, b, a);

	glBindVertexArray(quad.getVAO());
	glEnableVertexArrayAttrib(quad.getVAO(), 0);

	glDrawArrays(GL_TRIANGLES, 0, quad.getCount());
	glEnable(GL_DEPTH_TEST);
}

void GFX::fillRect(float x, float y, float xScale, float yScale, float r, float g, float b, float a)
{
	fillRect(x, WindowManager::height - y, xScale, -yScale, WindowManager::width, WindowManager::height, r, g, b, a);
}

void GFX::drawImage(float x, float y, float width, float height, int texture)
{
	drawImage(x, WindowManager::height - y - height, width, height, texture, WindowManager::width, WindowManager::height);
}

void GFX::init()
{
	std::vector<float> quadVert = { 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1 };
	quad = Model::load2DModel(quadVert);
}

void GFX::enableScissor(float x, float y, float width, float height)
{
	glScissor(x, WindowManager::height - y - height, width, height);
	glEnable(GL_SCISSOR_TEST);
}

void GFX::disableScissor()
{
	glDisable(GL_SCISSOR_TEST);
}
