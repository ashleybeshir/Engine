#include "MenuState.h"
#include "GUIButton.h"


MenuState::MenuState()
{
}


MenuState::~MenuState()
{
}

void MenuState::Start()
{
	Button* newbutton = new Button("New Game",0.45,0.2);
	Button* loadbutton = new Button("Load Game",0.45,0.3);
	Button* exitbutton = new Button("Exit Game",0.45,0.4);
	engine->gui->AddWidget("new",newbutton);
	engine->gui->AddWidget("load",loadbutton);
	engine->gui->AddWidget("exit",exitbutton);

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
		}
		if (event.type == sf::Event::KeyPressed) 
		{
			if (event.key.code == sf::Keyboard::Return) 
			{
				std::string temp = label->GetString();
				
				engine->ChangeState(new WorldState(stoi(temp)));
			}
		}else if (event.type == sf::Event::MouseButtonPressed)
		{
			sf::Vector2i position = sf::Mouse::getPosition();
			if (engine->gui->clicked(position.x, position.y))
			{
				std::string string = engine->gui->GetString();
				if (!newgame) {
					if (string.compare("New Game") == 0)
					{
						engine->gui->Clear();
						newgame = true;
						label = new TextInput(0.4,0.5);
						engine->gui->AddWidget("label",label);
						text = new Label(0.4,0.30,"write a number for the seed",sf::Color::White);
						engine->gui->AddWidget("text",text);
					}
					else if (string.compare("Exit Game") == 0)
					{
						engine->window.close();
					}
				}
			}
		}else if(event.type == sf::Event::MouseMoved)
		{
			sf::Vector2i _position = sf::Mouse::getPosition();
			engine->gui->check(_position.x, _position.y);
		}else if(event.type == sf::Event::TextEntered)
		{
			label->AddToString(static_cast<char>(event.text.unicode));
		}
	}
}

void MenuState::Draw(Engine * engine)
{
	
}
