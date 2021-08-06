
#include "stdafx.h"
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "WindowManager.h"
#include <string>
#include <iostream>
#include "al.h"
#include "SoundManager.h"
#include "Texture.h"
#include "Log.h"
#include "WAVE.h"
#include "Sound.h"
#include "Control.h"
#include "Resource.h"
#include "GFX.h"
#include "Assets.h"
#include "Shaders.h"
#include <chrono>
#include "FBO.h"
#include "Chunk.h"
WindowManager window;

double UPS = 60;
double FPS = 120;

double thisFrame = 0;
double nextFrame = 0;

void update(double delta, double lerp)
{
	if (thisFrame > 1 || nextFrame > 1)
	{
		thisFrame = 0;
		nextFrame = 0;
	}
	thisFrame = nextFrame;
	nextFrame = thisFrame + 1.0 / UPS;
	if (thisFrame > 1 || nextFrame > 1)
	{
		thisFrame = 0;
		nextFrame = 0;
		std::cout << "lol";
	}
		//std::cout << thisFrame << '\n';
}
Chunk chunk;
FBO fbo;
void render(double delta, double lerp)
{
	window.update();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(thisFrame * (1 - lerp) + nextFrame * lerp, 0, 0, 1);
	//GFX::drawImage(0, 0, WindowManager::width, WindowManager::height, GFX::tileMap);
	chunk.render();
}

void loop()
{
	WAVE wave("D:\\ler.wav");
	Sound sound;
	sound.setPitch(1.2);
	sound.play(wave);
	float pitch = 1;
	float pos = 0;
	double updatesPerSecond = 1 / UPS;
	double lastTime = -1;
	double thisTime = 0;;
	while (true)
	{
		thisTime = glfwGetTime();
		double delta = thisTime - lastTime;
		double lerp = delta * UPS;
		if (delta >= updatesPerSecond)
		{
			lastTime = thisTime;
			update(delta, lerp);
			if (Control::active(GLFW_KEY_1))
			{
				pos -= 0.01;
				sound.setVelocity(-10, 0, 0);
			}
			if (Control::active(GLFW_KEY_2))
			{
				pos += 0.01;
				sound.setVelocity(10, 0, 0);
			}
			if (Control::active(GLFW_KEY_EQUAL))
			{
				pitch += 0.01;
			}
			if (Control::active(GLFW_KEY_MINUS))
			{
				pitch -= 0.01;
			}
			sound.setPosition(pos, 0, -1);
			sound.setPitch(pitch);
		}
		render(delta, lerp);
	}	
}

void createWindow()
{
	window.create();
}

void glfwErrorCallback(int error, const char* description)
{
	std::string strWithErrCode;
	strWithErrCode.append("[");
	strWithErrCode.append(std::to_string(error));
	strWithErrCode.append("] ");
	strWithErrCode.append(description);
	std::cout << "[GLFW Error] " << strWithErrCode << "\n";
}

void printInfo()
{
	std::string alVersion = alGetString(AL_VERSION);
	std::string alVendor = alGetString(AL_VENDOR);
	std::string alRenderer = alGetString(AL_RENDERER);

	std::string glVersion = (char*) glGetString(GL_VERSION);
	std::string glVendor = (char*) glGetString(GL_VENDOR);
	std::string glRenderer = (char*) glGetString(GL_RENDERER);
	Log::out("[OpenGL]", "Version: " + glVersion + ", Vendor: " + glVendor + ", GPU: " + glRenderer, LBLUE);
	Log::out("[OpenAL]", "Version: " + alVersion + ", Vendor: " + alVendor + ", Renderer: " + alRenderer, GREEN);
}

int main()
{
	Log::out("Flet", "Loading...    UPS : " + std::to_string(UPS) + "  FPS : " + std::to_string(FPS), BLUE);
	glfwInit();
	if (!glfwInit())
	{
		printf("Oh no.\n");
	}
	glfwSetErrorCallback(glfwErrorCallback);
	createWindow();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		printf("%s", glewGetErrorString(err));
		system("PAUSE");
	}
	SoundManager m;
	m.start();
	alDopplerFactor(10);
	printInfo();

	Shaders shaders;
	shaders.init(Resource::loadShaders());

	GFX::init();
	Resource::loadAllResources();
	fbo = FBO(WindowManager::width, WindowManager::height);
	fbo.create();

	loop();
	glfwTerminate();
    return 0;
}
