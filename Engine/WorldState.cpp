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
	texture = &AssetsManager::GetInstance()->GetRe("Map");
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
	
	Gplayer[0].texCoords = sf::Vector2f(0,0);
	Gplayer[1].texCoords = sf::Vector2f(32,0);
	Gplayer[2].texCoords = sf::Vector2f(32,32);
	Gplayer[3].texCoords = sf::Vector2f(0,32);

	Terrain.resize(50);
	for (size_t i = 0; i < Terrain.size(); i++) Terrain[i].resize(50);

	for (size_t x = 0; x < Terrain.size(); x++)
	{
		for (size_t y = 0; y < Terrain[x].size(); y++)
		{
			int temp = rand() % 100;
			if (temp <= 1)
			{
				Terrain[x][y] = TerrainType::dungeon;
			}else if(temp <= 3)
			{
				Terrain[x][y] = TerrainType::cave;
			}
			else if (temp <= 30) 
			{
				Terrain[x][y] = TerrainType::Forest;
			}
			else Terrain[x][y] = TerrainType::Ground;
			
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
			case Forest:
				quad[0].texCoords = sf::Vector2f(0, 192);
				quad[1].texCoords = sf::Vector2f(32, 192);
				quad[2].texCoords = sf::Vector2f(32, 224);
				quad[3].texCoords = sf::Vector2f(0, 224);
				break;
			case Cave:
				quad[0].texCoords = sf::Vector2f(192, 576);
				quad[1].texCoords = sf::Vector2f(224, 576);
				quad[2].texCoords = sf::Vector2f(224, 608);
				quad[3].texCoords = sf::Vector2f(192, 608);
				break;
			case Dungeon:
				quad[0].texCoords = sf::Vector2f(192, 416);
				quad[1].texCoords = sf::Vector2f(224, 416);
				quad[2].texCoords = sf::Vector2f(224, 448);
				quad[3].texCoords = sf::Vector2f(192, 448);
				break;
			default:
				quad[0].texCoords = sf::Vector2f(0, 32);
				quad[1].texCoords = sf::Vector2f(32, 32);
				quad[2].texCoords = sf::Vector2f(32, 64);
				quad[3].texCoords = sf::Vector2f(0, 64);
				break;
			}
		}
	}
	name = new Label(0,0.0,"",sf::Color::White);
	name->text.setCharacterSize(60);
	engine->gui->AddWidget("name",name);
	
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
	if (player.x >= 98)
	{
		player.x = 98;
	}
	else if (player.y >= 98)
	{
		player.y = 98;
	}
	if(Terrain[player.x][player.y] == TerrainType::cave)
	{
		name->SetText("Cave");
	}else if(Terrain[player.x][player.y] == TerrainType::dungeon)
	{
		name->SetText("Dungeon");
	}
	else if (Terrain[player.x][player.y] == TerrainType::Forest)
	{
		name->SetText("Forest");
	}
	else if (Terrain[player.x][player.y] == TerrainType::Sand)
	{
		name->SetText("Sand");
	}
	else if (Terrain[player.x][player.y] == TerrainType::Ground)
	{
		name->SetText("Ground");
	}
	else if (Terrain[player.x][player.y] == TerrainType::Water)
	{
		name->SetText("Water");
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
			else if (event.key.code == sf::Keyboard::Return)
			{
				TerrainType tile = Terrain[player.x][player.y];
				if (tile == TerrainType::cave)
				{
					int _seed = player.y * 100 + player.x + seed;
					MapNode* temp;
					if(AssetsManager::GetInstance()->GetDungeon(_seed) == nullptr)
					{
						temp = new MapNode(_seed,GenerationType::Cave,std::rand()%15+4);
						AssetsManager::GetInstance()->AddDungeon(temp);
					}
					else 
					{
						temp = AssetsManager::GetInstance()->GetDungeon(_seed);
					}
					engine->PushState(new PlayState(temp));
				}else if(tile == TerrainType::dungeon)
				{
					int _seed = player.y * 100 + player.x + seed;
					MapNode* temp;
					if (AssetsManager::GetInstance()->GetDungeon(_seed) == nullptr)
					{
						temp = new MapNode(_seed, GenerationType::Dungeon, std::rand() % 15 + 4);
						AssetsManager::GetInstance()->AddDungeon(temp);
					}
					else
					{
						temp = AssetsManager::GetInstance()->GetDungeon(_seed);
					}
					engine->PushState(new PlayState(temp));
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
	engine->window.draw(GTerrain,texture);
	engine->window.draw(Gplayer,tplayer);
}

void WorldState::ResetGraphics()
{
	engine->gui->Clear();
	name = new Label(0, 0.0, "", sf::Color::White);
	name->text.setCharacterSize(60);
	engine->gui->AddWidget("name", name);
}
