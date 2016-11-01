#include "PlayState.h"



PlayState::PlayState()
{
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
	for (size_t i = 0; i < Entities.size(); i++)
	{
		Entities[i]->Update();
	}
}

void PlayState::Input(Engine * engine)
{
	sf::Event event;
	while (engine->window.pollEvent(event))
	{

	}
}

void PlayState::Draw(Engine * engine)
{
	for (size_t i = 0; i < Entities.size(); i++)
	{
		Entities[i]->Draw(engine->window);
	}
}
