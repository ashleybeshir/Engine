#ifndef _BSPTREE_
#define _BSPTREE_

#pragma once

#include <vector>
#include <random>
#include <math.h>
#include <SFML\Graphics.hpp>
#include <iostream>

const int max_size{ 20 };
const int min_size{ 10 };

struct Room
{
	Room* parent{nullptr};
	Room* childx{ nullptr }, *childy{ nullptr };
	int x, y;
	int sizex, sizey;
	int count{ 0 };
	Room(int x, int y, int sizex, int sizey) :x(x), y(y), sizex(sizex), sizey(sizey)
	{
	}
  ~Room()
  {
	  //delete this;
  }
	
};
class bspG
{
	Room* root;
	
public:
	std::vector<std::vector<int>> map;
	std::vector<Room*> cor;
	std::vector<Room*> temp;
	void split();
	bspG();
	~bspG();
};


#endif // !_BSP_

