#include "Tilemap.h"




void TileMap::GenerateCave()
{
	CaveG gen(StairUp,StairDown);

	texture = &AssetsManager::GetInstance()->GetRe("Cave");
	map.resize(100);
	for (size_t i = 0; i < map.size(); i++)
	{
		map[i].resize(100);
	}
	std::vector<std::vector<int>> temp = gen.GetMap();
	for (size_t x = 0; x < map.size(); x++)
	{
		for (size_t y = 0; y < map[x].size(); y++)
		{
			map[x][y] = (MapType)temp[x][y];
		}
	}
	vertex.clear();
	vertex.setPrimitiveType(sf::Quads);
	vertex.resize(100 * 100 * 4);

	for (size_t x = 0; x < 100; x++)
	{
		for (size_t y = 0; y < 100; y++)
		{
			MapType type = map[x][y];
			sf::Vertex* quad = &vertex[(x + y * 100) * 4];

			quad[0].position = sf::Vector2f(x * TileSize, y * TileSize);
			quad[1].position = sf::Vector2f((x + 1) * TileSize, y * TileSize);
			quad[2].position = sf::Vector2f((x + 1) * TileSize, (y + 1) * TileSize);
			quad[3].position = sf::Vector2f(x * TileSize, (y + 1) * TileSize);

			if (type == MapType::Floor)
			{
				quad[0].texCoords = sf::Vector2f(0, 0);
				quad[1].texCoords = sf::Vector2f((0 + 32), 0);
				quad[2].texCoords = sf::Vector2f((0 + 32), (0 + 32));
				quad[3].texCoords = sf::Vector2f(0, (0 + 32));
			}
			
			else if (type == MapType::StairD)
			{
				quad[0].texCoords = sf::Vector2f(96, 0);
				quad[1].texCoords = sf::Vector2f((96 + 32), 0);
				quad[2].texCoords = sf::Vector2f((96 + 32), (0 + 32));
				quad[3].texCoords = sf::Vector2f(96, (0 + 32));
			}
			else if (type == MapType::StairU)
			{
				quad[0].texCoords = sf::Vector2f(64, 0);
				quad[1].texCoords = sf::Vector2f((64 + 32), 0);
				quad[2].texCoords = sf::Vector2f((64 + 32), (0 + 32));
				quad[3].texCoords = sf::Vector2f(64, (0 + 32));
			}
			else if (type == MapType::Wall)
			{
				if(x != 0 && y != 0 && x != 99 && y != 99)
				{
					if (map[x-1][y] == MapType::Floor || map[x+1][y] == MapType::Floor || map[x][y-1] == MapType::Floor || map[x][y+1] == MapType::Floor)
					{
						
						quad[0].texCoords = sf::Vector2f(128, 0);
						quad[1].texCoords = sf::Vector2f((128 + 32), 0);
						quad[2].texCoords = sf::Vector2f((128 + 32), (0 + 32));
						quad[3].texCoords = sf::Vector2f(128, (0 + 32));
					}
					else
					{
						quad[0].texCoords = sf::Vector2f(32, 0);
						quad[1].texCoords = sf::Vector2f((32 + 32), 0);
						quad[2].texCoords = sf::Vector2f((32 + 32), (0 + 32));
						quad[3].texCoords = sf::Vector2f(32, (0 + 32));
					}
				}
				else 
				{
					quad[0].texCoords = sf::Vector2f(32, 0);
					quad[1].texCoords = sf::Vector2f((32 + 32), 0);
					quad[2].texCoords = sf::Vector2f((32 + 32), (0 + 32));
					quad[3].texCoords = sf::Vector2f(32, (0 + 32));
				}
			}

		}
	}
}

void TileMap::GenerateDungeon()
{
	texture = &AssetsManager::GetInstance()->GetRe("dungeon");
	map.resize(100);
	for (size_t i = 0; i < map.size(); i++)
	{
		map[i].resize(100);
	}

	
	bspG* tree = new bspG;
	tree->split();

	for (int y = 0; y < 100; y++)
	{
		for (int x = 0; x < 100; x++)
		{
			if (tree->map[x][y] == 1)
			{
				map[x][y] = MapType::Floor;
			}
			else if (tree->map[x][y] == 2) 
			{
				map[x][y] = MapType::Wall;
			}
			else if (tree->map[x][y] == 0)
			{
				map[x][y] = MapType::Empty;
			}else if (tree->map[x][y] == 3)
			{
				map[x][y] = MapType::StairD;
				StairDown.x = x;
				StairDown.y = y;
			}else if (tree->map[x][y] == 4)
			{
				map[x][y] = MapType::StairU;
				StairUp.x = x;
				StairUp.y = y;
			}
			
		}
	}

	vertex.clear();
	vertex.setPrimitiveType(sf::Quads);
	vertex.resize(100 * 100 * 4);

	for (size_t x = 0; x < 100; x++)
	{
		for (size_t y = 0; y < 100; y++)
		{
			MapType type = map[x][y];
			sf::Vertex* quad = &vertex[(x + y * 100) * 4];

			quad[0].position = sf::Vector2f(x * TileSize, y * TileSize);
			quad[1].position = sf::Vector2f((x + 1) * TileSize, y * TileSize);
			quad[2].position = sf::Vector2f((x + 1) * TileSize, (y + 1) * TileSize);
			quad[3].position = sf::Vector2f(x * TileSize, (y + 1) * TileSize);

			if (type == MapType::Floor)
			{
				quad[0].texCoords = sf::Vector2f(32, 0);
				quad[1].texCoords = sf::Vector2f((32 + 32), 0);
				quad[2].texCoords = sf::Vector2f((32 + 32),32);
				quad[3].texCoords = sf::Vector2f(32, 32);
			}

			else if (type == MapType::StairD)
			{
				quad[0].texCoords = sf::Vector2f(32, 32);
				quad[1].texCoords = sf::Vector2f((32 + 32), 32);
				quad[2].texCoords = sf::Vector2f((32 + 32), (32 + 32));
				quad[3].texCoords = sf::Vector2f(32, (32 + 32));
			}
			else if (type == MapType::StairU)
			{
				quad[0].texCoords = sf::Vector2f(0, 32);
				quad[1].texCoords = sf::Vector2f((0 + 32), 32);
				quad[2].texCoords = sf::Vector2f((0 + 32), (32 + 32));
				quad[3].texCoords = sf::Vector2f(0, (32 + 32));
			}
			else if (type == MapType::Wall)
			{
				quad[0].texCoords = sf::Vector2f(0, 0);
				quad[1].texCoords = sf::Vector2f((0 + 32), 0);
				quad[2].texCoords = sf::Vector2f((0 + 32), (0 + 32));
				quad[3].texCoords = sf::Vector2f(0, (0 + 32));
			}

		}
	}
	delete tree;
}

void TileMap::Draw(sf::RenderWindow & window)
{
	window.draw(vertex,texture);
}

TileMap::TileMap()
{
	
}

TileMap::~TileMap()
{
}
