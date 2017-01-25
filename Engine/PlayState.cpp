#include "PlayState.h"
#include <iostream>
#include "pathfinder.h"
#include "XmlLoader.h"

PlayState::PlayState()
{
	
}

PlayState::PlayState(GenerationType type,int seed)
{
	
	
	if (type == GenerationType::Cave)
	{
		
	}
	
	//Entities.push_back(std::unique_ptr<Entity>(player));
	
}

PlayState::PlayState(MapNode * node)
{
	DungeonNode = node;
	std::srand(node->GetSeed());
	view.setCenter(sf::Vector2f(350, 300));
	view.setSize(sf::Vector2f(800, 600));
	if (node->GetType() == GenerationType::Cave) 
	{
		map.GenerateCave();
	}
	if (node->GetEntityForLvl().size() != 0) 
	{
		Entities = node->GetEntityForLvl();
	}
	else 
	{
		//LoadXmlEntity();
	}
	player = new Entity;
	player->AddComponent<PositionC>(map.GetStairUp().x, map.GetStairUp().y);
	player->AddComponent<DirectionC>();

	sf::Sprite sprite;
	sprite.setTexture(AssetsManager::GetInstance()->GetRe("Entity"));
	sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	sprite.setPosition(map.GetStairUp().x * 32, map.GetStairUp().y * 32);
	player->AddComponent<GraphicC>();
	player->GetComponent<GraphicC>()->sprite = sprite;
}

PlayState::~PlayState()
{
}

void PlayState::AddEntity(Entity * entity)
{
	Entities.push_back(entity);
}

void PlayState::Start()
{
	
	
	
}

void PlayState::Delete()
{
}

void PlayState::Pause()
{
}

void PlayState::Resume()
{
}

void PlayState::Run(Engine * engine)
{
	if (input == true)
	{
		sf::Vector2i* temp = &player->GetComponent<DirectionC>()->direction;
		sf::Vector2i* pos = &player->GetComponent<PositionC>()->Position;
		pos->x = temp->x + pos->x;
		pos->y = temp->y + pos->y;
		sf::Sprite* g = &player->GetComponent<GraphicC>()->sprite;

		g->setPosition(pos->x * 32, pos->y * 32);
		for (auto& e : Entities)
		{
			sf::Vector2i* temp = &e->GetComponent<DirectionC>()->direction;
			sf::Vector2i* pos = &e->GetComponent<PositionC>()->Position;
			/*int difference{ manhattan_distance(player->GetComponent<PositionC>()->Position,*pos) };
			if (difference < 15 && difference != 0) 
			{
				std::string *path = &e->GetComponent<PathC>()->path;
				if (path->compare("") != 0) 
				{
					if (path->at(0),'R')
					{
						temp->x = 1;
						temp->y = 0;
						path->erase(path->begin());
					}else if(path->at(0) == 'L')
					{
						temp->x = -1;
						temp->y = 0;
						path->erase(path->begin());
					}
					else if (path->at(0) == 'U')
					{
						temp->x = 0;
						temp->y = 1;
						path->erase(path->begin());
					}
					else if (path->at(0) == 'D')
					{
						temp->x = 0;
						temp->y = -1;
						path->erase(path->begin());
					}
				}
				else 
				{
					*path = pathfinding(*pos, player->GetComponent<PositionC>()->Position,map);
					temp->x = 0;
					temp->y = 0;
				}
			}*/
			pos->x = temp->x + pos->x;
			pos->y = temp->y + pos->y;
			sf::Sprite* g = &e->GetComponent<GraphicC>()->sprite;

			g->setPosition(pos->x * 32, pos->y * 32);
		}
	}
}

void PlayState::Input(Engine * engine)
{
	input = false;
	player->GetComponent<DirectionC>()->direction.x = 0;
	player->GetComponent<DirectionC>()->direction.y = 0;

	sf::Event event;
	while (engine->window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			engine->window.close();
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape) {
				engine->window.close();
			}
			else if (event.key.code == sf::Keyboard::Up)
			{
				input = true;
				player->GetComponent<DirectionC>()->direction.x = 0;
				player->GetComponent<DirectionC>()->direction.y = -1;
			}else if (event.key.code == sf::Keyboard::Down)
			{
				input = true;
				player->GetComponent<DirectionC>()->direction.x = 0;
				player->GetComponent<DirectionC>()->direction.y = 1;
			}
			else if (event.key.code == sf::Keyboard::Left)
			{
				input = true;
				player->GetComponent<DirectionC>()->direction.x = -1;
				player->GetComponent<DirectionC>()->direction.y = 0;
			}
			else if (event.key.code == sf::Keyboard::Right)
			{
				input = true;
				player->GetComponent<DirectionC>()->direction.x = 1;
				player->GetComponent<DirectionC>()->direction.y = 0;
			}
			else if (event.key.code == sf::Keyboard::E)
			{
				input = true;
				int x{ player->GetComponent<PositionC>()->Position.x }, y{ player->GetComponent<PositionC>()->Position.y};
				if (map.getBlock(x,y) == MapType::StairD) 
				{
					DungeonNode->SetSeed(DungeonNode->GetSeed() + 1);
					std::srand(DungeonNode->GetSeed());
					map.GenerateCave();
					DungeonNode->SetLevel(DungeonNode->GetLevel() + 1);
					player->GetComponent<PositionC>()->Position = map.GetStairUp();
					Entities.clear();
					LoadXmlEntity(*this,DungeonNode->GetLevel(),map);
				}
				else if (map.getBlock(x, y) == MapType::StairU)
				{
					if (DungeonNode->GetLevel() == 0)
					{
						engine->PopState();
					}
					DungeonNode->SetSeed(DungeonNode->GetSeed() - 1);
					DungeonNode->SetLevel(DungeonNode->GetLevel() + 1);
					std::srand(DungeonNode->GetSeed());
					map.GenerateCave();
					player->GetComponent<PositionC>()->Position = map.GetStairDown();
				}
				
			}
			else if (event.key.code == sf::Keyboard::L)
			{		
				//std::cout << pathfinding(map.GetStairUp(),sf::Vector2i(map.GetStairUp().x + 5, map.GetStairUp().y+1)) << std::endl ;
			}
		default:
			break;

		}
	}
}

void PlayState::Draw(Engine * engine)
{
	sf::Vector2f pos = player->GetComponent<GraphicC>()->sprite.getPosition();
	
	view.setCenter(pos);
	engine->window.setView(view);
	map.Draw(engine->window);
	engine->window.draw(player->GetComponent<GraphicC>()->sprite);
	for (auto& e : Entities)
	{		
		engine->window.draw(e->GetComponent<GraphicC>()->sprite);
	}
}
