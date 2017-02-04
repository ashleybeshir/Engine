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

void main()
{
	AssetsManager::GetInstance();
	GUI gui(800,800);
	Console* button = new Console(0,0.5f);
	gui.AddWidget("test",button);
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if(event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::L) {
					button->AddLog("hello world");
				}
			}
			
		}

		window.clear();
		gui.draw(&window);
		//window.draw(shape);
		window.display();
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