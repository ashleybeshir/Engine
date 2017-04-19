#ifndef _TILEMAP_
#define _TILEMAP_

#pragma once
#include <vector>
#include "SFML\Graphics.hpp"
#include "Terrain.h"
#include "CaveG.h"
#include <random>
#include "bspTree.h"
 #include "AssetsManager.h"

class TileMap
{
	std::vector<std::vector<MapType>> map;
	sf::VertexArray vertex;

	sf::Texture* texture;
	sf::Vector2i StairUp, StairDown;

	const int TileSize{ 32 };
	int c1, c2, c3;
	
public:
	int Width, Height;
	void GenerateCave();
	
	void GenerateDungeon();
	void Draw(sf::RenderWindow & window);
	void refreshGraphics(GenerationType type);
	inline sf::Vector2i& GetStairUp() 
	{
		return StairUp;
	}
	inline sf::Vector2i& GetStairDown()
	{
		return StairDown;
	}
	inline bool isPassable(int x,int y)
	{
		if (x < 0 || y < 0 || x > 99 || y > 99) return false;
		
		if (map[x][y] == MapType::Wall) return false;
		else if (map[x][y] == MapType::Empty) return false;
		else return true;
	}
	inline MapType getBlock(int x,int y) 
	{
		return map[x][y];
	}
	inline void SetBlock(int x,int y,MapType type)
	{
		map[x][y] = type;
		
	}
	TileMap();
	~TileMap();
};

#endif // !_MAP_

