#ifndef _PATH_
#define _PATH_
#pragma once

#include <SFML\System\Vector2.hpp>
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <vector>
#include <utility>
#include <queue>
#include <tuple>
#include <algorithm>
#include <functional>
#include <tuple>
#include "Tilemap.h"

/*struct node
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




std::string pathfinding(sf::Vector2i start, sf::Vector2i end,TileMap& map)
{
	std::vector<node> closed, open;
	open.push_back(node(start, manhattan_distance(start, end), 0));
	node current;
	current = open[0];
	
	do {	
		std::cout << current.pos.x << " " << current.pos.y << std::endl;
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
		if (current.pos.x != 0 ) 
		{
			if (map.isPassable(current.pos.x - 1, current.pos.y))
			{
				adjancent.push_back(node(sf::Vector2i(current.pos.x - 1, current.pos.y), manhattan_distance(sf::Vector2i(current.pos.x - 1, current.pos.y), end), current.G + 1));
			}
		}
		if (current.pos.x != 99)
		{
			if (map.isPassable(current.pos.x + 1, current.pos.y))
			{
				adjancent.push_back(node(sf::Vector2i(current.pos.x + 1, current.pos.y), manhattan_distance(sf::Vector2i(current.pos.x + 1, current.pos.y), end), current.G + 1));
			}
		}	
		if (current.pos.y != 0)
		{
			if (map.isPassable(current.pos.x, current.pos.y - 1))
			{
				adjancent.push_back(node(sf::Vector2i(current.pos.x, current.pos.y - 1), manhattan_distance(sf::Vector2i(current.pos.x, current.pos.y - 1), end), current.G + 1));
			}
		}
		if (current.pos.y != 99)
		{
			if (map.isPassable(current.pos.x, current.pos.y + 1))
			{
				adjancent.push_back(node(sf::Vector2i(current.pos.x, current.pos.y + 1), manhattan_distance(sf::Vector2i(current.pos.x, current.pos.y + 1), end), current.G + 1));
			}
		}
		
		for (int i = 0; i < adjancent.size(); i++)
		{
			bool _open{ false }, _closed{true};
			

			for (int x = 0; x < closed.size(); x++)
			{
				if (adjancent[i].pos == closed[x].pos)
				{
					_closed = false;
					break;
				}
			}
			if (_closed) {
				if (open.empty()) open.push_back(adjancent[i]);
				for (int y = 0; y < open.size(); y++)
				{
					if (open[y].pos == adjancent[i].pos)
					{
						_open = true;			
						break;
					}
					
				}
				if (!_open) {
					open.push_back(adjancent[i]);	
					current = adjancent[i];
				}
				else 
				{
					/*int _f = adjancent[i].G + adjancent[i].H;
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
}*/



template<typename T, typename priority_t>
struct PriorityQueue {
	typedef std::pair<priority_t, T> PQElement;
	std::priority_queue<PQElement, std::vector<PQElement>,
		std::greater<PQElement>> elements;

	inline bool empty() const { return elements.empty(); }

	inline void put(T item, priority_t priority) {
		elements.emplace(priority, item);
	
	}

	inline T get() {
		T best_item = elements.top().second;
		elements.pop();
		return best_item;
	}
};
typedef std::tuple<int, int> Location;
inline double heuristic(Location start, Location end)
{
	int x1, y1, x2, y2;
	std::tie(x1, y1) = start;
	std::tie(x2, y2) = end;
	return abs(x1 - x2) + abs(y1 - y2);
}
inline int heuristic(sf::Vector2i start, sf::Vector2i end)
{
	return std::abs(end.x - start.x) + std::abs(end.y - start.y);
}
namespace std {
	template <>
	struct hash<tuple<int, int> > {
		inline size_t operator()(const tuple<int, int>& location) const {
			int x, y;
			tie(x, y) = location;
			return x * 1812433253 + y;
		}
	};
}
std::string pathfinding(Location start,Location end ,TileMap& map) 
{
	
	PriorityQueue<Location, double> frontier;
	std::unordered_map<Location, Location> came_from;
	std::unordered_map<Location, double> cost_so_far;
	frontier.put(start,0);
	came_from[start] = start;
	cost_so_far[start] = 0;

	while (!frontier.empty())
	{
		auto current = frontier.get();
		if (current == end) break;

		std::vector<Location> adjancent;
		int x{ std::get<0>(current) }, y{ std::get<1>(current) };
		//std::tie(x, y) = current;
		if (x != 0)
		{
			if (map.isPassable(x - 1, y))
			{
				adjancent.push_back(Location(x - 1, y));
			}
		}
		if (x != 99)
		{
			if (map.isPassable(x + 1,y))
			{
				adjancent.push_back(Location(x + 1, y));
			}
		}
		if (y != 0)
		{
			if (map.isPassable(x, y - 1))
			{
				adjancent.push_back(Location(x, y - 1));
			}
		}
		if (y != 99)
		{
			if (map.isPassable(x, y + 1))
			{
				adjancent.push_back(Location(x, y + 1));
			}
		}
		for (auto& next:adjancent ) 
		{
			double new_cost = cost_so_far[current] + 1;
			if(!cost_so_far.count(next) || new_cost < cost_so_far[next])
			{
				cost_so_far[next] = new_cost;
				double priority = new_cost + heuristic(next, end);
				frontier.put(next, priority);
				came_from[next] = current;
			}
		}
		
	}
	
	std::vector<sf::Vector2i> _path;
	sf::Vector2i temp;
	temp.x = std::get<0>(end);
	temp.y = std::get<1>(end);
	_path.push_back(temp);
	Location _current = end;
	while (_current != start)
	{
		_current = came_from[_current];
		sf::Vector2i temp;
		temp.x = std::get<0>(_current);
		temp.y = std::get<1>(_current);
		_path.push_back(temp);
	}
	
	temp.x = std::get<0>(start);
	temp.y = std::get<1>(start);
	_path.push_back(temp);
	std::reverse(_path.begin(), _path.end());
	
	std::string path;
	for (int x = 0; x < _path.size(); x++)
	{
		if ((x + 1) < _path.size())
		{
			sf::Vector2i temp = _path[x + 1] - _path[x];
			if (temp.x == 1 && temp.y == 0)
			{
				path += 'R';
			}
			else if (temp.x == -1 && temp.y == 0)
			{
				path += 'L';
			}
			else if (temp.x == 0 && temp.y == -1)
			{
				path += 'U';
			}
			else if (temp.x == 0 && temp.y == 1)
			{
				path += 'D';
			}
		}
	}
	
	return path;
}

#endif