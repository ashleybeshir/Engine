#ifndef _TILEMAP_
#define _TILEMAP_

#pragma once
#include <vector>
#include "SFML\Graphics.hpp"
#include "Terrain.h"
#include <random>

class TileMap
{
	std::vector<std::vector<MapType>> map;
	sf::VertexArray vertex;

	sf::Texture texture;

	const int TileSize{ 32 };
public:
	int Width, Height;
	void GenerateCave();
	void GenerateDungeon();
	void Draw(sf::RenderWindow & window);
	bool isPassable(int x,int y)
	{
		if (map[x][y] == MapType::Wall) return false;
		else return true;	
	}
	TileMap();
	~TileMap();
};

#endif // !_MAP_

