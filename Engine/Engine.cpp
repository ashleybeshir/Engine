#include "Engine.h"



Engine::Engine()
{
}


Engine::~Engine()
{
}

void Engine::Start()
{
	window.create(sf::VideoMode(800, 600), "My window");
}

void Engine::Delete()
{
}

void Engine::ChangeState(GameState * state)
{
	if (!states.empty())
	{
		states.back()->Delete();
		states.pop_back();
		
	}

	states.push_back(state);
	states.back()->Start();
}

void Engine::PushState(GameState * state)
{
	if (!states.empty()) {
		states.back()->Pause();
	}

	states.push_back(state);
	states.back()->Start();
}




void Engine::PopState()
{
	if (!states.empty()) {
		states.back()->Delete();
		states.pop_back();
	}

	// resume previous state
	if (!states.empty()) {
		states.back()->Resume();
	}
}

void Engine::Run()
{
	states.back()->Run(this);
}

void Engine::Input()
{
	states.back()->Input(this);
}

void Engine::Draw()
{
	states.back()->Draw(this);
}
