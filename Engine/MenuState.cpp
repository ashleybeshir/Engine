#include "MenuState.h"



MenuState::MenuState()
{
}


MenuState::~MenuState()
{
}

void MenuState::Start()
{
	
}

void MenuState::Delete()
{
}

void MenuState::Pause()
{
}

void MenuState::Resume()
{
}

void MenuState::Run(Engine * engine)
{
	
}

void MenuState::Input(Engine * engine)
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
			}
			break;

			// we don't process other types of events
		default:
			break;
		}
	}
}

void MenuState::Draw(Engine * engine)
{
	engine->window.clear();
	engine->window.display();
}
