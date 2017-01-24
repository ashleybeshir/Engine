#ifndef _COMPONENTS_
#define _COMPONENTS_
#pragma once

#include <SFML\Graphics.hpp>
#include <string>
#include "Entity.h"

struct PositionC : public Component
{
	PositionC(int x, int y) 
	{
		Position.x = x;
		Position.y = y;
	}
	sf::Vector2i Position;
};

struct GraphicC : public Component
{
	GraphicC()
	{
	}
	sf::Sprite sprite;
	
};
struct DirectionC : public Component
{
	sf::Vector2i direction;
};

struct EnergyC : public Component
{
	int Energy;
};
struct PathC : public Component
{
	std::string path;
};

#endif // !_COMPONENTS_


