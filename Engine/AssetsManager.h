#ifndef _ASSETSMANAGER_
#define _ASSETSMANAGER_

#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <map>
#include <iostream>
#include "MapNode.h"

struct ColorSheet
{
	sf::Color Normal, InView, Clicked;
	ColorSheet() {}
	ColorSheet(sf::Color normal, sf::Color inView, sf::Color clicked)
	{
		Normal = normal;
		InView = inView;
		Clicked = clicked;
	}
};

class AssetsManager
{
	std::vector<Item*> inventory;
	std::map<sf::String, sf::Texture> data;
	std::map<sf::String, sf::SoundBuffer> sounds;
	sf::SoundBuffer  buffer;
	std::map<int, MapNode*> dungeons;
	std::map<int, ColorSheet> colorsheets;
	sf::Font font;
	static AssetsManager* p_instance;
public:
	static AssetsManager* GetInstance();
	int player_level{ 0 };
	void LoadTexture(const std::string& name, const std::string& filename);
	void LoadMusic(const std::string& name, const std::string& filename);
	sf::Texture& GetRe(const std::string& texture);
	sf::SoundBuffer& GetSound(const std::string& sound)
	{
		return sounds[sound];
	}
	void AddDungeon(MapNode* node);
	MapNode* GetDungeon(int seed);
	sf::Font& GetFont()
	{
		return font;
	}
	std::vector<Item*>& GetInventory()
	{
		return inventory;
	}
	void SetInventory(std::vector<Item*> inv)
	{
		inventory = inv;
	}
	ColorSheet& GetColorSheet(int type)
	{
		return colorsheets[type];
	}
	AssetsManager(AssetsManager const&) = delete;
	void operator=(AssetsManager const&) = delete;
	AssetsManager();
	~AssetsManager();
};

#endif // !_ASSETSMANAGER_