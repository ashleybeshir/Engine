#include "PlayState.h"



PlayState::PlayState()
{
}

PlayState::PlayState(bool type)
{
	Dungeon_Cave = type;
}

PlayState::~PlayState()
{
}

void PlayState::AddEntity(Entity * entity)
{
	Entities.push_back(std::unique_ptr<Entity>(entity));
}

void PlayState::Start()
{
	int max_leaf_size{20};
	
	BSP helper;
	BSP* root = new BSP(0, 0, 80, 80);
	bsp.push_back(root);

	bool did_split{true};
	while (did_split)
	{
		did_split = false;
		for(int i=0;i < bsp.size();i++)
		{
			if (bsp[i]->LeftChild == nullptr && bsp[i]->RightChild == nullptr) // if this Leaf is not already split...
			{
			
				if (bsp[i]->width > max_leaf_size || bsp[i]->height > max_leaf_size || std::rand() > 0.25)
				{
					if (bsp[i]->Split()) // split the Leaf!
					{
						// if we did split, push the child leafs to the Vector so we can loop into them next
						bsp.push_back(bsp[i]->LeftChild);
						bsp.push_back(bsp[i]->RightChild);
						did_split = true;
					}
				}
			}
		}
	}
	root->CreateRooms();
}

void PlayState::Delete()
{
}

void PlayState::Pause()
{
}

void PlayState::Resume()
{
}

void PlayState::Run(Engine * engine)
{
	/*for (size_t i = 0; i < Entities.size(); i++)
	{
		Entities[i]->Update();
	}*/
}

void PlayState::Input(Engine * engine)
{
	sf::Event event;
	while (engine->window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			engine->window.close();
			break;
		default:
			break;
		}
	}
}

void PlayState::Draw(Engine * engine)
{
	/*for (size_t i = 0; i < Entities.size(); i++)
	{
		Entities[i]->Draw(engine->window);
	}*/
	for (size_t i = 0; i < bsp.size(); i++)
	{
		engine->window.draw(bsp[i]->room);
	}
}
