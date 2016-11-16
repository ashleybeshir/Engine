#ifndef _ASSETSMANAGER_
#define _ASSETSMANAGER_

#pragma once
#include <SFML\Graphics.hpp>
#include <map>

class AssetsManager
{
	std::map<sf::String, sf::Texture> textures;
	static AssetsManager* p_instance;
public:
	static AssetsManager* GetInstance();

	AssetsManager(AssetsManager const&) = delete;
	void operator=(AssetsManager const&) = delete;
	AssetsManager();
	~AssetsManager();
};

#endif // !_ASSETSMANAGER_



