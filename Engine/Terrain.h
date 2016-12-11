#ifndef _TERRAIN_
#define _TERRAIN_
#pragma once

#include <SFML\Graphics.hpp>

enum MapType
{
	Floor = 0,
	Wall	
};

enum GenerationType
{
	Cave = 0,
	Dungeon
};
enum TerrainType
{
	dungeon = 0,
	cave,
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



