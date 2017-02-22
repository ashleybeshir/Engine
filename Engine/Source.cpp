#include <SFML\Graphics.hpp>
#include "Engine.h"
#include "MenuState.h"

#include "bspTree.h"
void main()
{
	/*std::srand(900);
	bspG tree;
	tree.split();
	sf::RenderWindow window(sf::VideoMode(120, 120), "SFML works!");
	std::vector<sf::RectangleShape> shapes;
	sf::RectangleShape temp;
	temp.setPosition(sf::Vector2f(0,0));
	temp.setFillColor(sf::Color::Blue);
	temp.setSize(sf::Vector2f(100,100));
	//shapes.push_back(temp);
	for (auto& c: tree.temp) 
	{
		sf::RectangleShape shape;
		shape.setPosition(sf::Vector2f(c->x,c->y));
		shape.setSize(sf::Vector2f(c->sizex,c->sizey));
		int r = std::rand() % 256;
		shape.setFillColor(sf::Color(r,r,r));
		shapes.push_back(shape);
	}
	
	
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(temp);
		for (auto& b : shapes) 
		{
			window.draw(b);
		}
		window.display();
	}
	*/
	
	AssetsManager::GetInstance();
	
	
	Engine engine;

	engine.Start();
	engine.PushState(new MenuState());

	while (engine.window.isOpen())
	{
		engine.Run();
		engine.Input();
		engine.Draw();
	}
}