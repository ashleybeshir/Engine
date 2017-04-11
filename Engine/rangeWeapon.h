#ifndef _RANGEWEAPON_
#define _RANGEWEAPON_
#pragma once
#include <SFML\Graphics.hpp>

struct RangeWeapon
{
	sf::Sprite graphics;
	sf::Vector2i direction;
	sf::Vector2i position;
	int damage;

	RangeWeapon(sf::Vector2i position,sf::Vector2i direction,int damage) :direction(direction),damage(damage),position(position)
	{
	}
};

#endif