#ifndef _TILEMAP_
#define _TILEMAP_

#pragma once
#include <vector>
#include "SFML\Graphics.hpp"
#include "Terrain.h"

const int TileSize = 32;


class TileMap
{
	std::vector<std::vector<MapType>> map;
	sf::VertexArray vertex;

public:
	int Width, Height;
	TileMap();
	~TileMap();
};

#endif // !_MAP_

