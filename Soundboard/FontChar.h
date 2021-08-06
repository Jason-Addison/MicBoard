#pragma once
class FontChar
{
public:
	int xAdvance;
	int xOffset;
	int yOffset;
	int vaoID;
	int width;
	int height;

	FontChar(int xAdvance, int xOffset, int yOffset, int width, int height, int vaoID);

	FontChar();
	~FontChar();
};

