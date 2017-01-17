#include "PlayState.h"
#include <iostream>



PlayState::PlayState()
{
	
}

PlayState::PlayState(GenerationType type,int seed)
{
	std::srand(50);
	view.setCenter(sf::Vector2f(350, 300));
	view.setSize(sf::Vector2f(800, 600));
	if (!CharTextures.loadFromFile("monster.png"))
	{

	}
	if (type == GenerationType::Cave)
	{
		map.GenerateCave();
	}
	Entity* player = new Entity;
	player->AddComponent<PositionC>(map.GetStairUp().x,map.GetStairUp().y);
	player->AddComponent<DirectionC>();

	sf::Sprite sprite;
	sprite.setTexture(CharTextures);
	sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	sprite.setPosition(0,0);
	player->AddComponent<GraphicC>();
	player->GetComponent<GraphicC>()->sprite = sprite;
	Entities.push_back(std::unique_ptr<Entity>(player));
	
}

PlayState::~PlayState()
{
}

void PlayState::AddEntity(Entity * entity)
{
	Entities.push_back(std::unique_ptr<Entity>(entity));
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
	for (auto& e : Entities)
	{
		sf::Vector2i temp = e->GetComponent<DirectionC>()->direction;
		sf::Vector2i* pos = &e->GetComponent<PositionC>()->Position;

		pos->x = temp.x + pos->x;
		pos->y = temp.y + pos->y;
		sf::Sprite* g = &e->GetComponent<GraphicC>()->sprite;

		g->setPosition(pos->x*32,pos->y*32);
	}
}

void PlayState::Input(Engine * engine)
{
	Entities[0]->GetComponent<DirectionC>()->direction.x = 0;
	Entities[0]->GetComponent<DirectionC>()->direction.y = 0;

	sf::Event event;
	while (engine->window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			engine->window.close();
			break;
		case sf::Event::KeyPressed:
			
			if (event.key.code == sf::Keyboard::Up)
			{
				Entities[0]->GetComponent<DirectionC>()->direction.x = 0;
				Entities[0]->GetComponent<DirectionC>()->direction.y = -1;
			}else if (event.key.code == sf::Keyboard::Down)
			{
				Entities[0]->GetComponent<DirectionC>()->direction.x = 0;
				Entities[0]->GetComponent<DirectionC>()->direction.y = 1;
			}
			else if (event.key.code == sf::Keyboard::Left)
			{
				Entities[0]->GetComponent<DirectionC>()->direction.x = -1;
				Entities[0]->GetComponent<DirectionC>()->direction.y = 0;
			}
			else if (event.key.code == sf::Keyboard::Right)
			{
				Entities[0]->GetComponent<DirectionC>()->direction.x = 1;
				Entities[0]->GetComponent<DirectionC>()->direction.y = 0;
			}
			else if (event.key.code == sf::Keyboard::E)
			{
				int x{ Entities[0]->GetComponent<PositionC>()->Position.x }, y{ Entities[0]->GetComponent<PositionC>()->Position.y};
				if (map.getBlock(x,y) == MapType::StairD) 
				{
					seed+= 1;
					std::srand(seed);
					map.GenerateCave();
					Clvl += 1;
					Entities[0]->GetComponent<PositionC>()->Position = map.GetStairUp();
				}
				else if (map.getBlock(x, y) == MapType::StairU)
				{
					if (Clvl == 0)
					{
						engine->PopState();
					}
					seed -= 1;
					Clvl -= 1;
					std::srand(seed);
					map.GenerateCave();
					Entities[0]->GetComponent<PositionC>()->Position = map.GetStairDown();
				}
				
			}
		default:
			break;

		}
	}
}

void PlayState::Draw(Engine * engine)
{
	sf::Vector2f pos = Entities[0]->GetComponent<GraphicC>()->sprite.getPosition();
	
	view.setCenter(pos);
	engine->window.setView(view);
	map.Draw(engine->window);
	for (auto& e : Entities)
	{		
		engine->window.draw(e->GetComponent<GraphicC>()->sprite);
	}
}
