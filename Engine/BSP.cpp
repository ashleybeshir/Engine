#include "BSP.h"
#include <random>
#include <iostream>

void BSP::start()
{
	
	BSPNode* root = new BSPNode(0,0,100,100,nullptr);
	nodes.push_back(root);
	split();
}

bool BSP::split()
{
	bool did_split{true};
	
	while (did_split) 
	{
		did_split = false;
		for (int i = 0; i < nodes.size();i++) {
			if (nodes[i]->leftchild == nullptr && nodes[i]->rightchild == nullptr) {
				if (nodes[i]->width > max_size || nodes[i]->height > max_size || std::rand() > 0.25f) {
					bool splitH{ std::rand() > 0.5f };
					if (nodes[i]->width > nodes[i]->height && nodes[i]->width / nodes[i]->height >= 1.25)
						splitH = false;
					else if (nodes[i]->height > nodes[i]->width && nodes[i]->height / nodes[i]->width >= 1.25)
						splitH = true;
					int max{ (splitH ? nodes[i]->height : nodes[i]->width) - min_size };
					if (max <= min_size)
						return false;
					int split{ std::rand() % (max + 1) + min_size };

					if (splitH)
					{
						nodes[i]->leftchild = new BSPNode(nodes[i]->x, nodes[i]->y, nodes[i]->width, split, nodes[i]);
						nodes[i]->rightchild = new BSPNode(nodes[i]->x, nodes[i]->y + split, nodes[i]->width, nodes[i]->height - split, nodes[i]);
					}
					else
					{
						nodes[i]->leftchild = new BSPNode(nodes[i]->x, nodes[i]->y, split, nodes[i]->height, nodes[i]);
						nodes[i]->rightchild = new BSPNode(nodes[i]->x + split, nodes[i]->y, nodes[i]->width - split, nodes[i]->height, nodes[i]);
					}
					nodes.push_back(nodes[i]->leftchild);
					nodes.push_back(nodes[i]->rightchild);
					sf::RectangleShape shape;
					shape.setPosition(nodes[i]->x,nodes[i]->y);
					shape.setSize(sf::Vector2f(nodes[i]->width,nodes[i]->height));
					float fuck = std::rand();
					std::cout << fuck << std::endl;
					if (fuck < 0.2f) 
					{
						shape.setFillColor(sf::Color::Green);
					}
					else if (fuck < 0.4f)
					{
						shape.setFillColor(sf::Color::Blue);
					}
					else if (fuck < 0.6f)
					{
						shape.setFillColor(sf::Color::Magenta);
					}
					else if (fuck < 0.8f)
					{
						shape.setFillColor(sf::Color::Cyan);
					}else
					{
						shape.setFillColor(sf::Color::White);
					}
					rectangle.push_back(shape);
					
					did_split = true;
				}
			}
		}
	}
	return true;
}

BSP::BSP()
{
}


BSP::~BSP()
{
}
