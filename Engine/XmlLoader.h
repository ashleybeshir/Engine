#ifndef _XMLLOADER_
#define _XMLOADER_
#pragma once
#include <random>
#include <math.h>
#include "tinyxml2.h"
#include "PlayState.h"

bool LoadXmlEntity(std::vector<Entity*>* entities, int level, TileMap& map)
{
	int number = std::rand() % (level + 10) + 1;

	tinyxml2::XMLDocument doc = new tinyxml2::XMLDocument();
	doc.LoadFile("Entity.xml");
	while (number > 0) {
		bool skip{ true };
		for (tinyxml2::XMLElement* root = doc.RootElement(); root != NULL; root = root->NextSiblingElement())
		{
			if (skip)
			{
				Entity* entity = new Entity;
				for (tinyxml2::XMLElement* child = root->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
				{

					//std::cout << child->GetText() << std::endl;
					if (strcmp(child->Value(), "level") == 0)
					{
						if (atoi(child->GetText()) != level)
						{
							skip = false;
						}
					}
					if (strcmp(child->Value(), "name") == 0)
					{
						entity->AddComponent<NameC>(child->GetText());
					}
					else if (strcmp(child->Value(), "health") == 0)
					{
						entity->AddComponent<HealthC>(atoi(child->GetText()));
					}
					else if (strcmp(child->Value(), "energy") == 0)
					{
						entity->AddComponent<EnergyC>(atoi(child->GetText()));
					}
					else if (strcmp(child->Value(), "damage") == 0)
					{
						entity->AddComponent<DamageC>(atoi(child->GetText()));
					}
					else if (strcmp(child->Value(), "sprite") == 0)
					{
						int pos = atoi(child->GetText());
						entity->AddComponent<GraphicC>();
						sf::Sprite* sprite = &entity->GetComponent<GraphicC>()->sprite;
						sprite->setTexture(AssetsManager::GetInstance()->GetRe("Entity"));
						int x, y;
						if (pos < 6) 
						{
							x = pos * 32;
						}
						else x = (pos % 6) * 32;
						y = std::floor(pos /36) * 32;
						sprite->setTextureRect(sf::IntRect(x,y, 32, 32));
					}
				}
				int x, y;
				do
				{
					x = std::rand() % 100 + 1;
					y = std::rand() % 100 + 1;
				} while (!map.isPassable(x, y));
				entity->AddComponent<PositionC>(x, y);
				entity->AddComponent<DirectionC>();
				entities->push_back(entity);
				number -= 1;
			}
		}
	}
	return true;
}

#endif