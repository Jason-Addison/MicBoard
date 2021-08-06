#pragma once
#include <map>
#include "Texture.h"
#include "Model.h"
#include <memory>
#include "Font.h"
#include "WAVE.h"
//#include "GUI\Font.h"
//#include "Entity\Entity.h"
class Assets
{
public:
	Assets();
	~Assets();

	static std::map<std::string, std::shared_ptr<Model>> models;

	static std::map<std::string, std::shared_ptr<Texture>> textures;

	static std::map<std::string, std::shared_ptr<Font>> fonts;

	static std::map<std::string, std::shared_ptr<WAVE>> audio;

	//static std::map<std::string, const Entity> entities;

	static void addTexture(std::string name, Texture texture);

	static void addModel(std::string name, Model model);

	static void addFont(std::string name, Font font);

	static void addAudio(std::string name, WAVE a);

	//static void addEntity(std::string name, Entity font);

	static std::shared_ptr<Texture> getTexture(std::string name);

	static std::shared_ptr<Model> getModel(std::string name);

	static std::shared_ptr<Font> getFont(std::string name);

	static std::shared_ptr<WAVE> getAudio(std::string name);

	//static Entity getEntity(std::string name);
};

