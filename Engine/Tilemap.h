#ifndef _TILEMAP_
#define _TILEMAP_

#pragma once
#include <vector>
#include "SFML\Graphics.hpp"
#include "Terrain.h"
#include "CaveG.h"
#include <random>

class TileMap
{
	std::vector<std::vector<MapType>> map;
	sf::VertexArray vertex;

	sf::Texture texture;
	sf::Vector2i StairUp, StairDown;

	const int TileSize{ 32 };
public:
	int Width, Height;
	void GenerateCave();
	
	void GenerateDungeon();
	void Draw(sf::RenderWindow & window);
	sf::Vector2i& GetStairUp() 
	{
		return StairUp;
	}
	sf::Vector2i& GetStairDown()
	{
		return StairDown;
	}
	bool isPassable(int x,int y)
	{
		if (map[x][y] == MapType::Wall) return false;
		else return true;
	}
	MapType getBlock(int x,int y) 
	{
		return map[x][y];
	}
	TileMap();
	~TileMap();
};

#endif // !_MAP_

