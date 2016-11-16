#ifndef _COMPONENTS_
#define _COMPONENTS_
#pragma once

#include <SFML\Graphics.hpp>
#include "Entity.h"

struct PositionC : public Component
{
	sf::Vector2i Position;
};

struct GraphicC : public Component
{
	sf::VertexArray Graphics;
};

struct EnergyC : public Component
{
	int Energy;
};

#endif // !_COMPONENTS_


