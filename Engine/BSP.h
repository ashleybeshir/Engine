#ifndef _BSP_
#define _BSP_

#pragma once

#include <vector>
#include "BSPNode.h"
#include <SFML\Graphics.hpp>

class BSP
{
	
	const int min_size{6};
	const int max_size{20};
public:
	std::vector<BSPNode*> nodes;
	std::vector<sf::RectangleShape> rectangle;
	void start();
	bool split();
	BSP();
	~BSP();
};

#endif // !1