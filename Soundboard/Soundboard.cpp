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
#include <list>
#include "GUI.h"
#include <windows.h>
#include "GUIContainer.h"
#include "Button.h"
#include "FontLoader.h"
#include "ScrollBar.h"
#include "efx.h"
#include "FileIO.h"
#include "ListMenu.h"
#include "Image.h"
#include <math.h>
#include "DropdownMenu.h"
WindowManager window;

double UPS = 60;
double FPS = 120;

double thisFrame = 0;
double nextFrame = 0;

Chunk chunk;
FBO fbo;
void render(double delta, double lerp)
{
	window.update();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.917, 0.917, 0.917, 1);
	glClearColor(0.8, 0.8, 0.8, 1);
	//GFX::drawImage(0, 0, WindowManager::width, WindowManager::height, 2);
	//GFX::fillRect(0, 0, 100, 100, 1, 1, 1, 1);
	//chunk.render();
}
std::shared_ptr<GUIContainer> container;
std::shared_ptr<ListMenu> trackList(new ListMenu());
std::shared_ptr<GUIContainer> dashboard;
int length = 0;

std::vector<std::string> filesToSave;

std::shared_ptr<GUIContainer> addTrack(std::shared_ptr<GUIContainer> c, std::string fileName)
{
	filesToSave.emplace_back(fileName);
	//WAVE wave(fileName.c_str());
	//Sound sound; 
	//sound.play(wave);
	
	std::string name = FileIO::getFileNameNoEXT(fileName);
	std::shared_ptr<GUIContainer> trackContainer(new GUIContainer(0, 0, WindowManager::width, 100));
	std::shared_ptr<Button> playButton(new Button(name));
	std::shared_ptr<Button> stopButton(new Button("Stop"));
	std::shared_ptr<Button> timeUp5(new Button("+5s"));
	std::shared_ptr<Button> timeDown5(new Button("-5s"));
	std::shared_ptr<WAVE> wave = Assets::getAudio(name);
	std::shared_ptr<Sound> sound(new Sound());
	sound->setGain(1000000);
	std::shared_ptr<ScrollBar> pitchBar(new ScrollBar());
	pitchBar->mode = HORIZONTAL;
	pitchBar->range = 2;
	pitchBar->slide = 63;
	pitchBar->setProgress(0.5);
	std::shared_ptr<ScrollBar> volumeBar(new ScrollBar());
	volumeBar->mode = HORIZONTAL;
	volumeBar->range = 2;
	volumeBar->backgroundColour = Vec4f(1, 0, 0, 1);
	pitchBar->updateEvent = [sound, pitchBar]()
	{
		sound->setPitch(pitchBar->slide * 0.01 * 3);
	};
	volumeBar->updateEvent = [sound, volumeBar]()
	{
		sound->setGain((pow(volumeBar->slide * 0.01, 2)) * 2);
	};
	playButton->clickEvent = [sound, wave, fileName]()
	{		
		sound->play(wave);
	};
	stopButton->clickEvent = [sound, wave, fileName]()
	{
		sound->stop();
	};
	timeUp5->clickEvent = [sound]()
	{
		ALfloat time = sound->getTime() + 5;
		sound->setTime(time);
	};
	timeDown5->clickEvent = [sound]()
	{
		ALfloat time = sound->getTime() - 5;
		if (time < 0)
			time = 0;
		sound->setTime(time);
	};
	trackContainer->add(playButton, 0, 0, 1, 1);
	trackContainer->add(stopButton, 1, 0, 1, 1);
	trackContainer->add(timeUp5, 2, 0, 1, 1);
	trackContainer->add(timeDown5, 3, 0, 1, 1);
	trackContainer->add(pitchBar, 4, 0, 2, 1);
	trackContainer->add(volumeBar, 6, 0, 2, 1);
	//std::cout << pitchBar->button->width << "\n";
	/*std::shared_ptr<ScrollBar> sb(new ScrollBar());
	sb->mode = HORIZONTAL;
	sb->range = 5;

	sb->updateEvent = [&sound, &sb]()
	{
		alListenerf(AL_GAIN, sb->slide);
		//sound.setPitch((sb->slide + 0.5) * 0.02);
	};
	//container->add(sb, 1, 0, 4, 1);
	*/
	trackList->add(trackContainer);
	length++;
	return trackContainer;
}
void saveAll()
{
	std::string data;
	
	for (auto i : filesToSave)
	{
		data = data + i + "\n";
	}
	Util::writeToFile("save.txt", data);
}
void loadAll()
{
	std::string data = Util::readTextFile("save.txt");
	std::vector<std::string> lines = Util::splitString(data, "\n");
	std::string header = lines.at(0);

	for (int i = 1; i < lines.size(); i++)
	{
		std::string line = lines.at(i);
		std::cout << "|" << line << "|\n";
		addTrack(container, line);
	}
}
void loop()
{
	container = std::shared_ptr<GUIContainer>(new GUIContainer(0, 0, WindowManager::width, WindowManager::height));
	dashboard = std::shared_ptr<GUIContainer>(new GUIContainer(0, 0, WindowManager::width * 0.1, WindowManager::height * 0.1));
	WAVE wave("C:\\Temp\\song.wav");
	Assets::addAudio("faces", wave);
	Sound sound;
	sound.setPitch(1.2);
	//sound.play(wave);
	sound.setPitch(1.00);
	alSourcef(sound.source, AL_REVERB_GAIN, 1000);
	alListenerf(AL_REVERB_GAIN, 1000);
	alSourcef(sound.source, AL_REVERB_DIFFUSION, 1000);
	alListenerf(AL_REVERB_DIFFUSION, 1000);
	alSourcef(sound.source, AL_REVERB_DENSITY, 1000);
	alListenerf(AL_REVERB_DENSITY, 1000);
	loadAll();
	float pitch = 1;
	float pos = 0;
	double updatesPerSecond = 1 / UPS;
	double lastTime = -1;
	double thisTime = 0;

	float volume = 1;
	GUI gui;// (WindowManager::width, WindowManager::height);
	container->resizeEvent = []()
	{
		//container->setBounds(0, 0, WindowManager::width, 300);
	};
	trackList->setBounds(0, 0, WindowManager::width, 300);
	trackList->mode = SCROLL;
	gui.add(container);
	std::shared_ptr<Button> b(new Button("d"));
	int length = 0;
	b->clickEvent = [&length]()
	{

		auto i = addTrack(container, "C:\\Temp\\song.wav");
		//if (i == 0)
		//	printf("HELP");
		std::shared_ptr<Button> bt(new Button("d"));
		bt->clickEvent = []()
		{
		};
		//pog->add<Button>(0, length, 1, 1);// addTrack(container, "C:\\Temp\\faces.wav", length), 0, 0, 1, 1);
		
		trackList->handleResize();
		container->handleResize();
		saveAll();
	};
	container->add(b, 0, 0, 1, 1);
	container->add(trackList, 0, 1, 1, 20);
	container->add(dashboard, 0, 21, 1, 5);

	std::shared_ptr<Image> img(new Image());
	std::shared_ptr<Button> addAudio(new Button("Add"));
	//img->texture = Assets::getTexture("pepega")->texture;
	dashboard->add(addAudio, 0, 0, 1, 1);
	dashboard->add(img, 1, 1, 1, 1);

	addAudio->clickEvent = []()
	{

		char filename[MAX_PATH];

		OPENFILENAME ofn;

		ZeroMemory(&filename, sizeof(filename));
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
		ofn.lpstrFilter = "WAVE Files\0*.wav\0";
		ofn.lpstrFile = filename;
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrTitle = "Select audio";
		//ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;
		ofn.nMaxFile = 10;

		if (GetOpenFileName(&ofn))
		{
			//printf("%s\n", filename);
			addTrack(container, std::string(filename));
		}
		else
		{
			printf("LOL");
		}
	};
	dashboard->handleResize();

	std::shared_ptr<ScrollBar> sb(new ScrollBar());
	sb->mode = HORIZONTAL;
	sb->range = 5;
	
	sb->updateEvent = [&sound, &sb]()
	{
		alListenerf(AL_GAIN, sb->slide);
		//sound.setPitch((sb->slide + 0.5) * 0.02);
	};
	//container->add(sb, 1, 0, 1, 1);
	std::shared_ptr<DropdownMenu> sbb(new DropdownMenu("swag"));
	//sbb->list = std::shared_ptr<ListMenu>(new ListMenu());
	std::shared_ptr<Button> sbu(new Button("sadsfe"));
	sbu->updateEvent = [sbu]()
	{
		std::cout << sbu->x << " | " << sbu->y << " " << sbu->width << " " << sbu->height << "\n";
	};
	/*sbb->list->add(sbu);
	sbb->list->add<Button>();
	sbb->list->add<Button>();
	sbb->list->add<Button>();*/
	//sbb->list->add<Button>();
	//sbb->handleResize();
	//container->add(sbb, 1, 0, 1, 1);
	
	gui.handleResize();

	//GFX::drawString("hello", -10, -10, 10, 1, 1, 0, 1);
	
	while (!window.closeRequested())
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Controller::update();
		sound.setGain(volume);
		/*thisTime = glfwGetTime();
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
		}*/
		
		gui.refresh();
		render(1, 1);
		if (Control::active(GLFW_KEY_0))
		{
			sound.setGain(volume + 0.01);
		}
		GFX::fillRect(100, 100, 10000, 10000, 1, 0, 0, 1);
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

	std::string glVersion = (char*)glGetString(GL_VERSION);
	std::string glVendor = (char*)glGetString(GL_VENDOR);
	std::string glRenderer = (char*)glGetString(GL_RENDERER);
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
	Controller::init();
	GFX::init();
	Resource::loadAllResources();
	FontLoader::loadFont("C:\\Auravyx\\x64\\Release\\Assets\\Boot\\font.fnt");
	fbo = FBO(WindowManager::width, WindowManager::height);
	fbo.create();
	//fbo.bind();

	loop();
	glfwTerminate();
	return 0;
}
