#ifndef _CAVE_
#define _CAVE_

#pragma once

#include <vector>
#include <random>
#include <iostream>
#include<SFML\System\Vector2.hpp>

class CaveG
{
	std::vector<std::vector<int>> map;

	int height, width, WallPercentage;

	void addStairs(sf::Vector2i& Up, sf::Vector2i& Dow);
	void makeCavern();
	int PlaceWall(int x, int y);
	int GetAdjWall(int x, int y, int _x, int _y);
	bool isWall(int x, int y);
	bool isOutOfBounds(int x, int y);

	void fillMap();
	bool outOfBounds(int x, int y);
	int randomPercentage(int percentage);

public:
	std::vector<std::vector<int>>& GetMap();
	CaveG();
	CaveG(int seed);
	CaveG(sf::Vector2i& Up,sf::Vector2i& Dow);
	~CaveG();
};

#endif // !_CAVE_