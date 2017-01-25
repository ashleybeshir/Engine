#ifndef _PATH_
#define _PATH_
#pragma once

#include <SFML\System\Vector2.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "Terrain.h"

struct node
{
	sf::Vector2i pos;
	int H, G;
	node(sf::Vector2i _pos, int h, int g)
	{
		pos = _pos;
		H = h;
		G = g;
	}
	node() {}
};
inline int manhattan_distance(sf::Vector2i start, sf::Vector2i end)
{
	return std::abs(end.x - start.x) + std::abs(end.y - start.y);
}

std::string pathfinding(sf::Vector2i start, sf::Vector2i end,std::vector<std::vector<MapType>>& map)
{
	std::vector<node> closed, open;
	open.push_back(node(start, manhattan_distance(start, end), 0));
	node current;
	current = open[0];
	do {	
		for (int x = 0; x < open.size(); x++)
		{
			int f{current.G+current.H};
			int _f{ open[x].G + open[x].H };
			
			if (_f <= f)
			{
				current = open[x];
			}
			
		}
		closed.push_back(current);
		for (int x = 0; x < open.size(); x++)
		{
			if (open[x].pos == current.pos)
			{
				open.erase(open.begin() + x);
				
			}
		}
		if (current.pos == end)
		{
			break;
			
		}
		std::vector<node> adjancent;
		if (map[current.pos.x - 1][ current.pos.y] != MapType::Wall)
		{
			adjancent.push_back(node(sf::Vector2i(current.pos.x - 1, current.pos.y), manhattan_distance(sf::Vector2i(current.pos.x - 1, current.pos.y), end), current.G + 1));
		}
		if (map[current.pos.x + 1][current.pos.y] != MapType::Wall)
		{
			adjancent.push_back(node(sf::Vector2i(current.pos.x + 1, current.pos.y), manhattan_distance(sf::Vector2i(current.pos.x + 1, current.pos.y), end), current.G + 1));
		}
		if (map[current.pos.x][current.pos.y-1] != MapType::Wall)
		{
			adjancent.push_back(node(sf::Vector2i(current.pos.x, current.pos.y - 1), manhattan_distance(sf::Vector2i(current.pos.x, current.pos.y - 1), end), current.G + 1));
		}
		if (map[current.pos.x][current.pos.y+1] != MapType::Wall)
		{
			adjancent.push_back(node(sf::Vector2i(current.pos.x, current.pos.y + 1), manhattan_distance(sf::Vector2i(current.pos.x, current.pos.y + 1), end), current.G + 1));
		}
		
		for (int i = 0; i < 4; i++)
		{
			bool _open{ false }, _closed{true};
			
			for (int x = 0; x < closed.size(); x++)
			{
				if (adjancent[i].pos == closed[x].pos)
				{
					_closed = false;
				}
			}
			if (_closed) {
				if (open.empty()) open.push_back(adjancent[i]);
				for (int y = 0; y < open.size(); y++)
				{
					if (open[y].pos == adjancent[i].pos)
					{
						_open = true;					
					}
					
				}
				if (!_open) {
					open.push_back(adjancent[i]);	
				}
				else 
				{
					int _f = adjancent[i].G + adjancent[i].H;
					if (_f <= (current.G + current.H))
					{
						current = adjancent[i];
					}
				}
			}
		}

	} while (!open.empty());
	std::string path;
	for (int x = 0; x < closed.size(); x++)
	{
		if ((x + 1) < closed.size())
		{
			sf::Vector2i temp = closed[x + 1].pos - closed[x].pos;
			if (temp.x == 1 && temp.y == 0)
			{
				path += 'R';
			}
			else if (temp.x == -1 && temp.y == 0)
			{
				path += 'L';
			}
			else if (temp.x == 0 && temp.y == 1)
			{
				path += 'U';
			}
			else if (temp.x == 0 && temp.y == -1)
			{
				path += 'D';
			}
		}
	}
	return path;
}

#endif