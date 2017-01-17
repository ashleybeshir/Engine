#include "WorldState.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

WorldState::WorldState(int seed)
{
	this->seed = seed;
	
}

WorldState::WorldState()
{
	seed = std::time(0);
	std::srand(seed);
}


WorldState::~WorldState()
{
}

void WorldState::Start()
{
	std::cout << "world is generating" << std::endl;

	view.setCenter(sf::Vector2f(0, 0));
	view.setSize(sf::Vector2f(1920, 1080));

	player.x = 0;
	player.y = 0;
	Gplayer.setPrimitiveType(sf::Quads);
	Gplayer.resize(4);
	Gplayer[0].position = sf::Vector2f(player.x * 32, player.y * 32);
	Gplayer[1].position = sf::Vector2f((player.x+1) * 32, player.y * 32);
	Gplayer[2].position = sf::Vector2f((player.x+1) * 32, (player.y+1) * 32);
	Gplayer[3].position = sf::Vector2f(player.x * 32, (player.y+1) * 32);

	Gplayer[0].color = sf::Color::White;
	Gplayer[1].color = sf::Color::White;
	Gplayer[2].color = sf::Color::White;
	Gplayer[3].color = sf::Color::White;

	Terrain.resize(50);
	for (size_t i = 0; i < Terrain.size(); i++) Terrain[i].resize(50);

	for (size_t x = 0; x < Terrain.size(); x++)
	{
		for (size_t y = 0; y < Terrain[x].size(); y++)
		{
			Terrain[x][y] = (TerrainType)(0  + (rand() % (int)(5 - 0  + 1)));
		}
	}

	GTerrain.setPrimitiveType(sf::Quads);
	GTerrain.resize(50*50*4);
	for (size_t x = 0; x < Terrain.size(); x++)
	{
		for (size_t y = 0; y < Terrain[x].size(); y++)
		{
			sf::Vertex* quad = &GTerrain[(x + y * 50) * 4];

			quad[0].position = sf::Vector2f(x * 32, y * 32);
			quad[1].position = sf::Vector2f((x + 1) * 32, y * 32);
			quad[2].position = sf::Vector2f((x + 1) * 32, (y + 1) * 32);
			quad[3].position = sf::Vector2f(x * 32, (y + 1) * 32);

			TerrainType tileNumber = Terrain[x][y];
			switch (tileNumber)
			{
			case Ground:
				quad[0].color = sf::Color(51,25,0);
				quad[1].color = sf::Color(51, 25, 0);
				quad[2].color = sf::Color(51, 25, 0);
				quad[3].color = sf::Color(51, 25, 0);
				break;
			case Sand:
				quad[0].color = sf::Color(204,204, 0);
				quad[1].color = sf::Color(204,204, 0);
				quad[2].color = sf::Color(204,204, 0);
				quad[3].color = sf::Color(204,204, 0);
				break;
			case Forest:
				quad[0].color = sf::Color(0, 204, 0);
				quad[1].color = sf::Color(0, 204, 0);
				quad[2].color = sf::Color(0, 204, 0);
				quad[3].color = sf::Color(0, 204, 0);
				break;
			case Water:
				quad[0].color = sf::Color(255, 255, 0);
				quad[1].color = sf::Color(255, 255, 0);
				quad[2].color = sf::Color(255, 255, 0);
				quad[3].color = sf::Color(255, 255, 0);
				break;
			case Cave:
				quad[0].color = sf::Color(96, 96, 96);
				quad[1].color = sf::Color(96, 96, 96);
				quad[2].color = sf::Color(96, 96, 96);
				quad[3].color = sf::Color(96, 96, 96);
				break;
			case Dungeon:
				quad[0].color = sf::Color(204, 0, 0);
				quad[1].color = sf::Color(204, 0, 0);
				quad[2].color = sf::Color(204, 0, 0);
				quad[3].color = sf::Color(204, 0, 0);
				break;
			default:
				std::cout << tileNumber << std::endl;
				break;
			}
		}
	}
	
}

void WorldState::Delete()
{
}

void WorldState::Pause()
{
}

void WorldState::Resume()
{
}

void WorldState::Run(Engine * engine)
{
	if (player.x < 0)
	{
		player.x = 0;
	}
	else if (player.y < 0)
	{
		player.y = 0;
	}
}

void WorldState::Input(Engine * engine)
{
	sf::Event event;
	while (engine->window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			engine->window.close();
			break;

			// key pressed
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::A)
			{
				std::cout << "911 was a inside job" << std::endl;
			}else
			if (event.key.code == sf::Keyboard::Up)
			{
				player.y -= 1;
				Gplayer[0].position = sf::Vector2f(player.x * 32, player.y * 32);
				Gplayer[1].position = sf::Vector2f((player.x + 1) * 32, player.y * 32);
				Gplayer[2].position = sf::Vector2f((player.x + 1) * 32, (player.y + 1) * 32);
				Gplayer[3].position = sf::Vector2f(player.x * 32, (player.y + 1) * 32);
				view.setCenter(player.x*32,player.y*32);
			}
			else if (event.key.code == sf::Keyboard::Down)
			{
				player.y +=1;
				Gplayer[0].position = sf::Vector2f(player.x * 32, player.y * 32);
				Gplayer[1].position = sf::Vector2f((player.x + 1) * 32, player.y * 32);
				Gplayer[2].position = sf::Vector2f((player.x + 1) * 32, (player.y + 1) * 32);
				Gplayer[3].position = sf::Vector2f(player.x * 32, (player.y + 1) * 32);
				view.setCenter(player.x * 32, player.y * 32);
			}
			else if (event.key.code == sf::Keyboard::Left)
			{
				player.x -= 1;
				Gplayer[0].position = sf::Vector2f(player.x * 32, player.y * 32);
				Gplayer[1].position = sf::Vector2f((player.x + 1) * 32, player.y * 32);
				Gplayer[2].position = sf::Vector2f((player.x + 1) * 32, (player.y + 1) * 32);
				Gplayer[3].position = sf::Vector2f(player.x * 32, (player.y + 1) * 32);
				view.setCenter(player.x * 32, player.y * 32);
			}
			else if (event.key.code == sf::Keyboard::Right)
			{
				player.x += 1;
				Gplayer[0].position = sf::Vector2f(player.x * 32, player.y * 32);
				Gplayer[1].position = sf::Vector2f((player.x + 1) * 32, player.y * 32);
				Gplayer[2].position = sf::Vector2f((player.x + 1) * 32, (player.y + 1) * 32);
				Gplayer[3].position = sf::Vector2f(player.x * 32, (player.y + 1) * 32);
				view.setCenter(player.x * 32, player.y * 32);
			}
			else if (event.key.code == sf::Keyboard::F)
			{
				TerrainType tile = Terrain[player.x][player.y];
				if (tile == TerrainType::dungeon)
				{
					engine->PushState(new PlayState(GenerationType::Cave,50));
				}
			}
			
			break;


			
		case sf::Event::MouseWheelScrolled:
			if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) 
			{
				
				if (event.mouseWheelScroll.delta == 1)
				{
					view.zoom(0.9f);
				}
				else
				{
					view.zoom(1.1f);
				}
			}
		default:
			break;
		}
	}
}

void WorldState::Draw(Engine * engine)
{
	engine->window.setView(view);
	engine->window.draw(GTerrain);
	engine->window.draw(Gplayer);
}
