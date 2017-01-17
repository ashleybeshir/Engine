#include "CaveG.h"



void CaveG::addStairs(sf::Vector2i& Up, sf::Vector2i& Dow)
{
	bool down{ true }, up{ true };
	while (true) 
	{
		
		int x{ std::rand() % 99 + 1 };
		int y{ std::rand() % 99 + 1 };
		if (map[x][y] != 1) 
		{
			if (map[x][y] != 2 && down != false) 
			{
				std::cout << "down";
				map[x][y] = 3;
				Dow.x = x;
				Dow.y = y;
				down = false;
			}
			if (map[x][y] != 3 && up != false) 
			{
				std::cout << "up";
				map[x][y] = 2;
				up = false;
				Up.x = x;
				Up.y = y;
			}
			
		}
		if (up != true && down != true) 
		{
			return;
		}
	}
}

void CaveG::makeCavern()
{
	for (size_t y = 0; y <= height - 1; y++)
	{
		for (size_t x = 0; x <= width - 1; x++)
		{
			map[x][y] = PlaceWall(x, y);
		}

	}
}

int CaveG::PlaceWall(int x, int y)
{
	int numofWalls = GetAdjWall(x, y, 1, 1);
	if (map[x][y] == 1)
	{
		if (numofWalls >= 4)
		{
			return 1;
		}
		if (numofWalls <2)
		{
			return 0;
		}

	}
	else
	{
		if (numofWalls >= 5)
		{
			return 1;
		}
	}
	return 0;
}

int CaveG::GetAdjWall(int x, int y, int _x, int _y)
{

	int startX = x - _x;
	int startY = y - _y;
	int endX = x + _x;
	int endY = y + _y;

	int iX = startX;
	int iY = startY;

	int wallCounter = 0;

	for (iY = startY; iY <= endY; iY++) {
		for (iX = startX; iX <= endX; iX++)
		{
			if (!(iX == x && iY == y))
			{
				if (isWall(iX, iY))
				{
					wallCounter += 1;
				}
			}
		}
	}
	return wallCounter;
}

bool CaveG::isWall(int x, int y)
{
	if (isOutOfBounds(x, y))
	{
		return true;
	}

	if (map[x][y] == 1)
	{
		return true;
	}

	if (map[x][y] == 0)
	{
		return false;
	}
	return false;
}

bool CaveG::isOutOfBounds(int x, int y)
{
	if (x<0 || y<0)
	{
		return true;
	}
	else if (x>width - 1 || y>height - 1)
	{
		return true;
	}
	return false;
}



void CaveG::fillMap()
{
	map.resize(height);
	for (size_t i = 0; i < map.size(); i++)
	{
		map[i].resize(width);
	}
	int middle{ 0 };

	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			if (x == 0)
			{
				map[x][y] = 1;
			}
			else if (y == 0)
			{
				map[x][y] = 1;
			}
			else if (x == width - 1)
			{
				map[x][y] = 1;
			}
			else if (y == height - 1)
			{
				map[x][y] = 1;
			}
			else
			{
				middle = (height / 2);

				if (y == middle)
				{
					map[x][y] = 0;
				}
				else
				{
					map[x][y] = randomPercentage(WallPercentage);
				}
			}
		}

	}
}

bool CaveG::outOfBounds(int x, int y)
{
	return false;
}

int CaveG::randomPercentage(int percentage)
{
	if (percentage >= (std::rand() % 100 + 1))
	{
		return 1;
	}
	else return 0;
}

std::vector<std::vector<int>>& CaveG::GetMap()
{
	return map;
}

CaveG::CaveG()
{
	height = 100;
	width = 100;
	WallPercentage = 45;
	fillMap();
	makeCavern();
//	addStairs();
}

CaveG::CaveG(int seed)
{
	height = 100;
	width = 100;
	WallPercentage = 45;
	fillMap();
	makeCavern();
	//addStairs();
}

CaveG::CaveG(sf::Vector2i& Up, sf::Vector2i& Dow)
{
	height = 100;
	width = 100;
	WallPercentage = 45;
	fillMap();
 	makeCavern();
	addStairs(Up, Dow);

}


CaveG::~CaveG()
{
}
