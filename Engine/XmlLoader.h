#ifndef _XMLLOADER_
#define _XMLOADER_
#pragma once
#include <random>
#include <math.h>
#include "tinyxml2.h"
#include "PlayState.h"

bool LoadXmlEntity(std::vector<Entity*>& entities, int level, TileMap& map)
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
					x = std::rand() % 99 + 1;
					y = std::rand() % 99 + 1;
				} while (!map.isPassable(x, y));
				if (!map.isPassable(x, y)) std::cout << "weird" << std::endl;
				entity->AddComponent<PositionC>(x, y);
				entity->AddComponent<DirectionC>();
				entity->AddComponent<PathC>();
				entities.push_back(entity);
				number -= 1;
			}
		}
	}
	return true;
}

bool LoadXmlItems(std::vector<Item*>& items,int level, TileMap& map) 
{
	/*int number = std::rand() % (level + 10) + 1;
	tinyxml2::XMLDocument doc = new tinyxml2::XMLDocument();
	doc.LoadFile("item.xml");
	while (number > 0) 
	{
		bool skip{true};
		for (tinyxml2::XMLElement* root = doc.RootElement(); root != NULL; root = root->NextSiblingElement())
		{
			Potion* potion;
			Armor* armor;
			Weapon* weapon;
			if (strcmp(root->Value(),"potion") == 0)
			{
				potion = new Potion();
			}
			else if (strcmp(root->Value(), "armor")== 0)
			{
				armor = new Armor();
			}
			else if (strcmp(root->Value(), "weapon") == 0)
			{
				weapon = new Weapon();
			}
			for (tinyxml2::XMLElement* child = root->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
			{
				if (strcmp(root->Value(), "potion") == 0)
				{
					if (strcmp(child->Value(), "level") == 0)
					{
						if (atoi(child->GetText()) != level)
						{
							skip = false;
						}
						
					}
					if (strcmp(child->Value(), "name") == 0)
					{
						//potion->name = child->GetText();
					}
					if (strcmp(child->Value(), "amount") == 0)
					{
						potion->amount = atoi(child->GetText());
					}
					if (strcmp(child->Value(), "perturn") == 0)
					{
						potion->turns = atoi(child->GetText());
					}
					if (strcmp(child->Value(), "sprite") == 0)
					{
						
						int pos = atoi(child->GetText());
						potion->sprite.setTexture(AssetsManager::GetInstance()->GetRe("Entity"));
						int x, y;
						if (pos < 6)
						{
							x = pos * 32;
						}
						else x = (pos % 6) * 32;
						y = std::floor(pos / 36) * 32;
						potion->sprite.setTextureRect(sf::IntRect(x, y, 32, 32));
					}

				}
				else if (strcmp(root->Value(), "armor") == 0)
				{
					if (strcmp(child->Value(), "level") == 0)
					{
						if (atoi(child->GetText()) != level)
						{
							skip = false;
						}

					}
					if (strcmp(child->Value(), "name") == 0)
					{
						armor->name = child->GetText();
					}
					if (strcmp(child->Value(), "amount") == 0)
					{
						armor->protection = atoi(child->GetText());
					}
					if (strcmp(child->Value(), "sprite") == 0)
					{

						int pos = atoi(child->GetText());
						armor->sprite.setTexture(AssetsManager::GetInstance()->GetRe("Entity"));
						int x, y;
						if (pos < 6)
						{
							x = pos * 32;
						}
						else x = (pos % 6) * 32;
						y = std::floor(pos / 36) * 32;
						armor->sprite.setTextureRect(sf::IntRect(x, y, 32, 32));
					}
				}
				else if (strcmp(root->Value(), "weapon") == 0)
				{
					if (strcmp(child->Value(), "level") == 0)
					{
						if (atoi(child->GetText()) != level)
						{
							skip = false;
						}

					}
					if (strcmp(child->Value(), "name") == 0)
					{
						weapon->name = child->GetText();
					}
					if (strcmp(child->Value(), "amount") == 0)
					{
						weapon->damage = atoi(child->GetText());
					}
					
					if (strcmp(child->Value(), "sprite") == 0)
					{

						int pos = atoi(child->GetText());
						weapon->sprite.setTexture(AssetsManager::GetInstance()->GetRe("Entity"));
						int x, y;
						if (pos < 6)
						{
							x = pos * 32;
						}
						else x = (pos % 6) * 32;
						y = std::floor(pos / 36) * 32;
						weapon->sprite.setTextureRect(sf::IntRect(x, y, 32, 32));
					}
				}
			}
		}
	}*/
	return false;
}
#endif