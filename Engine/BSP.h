#ifndef _BSP_
#define _BSP_

#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <random>

struct BSP
{

	const int min_leaf_size = 6;
	int x, y, width, height;

	BSP* LeftChild;
	BSP* RightChild;
	std::vector<BSP*> halls;

	sf::RectangleShape room;


	BSP(int x ,int y,int width ,int height) :x(x),y(y),width(width),height(height){}
	bool Split();
	void CreateRooms();
	BSP();
	~BSP();
};

#endif // !_BSP_