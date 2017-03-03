#include "bspTree.h"
#include "pathfinder.h"

double r2()
{
	double r{ (double)std::rand() / (double)RAND_MAX };
	while (!(r >= 0.18 && r <= 0.85))
	{
		r = (double)std::rand() / (double)RAND_MAX;
	}
	return r;
}
double r()
{
	return (double)std::rand() / (double)RAND_MAX;
}
void walls(std::vector<std::vector<int>>& map)
{
	for (int x=0;x < 100;x++) 
	{
		for(int y=0;y < 100;y++)
		{
			if (x != 0 && y != 0 && x != 99 && y != 99)
			{
				if (map[x][y] == 1)
				{
					if (map[x + 1][y] == 0)
					{
						map[x + 1][y] = 2;
					}
					if (map[x - 1][y] == 0)
					{
						map[x - 1][y] = 2;
					}
					if (map[x][y + 1] == 0)
					{
						map[x][y + 1] = 2;
					}
					if (map[x][y - 1] == 0)
					{
						map[x][y - 1] = 2;
					}
					if(map[x-1][y - 1] == 0)
					{
						map[x-1][y - 1] = 2;
					}
					if (map[x + 1][y + 1] == 0)
					{
						map[x + 1][y + 1] = 2;
					}
					if (map[x - 1][y + 1] == 0)
					{
						map[x - 1][y + 1] = 2;
					}
					if (map[x + 1][y - 1] == 0)
					{
						map[x + 1][y - 1] = 2;
					}
				}
			}
			else if (map[x][y] == 0) map[x][y] = 2;
		}
	}
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
			if (r() < 0.2) {
				temp.push_back(room);
			}
		}
		InOrder(room->childy, temp);
	}

}
void randomdelete(std::vector<Room*>& room) 
{
	/*for (int i=0;i < room.size();) 
	{
		if (r() < 0.7) 
		{
			delete room[i];
			room.erase(room.begin() + i);
		}else
		{
			i++;
		}
	}*/

	
	
}
void generatemap(std::vector<Room*>& room, std::vector<std::vector<int>>& map, std::vector<Room*>& cor)
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
	for (auto& c : cor)
	{
		for (int x = c->x; x <= c->sizex + c->x; x++)
		{
			for (int y = c->y; y <= c->sizey + c->y; y++)
			{
				map[x][y] = 1;

			}
		}

	}
}
void createCorridors(std::vector<Room*>& room, std::vector<Room*>& cor)
{
	for (int i=0;i < room.size();i++) 
	{
		if (i + 1 < room.size()) 
		{
			int lengthx = room[i]->x + room[i]->sizex;
			int lengthy = room[i]->y + room[i]->sizey;
			int _lengthx = room[i+1]->x + room[i+1]->sizex;
			int _lengthy = room[i+1]->y + room[i+1]->sizey;
			if (room[i]->y < room[i+1]->y) 
			{
				if (room[i+1]->x >= room[i]->x && room[i + 1]->x <= lengthx)
				{
					Room* ho = new Room(room[i+1]->x,lengthy,0,std::abs(room[i + 1]->y-lengthy));
					cor.push_back(ho);
				}else if(room[i]->x >= room[i+1]->x && room[i]->x <= _lengthx)
				{
					Room* ho = new Room(room[i]->x, lengthy, 0, std::abs(room[i + 1]->y - lengthy));
					cor.push_back(ho);
				}
			}
			if(room[i]->y > room[i + 1]->y)
			{
				if (room[i + 1]->x >= room[i]->x && room[i + 1]->x <= lengthx)
				{
					Room* ho = new Room(room[i + 1]->x, _lengthy, 0, std::abs(room[i + 1]->y - lengthy));
					cor.push_back(ho);
				}
				else if (room[i]->x >= room[i + 1]->x && room[i]->x <= _lengthx)
				{
					Room* ho = new Room(room[i]->x, _lengthy, 0, std::abs(room[i + 1]->y - lengthy));
					cor.push_back(ho);
				}
			}
			if (room[i]->x < room[i + 1]->x)
			{
			
				if (room[i]->y >= room[i + 1]->y && room[i]->y <= _lengthy )
				{
					Room* hol = new Room(lengthx,room[i]->y,std::abs(lengthx - room[i+1]->x),0);
					cor.push_back(hol);
				}else if(lengthy >= room[i + 1]->y && lengthy <= _lengthy)
				{
					Room* hol = new Room(lengthx, lengthy, std::abs(lengthx - room[i + 1]->x), 0);
					cor.push_back(hol);
				}else if(room[i+1]->y >= room[i]->y && _lengthy <= lengthy )
				{
					Room* hol = new Room(lengthx, _lengthy, std::abs(lengthx - room[i + 1]->x), 0);
					cor.push_back(hol);
				}
			}else if(room[i]->x > room[i + 1]->x)
			{
				if (room[i]->y >= room[i + 1]->y && room[i]->y <= _lengthy)
				{
					Room* hol = new Room(_lengthx, room[i]->y, std::abs(lengthx - room[i + 1]->x), 0);
					cor.push_back(hol);
				}
				else if (lengthy >= room[i + 1]->y && lengthy <= _lengthy)
				{
					Room* hol = new Room(_lengthx, lengthy, std::abs(lengthx - room[i + 1]->x), 0);
					cor.push_back(hol);
				}
				else if (room[i + 1]->y >= room[i]->y && _lengthy <= lengthy)
				{
					Room* hol = new Room(_lengthx, _lengthy, std::abs(lengthx - room[i + 1]->x), 0);
					cor.push_back(hol);
				}
			}
			if(room[i]->x < room[i+1]->x && lengthx < room[i+1]->x && room[i]->y < room[i+1]->y && lengthy < room[i + 1]->y)
			{
				Room* first = new Room(lengthx,lengthy,0,std::abs(room[i+1]->y - lengthy));
				Room* second = new Room(lengthx,lengthy+(std::abs(room[i + 1]->y - lengthy)),std::abs(lengthx-room[i+1]->x),0);
				cor.push_back(first);
				cor.push_back(second);
			}else if(room[i]->x > room[i + 1]->x && lengthx > _lengthx && room[i]->y < room[i + 1]->y && lengthy < room[i + 1]->y)
			{
				Room* first = new Room(room[i]->x, lengthy, 0, std::abs(room[i + 1]->y - lengthy));
				Room* second = new Room(_lengthx, lengthy + (std::abs(room[i + 1]->y - lengthy)), std::abs(_lengthx - room[i]->x), 0);
				cor.push_back(first);
				cor.push_back(second);
			}
			if (room[i]->x < room[i + 1]->x && lengthx < room[i + 1]->x && room[i]->y > room[i + 1]->y && lengthy > _lengthy)
			{
				
				Room* first = new Room(lengthx, _lengthy, 0, std::abs(room[i]->y -_lengthy));
				Room* second = new Room(lengthx, _lengthy , std::abs(lengthx - room[i + 1]->x), 0);
				cor.push_back(first);
				cor.push_back(second);
			}
			else if (room[i]->x > room[i + 1]->x && lengthx > _lengthx && room[i]->y > room[i + 1]->y && lengthy > _lengthy)
			{
				
				Room* first = new Room(room[i]->x, _lengthy, 0, std::abs(room[i]->y - _lengthy));
				Room* second = new Room(_lengthx, _lengthy , std::abs(_lengthx - room[i]->x), 0);
				cor.push_back(first);
				cor.push_back(second);
			}

		}
	}
}
	

void bspG::split()
{
	root = new Room(0, 0, 100, 100);
	Split(root); 
	InOrder(root, temp);
	randomdelete(temp);
	createCorridors(temp,cor);
	generatemap(temp, map,cor);
	walls(map);
	bool stair1{ true };
	bool stair2{ true };
	while (stair1 || stair2) 
	{
		int x, y;
		if (stair1) 
		{
			x = std::rand() % 99+1;
			y= std::rand() % 99 + 1;
			if (map[x][y] == 1 ) 
			{
				map[x][y] = 3;
				stair1 = false;
			}
		}
		if (stair2) 
		{
			x = std::rand() % 99 + 1;
			y = std::rand() % 99 + 1;
			if (map[x][y] == 1)
			{
				map[x][y] = 4;
				stair2 = false;
			}
		}
	}
	
}

bspG::bspG()
{
}

void delete_tree(Room* _root)
{
	if (_root != nullptr)
	{
		delete_tree(_root->childx);
		delete_tree(_root->childy);
		delete(_root);
		if (_root->childx != nullptr)
			_root->childy = nullptr;
		if (_root->childx != nullptr)
			_root->childy = nullptr;
		_root = nullptr;
	}
}
bspG::~bspG()
{
	delete_tree(root);
	
	for(int i=0;i < cor.size();i++)
	{
		delete cor[i];
	}
	map.clear();
	
}
