#include <SFML\Graphics.hpp>
#include "Engine.h"
#include "MenuState.h"
#include "AssetsManager.h"
#include "Entity.h"
#include "PlayState.h"
#include "Terrain.h"
#include "GUI.h"
#include "GUIButton.h"

void main()
{
	AssetsManager::GetInstance();
	GUI gui(200,200);
	Button* button = new Button("the",0,0);
	gui.AddWidget("test",button);
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
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