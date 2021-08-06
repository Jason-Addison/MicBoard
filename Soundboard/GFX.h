#pragma once
#include "Texture.h"
#include "Model.h"
class GFX
{
public:
	GFX();
	~GFX();

	static bool WIREFRAME;

	static Model quad;

	static GLuint tileMap;

	static void fillRect(float x, float y, float width, float height, float xScale, float yScale, float r, float g, float b, float a);

	static void fillRect(float x, float y, float xScale, float yScale, float r, float g, float b, float a);

	static void drawImage(float x, float y, float width, float height, int texture);

	static void drawImage(float x, float y, float width, float height, int texture, int xScale, int yScale);

	static void drawString(std::string string, float x, float y, float size, float r, float g, float b, float a);

	static void init();

	//static void enableScissor(int x, int y, int width, int height);

	//static void disableScissor();
	static void enableScissor(float x, float y, float width, float height);

	static void disableScissor();

};

