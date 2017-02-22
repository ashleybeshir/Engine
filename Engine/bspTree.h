#ifndef _BSPTREE_
#define _BSPTREE_

#pragma once

#include <vector>
#include <random>
#include <math.h>
#include <SFML\Graphics.hpp>
#include <iostream>

const int max_size{ 25 };
const int min_size{ 12 };

struct Room
{
	Room* parent;
	Room* childx{ nullptr }, *childy{ nullptr };
	int x, y;
	int sizex, sizey;
	Room(int x, int y, int sizex, int sizey) :x(x), y(y), sizex(sizex), sizey(sizey)
	{
	}
	
};
class bspG
{
	Room* root;
	
	std::vector<std::vector<int>> map;
public:
	
	std::vector<Room*> temp;
	void split();
	bspG();
	~bspG();
};


#endif // !_BSP_

