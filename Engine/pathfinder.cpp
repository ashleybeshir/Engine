#include "pathfinder.h"

std::string path::pathfinding(Location start, Location end, TileMap & map)
{
	int safety{ 0 };
	PriorityQueue<Location, double> frontier;
	std::unordered_map<Location, Location> came_from;
	std::unordered_map<Location, double> cost_so_far;
	frontier.put(start, 0);
	came_from[start] = start;
	cost_so_far[start] = 0;

	while (!frontier.empty())
	{
		safety++;
		if (safety > 25)
		{
			return "q";
		}
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
			if (map.isPassable(x + 1, y))
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
		for (auto& next : adjancent)
		{
			double new_cost = cost_so_far[current] + 1;
			if (!cost_so_far.count(next) || new_cost < cost_so_far[next])
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

void path::pathfindingC(Location start, Location end, std::vector<std::vector<int>>& map)
{
	
	PriorityQueue<Location, double> frontier;
	std::unordered_map<Location, Location> came_from;
	std::unordered_map<Location, double> cost_so_far;
	frontier.put(start, 0);
	came_from[start] = start;
	cost_so_far[start] = 0;

	while (!frontier.empty())
	{
		
		auto current = frontier.get();
		if (current == end) break;

		std::vector<Location> adjancent;
		int x{ std::get<0>(current) }, y{ std::get<1>(current) };
		//std::tie(x, y) = current;
		std::cout << x << " " << y << std::endl;
		if (x != 0)
		{
			if (map[x][y] != 1)
			{
				adjancent.push_back(Location(x - 1, y));
			}

		}
		if (x != 99)
		{
			if (map[x][y] != 1) adjancent.push_back(Location(x + 1, y));

		}
		if (y != 0)
		{

			if (map[x][y] != 1) adjancent.push_back(Location(x, y - 1));

		}
		if (y != 99)
		{
			if (map[x][y] != 1) adjancent.push_back(Location(x, y + 1));
		}
		for (auto& next : adjancent)
		{
			double new_cost = cost_so_far[current] + 1;
			if (!cost_so_far.count(next) || new_cost < cost_so_far[next])
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

	for (auto& c : _path)
	{
		map[c.x][c.x] = 2;
	}
	

}
