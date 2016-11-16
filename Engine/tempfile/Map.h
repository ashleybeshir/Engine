#ifndef _MAP_
#define _MAP_

#pragma once
#include <vector>
#include "SFML\Graphics.hpp"
#include "Terrain.h"

const int TileSize = 32;


class Map
{
	std::vector<std::vector<MapType>> map;
	sf::VertexArray vertex;
	
public:
	int Width, Height;
	Map();
	~Map();
};

#endif // !_MAP_

