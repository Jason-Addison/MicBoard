#include "stdafx.h"
#include "WindowManager.h"
#include <Windows.h>
//#define GLFW_EXPOSE_NATIVE_X11
//#define GLFW_EXPOSE_NATIVE_GLX
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <iomanip>
#include <string>
#include <SOIL.h>

WindowManager::WindowManager()
{
}


WindowManager::~WindowManager()
{
}

int WindowManager::width = 0;
int WindowManager::height = 0;
GLFWwindow* WindowManager::window;
HWND hwnd;

void WindowManager::create()
{
	std::string title = "Pepega™";//Polyvox | Ver " + std::string(1.3) + " | FPS : " + std::to_string(Display::frameRate);
	glfwDefaultWindowHints();
	//glfwWindowHint(GLFW_DECORATED, 0);
	width = 584;
	height = 864;
	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	
	glfwSetWindowSizeCallback(window, &displayResizeCallback);
	glfwSetWindowPos(window, 300, 50);
	GLFWimage icons[1];
	icons[0].pixels = SOIL_load_image("C:\\Temp\\pepega.png", &icons[0].width, &icons[0].height, 0, SOIL_LOAD_RGBA);
	glfwSetWindowIcon(window, 1, icons);

	//SOIL_free_image_data(icons[0].pixels);
	//Util::log(Colour::GREEN, "OpenGL", "Creating OpenGL context...");
	glfwMakeContextCurrent(window);
	//glfwRestoreWindow(window);
	glfwShowWindow(window);

	HWND windowHandle = GetActiveWindow();
	long Style = GetWindowLong(windowHandle, GWL_STYLE);
	Style &= ~WS_MAXIMIZEBOX; //this makes it still work when WS_MAXIMIZEBOX is actually already toggled off
	SetWindowLong(windowHandle, GWL_STYLE, Style);
	//hwnd = glfwGetWin32Window(window);
	//HWND chwnd = GetConsoleWindow();
	//HANDLE hIcon = (HICON)LoadImage(NULL, L"chicken.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
	//if (!hIcon)
	{
		//Util::log(Colour::RED, "Icon failed to load :\\");
	}
	//glfwSetCharModsCallback(Display::getWindow(), textCallback);
	

	//::SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
	//::SendMessage(hwnd, WM_SETICON, ICON_SMALL2, (LPARAM)hIcon);
	//::SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);

	
	
}

void WindowManager::update()
{
	glfwGetWindowSize(window, &width, &height);
	glViewport(0, 0, width, height);
	
	glfwSwapBuffers(window);
	glfwPollEvents();
	resized = false;
}
bool WindowManager::resized = true;
void WindowManager::displayResizeCallback(GLFWwindow* _window, int _width, int _height)
{
	resized = true;
}

int WindowManager::getWidth()
{
	return width;
}

int WindowManager::getHeight()
{
	return height;
}

bool WindowManager::wasResized()
{
	return resized;
}

int WindowManager::closeRequested()
{
	return glfwWindowShouldClose(window);
}


