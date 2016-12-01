#include "PlayState.h"
#include <iostream>


PlayState::PlayState()
{
}

PlayState::PlayState(bool type)
{
	Dungeon_Cave = type;
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
	
	bsp.start();
	std::cout << bsp.nodes.size() << std::endl;
	
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
	/*for (size_t i = 0; i < Entities.size(); i++)
	{
		Entities[i]->Update();
	}*/
}

void PlayState::Input(Engine * engine)
{
	sf::Event event;
	while (engine->window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			engine->window.close();
			break;
		default:
			break;
		}
	}
}

void PlayState::Draw(Engine * engine)
{
	/*for (size_t i = 0; i < Entities.size(); i++)
	{
		Entities[i]->Draw(engine->window);
	}*/
	for (size_t i = 0; i < bsp.rectangle.size(); i++)
	{
		engine->window.draw(bsp.rectangle[i]);
	}
}
