#ifndef _TERRAIN_
#define _TERRAIN_
#pragma once

#include <SFML\Graphics.hpp>

enum TerrainType
{
	Dungeon = 0,
	Cave,
	Water,
	Forest,
	Sand,
	Ground
};

struct TerrainMap
{
	sf::String name;
	sf::Vector2i lvl;

	TerrainType type;

};


#endif // !_TERRAIN_



