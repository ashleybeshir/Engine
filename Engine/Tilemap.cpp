#include "Tilemap.h"


void TileMap::GenerateCave()
{
	CaveG gen;
	
	if (!texture.loadFromFile("ground.png"))
	{

	}
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
				quad[0].texCoords = sf::Vector2f(96, 32 );
				quad[1].texCoords = sf::Vector2f((96 + 32), 32 );
				quad[2].texCoords = sf::Vector2f((96 + 32) , (32 + 32) );
				quad[3].texCoords = sf::Vector2f(96, (32 + 32) );
			}
			else
			{
				quad[0].texCoords = sf::Vector2f(0 , 96);
				quad[1].texCoords = sf::Vector2f((0 + 32) , 96 );
				quad[2].texCoords = sf::Vector2f((0 + 32) , (96 + 32));
				quad[3].texCoords = sf::Vector2f(0 , (96 + 32));
			}
			
		}
	}
	
}

void TileMap::GenerateDungeon()
{
}

void TileMap::Draw(sf::RenderWindow & window)
{
	window.draw(vertex,&texture);
}

TileMap::TileMap()
{
	
}

TileMap::~TileMap()
{
}
