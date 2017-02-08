#include <SFML\Graphics.hpp>
#include "Engine.h"
#include "MenuState.h"
#include "AssetsManager.h"
#include "Entity.h"
#include "PlayState.h"
#include "Terrain.h"
#include "GUI.h"
#include "GUIButton.h"
#include "GUIConsole.h"
#include "GUIList.h"
#include "GUIInput.h"
#include <string>
void main()
{
	AssetsManager::GetInstance();
	GUI gui(800,800);
	TextInput* button = new TextInput(0.5f,0.5f);
	gui.AddWidget("test",button);
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < 128) button->AddToString(static_cast<char>(event.text.unicode));
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				
			}
			else if (event.type == sf::Event::MouseMoved) 
			{
				sf::Vector2i position = sf::Mouse::getPosition(window);
				gui.check(position.x,position.y);
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i position = sf::Mouse::getPosition(window);
				if (gui.clicked(position.x, position.y)) {
					std::string temp = gui.GetString().toAnsiString();
					std::cout << temp << std::endl;
				}
			}

			window.clear(sf::Color::Red);
			gui.draw(&window);
			//window.draw(shape);
			window.display();
		}
	}
	/*Engine engine;

	engine.Start();
	engine.PushState(new WorldState(50));

	while (engine.window.isOpen())
	{
		
		engine.Run();
		engine.Input();
		engine.Draw();
	}*/
}