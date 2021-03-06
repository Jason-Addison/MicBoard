#pragma once
#include "GUI.h"
#include <functional>
#include "Util.h"
//#include "Colour.h"
#include "Vec4f.h"
#include "Controller.h"
class Button : public GUI
{
public:
	Button();
	Button(std::string text);
	~Button();

	float x, y;
	float width, height;
	Vec4f backgroundColour = Vec4f::rgbaColour(60, 60, 60, 60);
	Vec4f hoverColour = Vec4f::rgbaColour(220, 220, 220, 130);
	Vec4f selectColour = Vec4f::rgbaColour(220, 220, 220, 255);
	Vec4f toggleColour = Vec4f::rgbaColour(147, 147, 147, 255);
	
	std::function<void()> clickEvent = []() {};
	std::function<void()> downEvent = []() {};
	std::function<void()> hoverEvent = []() {};

	std::string text;
	Vec4f textColour = Vec4f(1, 1, 1, 1);
	bool isDown;
	bool isHover;
	bool isClicked;

	//std::function<void()> Button::isDown = []() { Util::log(Colour::WHITE, "Button", "No event found."); };
	//std::function<void()> Button::isHover = []() { Util::log(Colour::WHITE, "Button", "No event found."); };

	void update();

	void render();

	void setBounds(float x, float y, float width, float height);

	void setClickEvent(std::function<void()> func);

	void setDownEvent(std::function<void()> func);
};

