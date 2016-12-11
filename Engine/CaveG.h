#ifndef _CAVE_
#define _CAVE_

#pragma once

#include <vector>
#include <random>
#include <iostream>

class CaveG
{
	std::vector<std::vector<int>> map;

	int height, width, WallPercentage;

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
	~CaveG();
};

#endif // !_CAVE_