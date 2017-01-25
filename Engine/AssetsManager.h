#ifndef _ASSETSMANAGER_
#define _ASSETSMANAGER_

#pragma once
#include <SFML\Graphics.hpp>
#include <map>
#include <iostream>

class AssetsManager
{
	std::map<sf::String, sf::Texture> data;
	static AssetsManager* p_instance;
public:
	static AssetsManager* GetInstance();
	void LoadTexture(const std::string& name, const std::string& filename);
	sf::Texture& GetRe(const std::string& texture);
	AssetsManager(AssetsManager const&) = delete;
	void operator=(AssetsManager const&) = delete;
	AssetsManager();
	~AssetsManager();
};

#endif // !_ASSETSMANAGER_



