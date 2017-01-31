#ifndef _ASSETSMANAGER_
#define _ASSETSMANAGER_

#pragma once
#include <SFML\Graphics.hpp>
#include <map>
#include <iostream>
#include "MapNode.h"

class AssetsManager
{
	std::map<sf::String, sf::Texture> data;
	std::map<int, MapNode*> dungeons;
	sf::Font* font;
	static AssetsManager* p_instance;
public:
	static AssetsManager* GetInstance();
	void LoadTexture(const std::string& name, const std::string& filename);
	sf::Texture& GetRe(const std::string& texture);
	void AddDungeon(MapNode* node);
	MapNode* GetDungeon(int seed);
	sf::Font* GetFont() 
	{
		return font;
	}
	AssetsManager(AssetsManager const&) = delete;
	void operator=(AssetsManager const&) = delete;
	AssetsManager();
	~AssetsManager();
};

#endif // !_ASSETSMANAGER_



