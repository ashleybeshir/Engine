#include "EndState.h"



EndState::EndState()
{
}

EndState::EndState(const std::string string)
{
	death = string;
}


EndState::~EndState()
{
}

void EndState::Start()
{
	Label* deat = new Label(0.5,0.25,"You died by "+death,sf::Color::White);
	Button* but = new Button("Menu",0.5,0.30);
	Button* butt = new Button("Exit", 0.5, 0.35);
	engine->gui->AddWidget("death",deat);
	engine->gui->AddWidget("menu",but);
	engine->gui->AddWidget("exit",butt);
}

void EndState::Delete()
{
}

void EndState::Pause()
{
}

void EndState::Resume()
{
}

void EndState::Run(Engine * engine)
{
}

void EndState::Input(Engine * engine)
{
	sf::Event event;
	while (engine->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			engine->window.close();
		else if (event.type == sf::Event::MouseButtonPressed) 
		{
			sf::Vector2i position = sf::Mouse::getPosition();
			if (engine->gui->clicked(position.x, position.y))
			{
				std::string string = engine->gui->GetString();
				if (string.compare("Menu") == 0)
				{
					engine->ChangeState(new MenuState());
				}else if(string.compare("Exit") == 0)
				{
					engine->window.close();
				}
			}
		}else if(event.type == sf::Event::MouseMoved)
		{
			sf::Vector2i position = sf::Mouse::getPosition();
			engine->gui->check(position.x,position.y);
		}
	}

	
}

void EndState::Draw(Engine * engine)
{
}
