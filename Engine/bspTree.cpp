#include "bspTree.h"
#include "pathfinder.h"

double r2()
{
	double r{ (double)rand() / (double)RAND_MAX };
	while (!(r >= 0.18 && r <= 0.85))
	{
		r = (double)rand() / (double)RAND_MAX;
	}
	return r;
}
double r()
{
	return (double)rand() / (double)RAND_MAX;
}

void Split(Room* current)
{
	double rand = r2();
	if (current->sizex > current->sizey)
	{
		int newsizex{ static_cast<int>(current->sizex * rand) };
		bool divide{ false };
		if (current->sizex >= max_size) divide = true;
		while (divide)
		{
			if (newsizex >= min_size && std::abs(current->sizex - newsizex) >= min_size )
			{
				divide = false;
				current->childx = new Room(current->x, current->y, newsizex - 2, current->sizey);
				current->childy = new Room(current->x + newsizex, current->y, std::abs(current->sizex - newsizex) - 2, current->sizey);
				current->childx->parent = current;
				current->childy->parent = current;
				Split(current->childx);
				Split(current->childy);
			}
			newsizex = current->sizex * r2();

		}
		
	}
	else
	{
		int newsizey{ static_cast<int>(current->sizey * rand) };
		bool divide{ false };
		if (current->sizey >= max_size) divide = true;
		while (divide)
		{
			if (newsizey >= min_size && std::abs(current->sizey - newsizey) >= min_size)
			{
				divide = false;
				current->childx = new Room(current->x, current->y, current->sizex, newsizey - 2);
				current->childy = new Room(current->x, current->y + newsizey, current->sizex, std::abs(current->sizey - newsizey) - 2);
				current->childx->parent = current;
				current->childy->parent = current;
				Split(current->childx);
				Split(current->childy);
			}
			newsizey = current->sizey * r2();

		}
		
		
	}
}
void InOrder(Room* room, std::vector<Room*>& temp)
{
	if (room != nullptr )
	{
		InOrder(room->childx, temp);
		if (room->childx == nullptr && room->childy == nullptr)
		{
			temp.push_back(room);
		}
		InOrder(room->childy, temp);
	}

}
bool randomdelete(/*std::vector<Room*>& room*/Room* room) 
{
	if (room != nullptr) 
	{
		if (room->childx == nullptr && room->childy == nullptr)
		{
			return true;
		}

		if(randomdelete(room->childx))
		{
			delete room->childx;
			room->childx = nullptr;
			return false;
		}
		
		if(randomdelete(room->childy))
		{
			delete room->childy;
			room->childy = nullptr;
			return false;
		}
		
		
	}
	
	
	/*for (int i=0;i < room.size();i++) 
	{
		if (r2() > 0.8) continue;
		delete room[i];
		room.erase(room.begin()+i);
	}*/
}
void generatemap(std::vector<Room*>& room, std::vector<std::vector<int>>& map)
{
	map.resize(100);
	for (int i=0;i < map.size();i++)
	{
		map[i].resize(100);
	}
	for (int x=0;x < map.size();x++) 
	{
		for (int i = 0; i < map.size(); i++)
		{
			map[x][i] = 0;
		}
	}
	for (auto& c : room)
	{
		for (int x = c->x; x <= c->sizex+c->x; x++)
		{
			for (int y = c->y; y <= c->sizey+c->y; y++)
			{
				map[x][y] = 1;
				
			}
		}
		
	}
}
void createCorridors(std::vector<Room*>& room,std::vector<std::vector<int>>& map)
{
	/*for (int i=0;i < room.size();i++) 
	{
		if (i + 1 < room.size()) 
		{
			int lengthx = room[i]->x + room[i]->sizex;
			int lengthy = room[i]->y + room[i]->sizey;

			if (lengthy > room[i + 1]->y)
			{
				if (room[i]->x - room[i + 1]->x < 0)
				{
					int y = lengthy -(lengthy - (room[i + 1]->y + room[i+1]->sizey));
					for (size_t x = 0; x <= std::abs(lengthx - room[i + 1]->x); x++)
					{
						map[x+lengthx][y] = 8;
					}
				}else
				{
					int y = lengthy - (lengthy - (room[i + 1]->y + room[i + 1]->sizey));
					for (size_t x = 0; x <= std::abs(lengthx - room[i + 1]->x); x++)
					{
						map[x + (room[i+1]->sizex+room[i+1]->x)][y] = 8;
					}
				}
			}
			
		}
	}*/
}
	

void bspG::split()
{
	root = new Room(0, 0, 100, 100);
	Split(root);
	randomdelete(root);
	InOrder(root, temp);
	generatemap(temp,map);
	//createCorridors(temp,map);
	for (int x=0;x < map.size();x++) 
	{
		for (int y=0;y < map.size();y++) 
		{
			std::cout << map[y][x];
		}
		std::cout << std::endl;
	}
}

bspG::bspG()
{
}


bspG::~bspG()
{
}
