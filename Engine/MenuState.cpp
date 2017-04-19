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
	
	Button* exitbutton = new Button("Exit Game",0.45,0.3);
	engine->gui->AddWidget("new",newbutton);
	
	engine->gui->AddWidget("exit",exitbutton);

	Label* movement = new Label(0,0,"Movement: Left/Right/Up/Down",sf::Color::White);
	Label* Drop = new Label(0,0.1,"Drop Item: D key",sf::Color::White);
	Label* get = new Label(0, 0.2, "Get Item: G key", sf::Color::White);
	Label* wear = new Label(0, 0.3, "Wear Item: W key", sf::Color::White);
	Label* drink = new Label(0, 0.4, "Drink Potion: Q key", sf::Color::White);
	engine->gui->AddWidget("move", movement);
	engine->gui->AddWidget("drop", Drop);
	engine->gui->AddWidget("get", get);
	engine->gui->AddWidget("wear", wear);
	engine->gui->AddWidget("drink", drink);
	engine->gui->AddWidget("range",new Label(0, 0.5, "Throw Stone: f key(Choose a direction after it)", sf::Color::White));
	engine->gui->AddWidget("spells", new Label(0, 0.6, "Spell list: s key(Click where to fire)", sf::Color::White));

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
				
				if(newgame)engine->ChangeState(new WorldState(stoi(temp)));
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
			if(newgame)label->AddToString(static_cast<char>(event.text.unicode));
		}
	}
}

void MenuState::Draw(Engine * engine)
{
	
}

void MenuState::ResetGraphics()
{
}
