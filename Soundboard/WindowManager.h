#pragma once
#include "GL\glew.h"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
class WindowManager
{
public:
	WindowManager();
	~WindowManager();

	static GLFWwindow* window;
	static int width;
	static int height;
	static bool resized;

	void create();

	void update();

	static void displayResizeCallback(GLFWwindow* _window, int _width, int _height);

	static int getWidth();

	static int getHeight();

	static bool wasResized();

	int closeRequested();
};

