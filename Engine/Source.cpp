#include <SFML\Graphics.hpp>
#include "Engine.h"
#include "MenuState.h"

#include "bspTree.h"

void redo(sf::VertexArray& graph,bspG* tree)
{
	for (unsigned int i = 0; i < 100; ++i)
	{
		for (unsigned int j = 0; j < 100; ++j)
		{
			sf::Vertex* quad = &graph[(i + j * 100) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(i * 32, j * 32);
			quad[1].position = sf::Vector2f((i + 1) * 32, j * 32);
			quad[2].position = sf::Vector2f((i + 1) * 32, (j + 1) * 32);
			quad[3].position = sf::Vector2f(i * 32, (j + 1) * 32);
			if (tree->map[j][i] != 0)
			{
				quad[0].color = sf::Color::Blue;
				quad[1].color = sf::Color::Blue;
				quad[2].color = sf::Color::Blue;
				quad[3].color = sf::Color::Blue;
			}
			else
			{
				quad[0].color = sf::Color::Green;
				quad[1].color = sf::Color::Green;
				quad[2].color = sf::Color::Green;
				quad[3].color = sf::Color::Green;
			}
		}
	}
}

void main()
{
	//50
   /* int seed = 320;
	std::srand(seed);
	bspG* tree = new bspG;
	tree->split();
	
	
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
	sf::View view(sf::Vector2f(1500, 1500), sf::Vector2f(6200, 6200));
	
	sf::VertexArray graph;
	sf::RectangleShape temp;
	temp.setPosition(sf::Vector2f(0,0));
	temp.setFillColor(sf::Color::Blue);
	temp.setSize(sf::Vector2f(100,100));
	//shapes.push_back(temp);
	graph.setPrimitiveType(sf::Quads);
	graph.resize(100 * 100 * 4);
	redo(graph,tree);

		
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed) 
			{
				if (event.key.code == sf::Keyboard::L)
				{
					delete tree;
					seed += 1;
					std::srand(seed);
					tree = new bspG;
					tree->split();
					redo(graph,tree);
				}
			}
		}

		window.clear();
		window.setView(view);
		window.draw(temp);
		window.draw(graph);
		window.display();
	}
	
	*/
	/*sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!", sf::Style::Fullscreen);
	sf::View guiview{ sf::Vector2f(960, 540), sf::Vector2f(1920, 1080) };
	MenuList* list = new MenuList(0,0,8);
	list->AddButton("fucksake");
	GUI lol;
	lol.AddWidget("lis",list);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed)
			{
				
			}
		}

		window.clear();
		window.setView(guiview);
		lol.draw(&window);
		window.display();
	}*/
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