#ifndef _XMLLOADER_
#define _XMLOADER_
#pragma once
#include <random>
#include <math.h>
#include "tinyxml2.h"
#include "PlayState.h"
sf::Vector2i find_location(TileMap& map)
{
	sf::Vector2i location;
	location.x = std::rand() % 99 + 1;
	location.y = std::rand() % 99 + 1;
	while (!map.isPassable(location.x, location.y))
	{
		location.x = std::rand() % 99 + 1;
		location.y = std::rand() % 99 + 1;
	}
	return location;
}
bool LoadXmlEntity(std::vector<Entity*>& entities, int level, TileMap& map)
{
	std::vector<Entity*> temp;
	int number = std::rand() % 13+3;

	tinyxml2::XMLDocument doc = new tinyxml2::XMLDocument();
	doc.LoadFile("Entity.xml");
	
	bool test{ true };
	for (tinyxml2::XMLElement* root = doc.RootElement(); root != NULL; root = root->NextSiblingElement())
	{
		Entity* entity = new Entity;
		for (tinyxml2::XMLElement* child = root->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
		{
			if (strcmp(child->Value(), "level") == 0)
			{
				if (atoi(child->GetText()) >= level && atoi(child->GetText()) <= (level + 1))
				{
					test = false;
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
		if (!test) 
		{
			temp.push_back(entity);
		}
		else
		{
			delete entity;
		}
	}

	for (int i=0;i < number;i++) 
	{
		int random_pos = std::rand() % temp.size();

		Entity* entity = new Entity;
		std::string test = temp[random_pos]->GetComponent<NameC>()->name;
		entity->AddComponent<NameC>(test);
		entity->AddComponent<HealthC>(temp[random_pos]->GetComponent<HealthC>()->health);
		entity->AddComponent<EnergyC>(temp[random_pos]->GetComponent<EnergyC>()->Energy);
		entity->AddComponent<DamageC>(temp[random_pos]->GetComponent<DamageC>()->damage);
		entity->AddComponent<GraphicC>();

		sf::Sprite* spr = &temp[random_pos]->GetComponent<GraphicC>()->sprite;
		sf::Sprite* sprite = &entity->GetComponent<GraphicC>()->sprite;
		sprite->setTexture(AssetsManager::GetInstance()->GetRe("Entity"));
		sprite->setTextureRect(spr->getTextureRect());
		sf::Vector2i loc = find_location(map);
		sprite->setPosition(loc.x*32,loc.y*32);
		entity->AddComponent<PositionC>(loc.x,loc.y);
		entity->AddComponent<DirectionC>();
		entity->AddComponent<PathC>();
		entity->AddComponent<FreezeC>();
		entities.push_back(entity);
	}
	for (auto& c : temp) 
	{
		delete c;
	}
	return true;
}

bool LoadXmlItems(std::vector<ItemBag>& items,int level, TileMap& map) 
{
	int number = std::rand() % 16 + 1;
	std::vector<Item*> temp;
	tinyxml2::XMLDocument doc = new tinyxml2::XMLDocument();
	doc.LoadFile("item.xml");
	
	
	for (tinyxml2::XMLElement* root = doc.RootElement(); root != NULL; root = root->NextSiblingElement())
	{
		bool test{ true };
		Potion* potion{ nullptr };
		Armor *armor{ nullptr };
		Weapon	*weapon{nullptr};

		if (strcmp(root->Value(), "potion") == 0)
		{
			potion = new Potion();
		}
		else if (strcmp(root->Value(), "armor") == 0)
		{
			armor = new Armor();
		}
		else if (strcmp(root->Value(), "weapon") == 0)
		{
			weapon = new Weapon();
		}
		
		for (tinyxml2::XMLElement* child = root->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
		{
			

			if (strcmp(child->Value(), "level") == 0)
			{
				if (atoi(child->GetText()) >= level && atoi(child->GetText()) <= (level+1))
				{
					test = false;
				}
			}
			if (strcmp(root->Value(), "potion") == 0)
			{
				if (strcmp(child->Value(), "name") == 0)
				{
					potion->name = child->GetText();
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
					potion->sprite.setTexture(AssetsManager::GetInstance()->GetRe("Item"));
					int x, y;
					if (pos < 6)
					{
						x = pos * 32;
					}
					else x = (pos % 6) * 32;
					y = std::floor(pos / 32) * 32;
					potion->sprite.setTextureRect(sf::IntRect(x, y, 32, 32));
					//potion->sprite.setColor(sf::Color(255, 255, 255, 200));
				}

			}
			else if (strcmp(root->Value(), "armor") == 0)
			{

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
					armor->sprite.setTexture(AssetsManager::GetInstance()->GetRe("Item"));
					int x, y;
					if (pos < 10)
					{
						x = pos * 32;
					}
					else x = (pos % 10) * 32;
					y = std::floor(pos / 32) * 32;
					armor->sprite.setTextureRect(sf::IntRect(x, y, 32, 32));
					//armor->sprite.setColor(sf::Color(255, 255, 255, 200));
				}
			}
			else if (strcmp(root->Value(), "weapon") == 0)
			{

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
					weapon->sprite.setTexture(AssetsManager::GetInstance()->GetRe("Item"));
					int x, y;
					if (pos < 10)
					{
						x = pos * 32;
					}
					else x = (pos % 10) * 32;
					y = std::floor(pos / 32) * 32;
					weapon->sprite.setTextureRect(sf::IntRect(x, y, 32, 32));
					//std::cout << pos << std::endl;
					//weapon->sprite.setColor(sf::Color(255, 255, 255, 200));
				}
			}
		}
		
		if (test) {
			if (potion != nullptr)
			{
				temp.push_back(potion);
			}
			else if (weapon != nullptr)
			{
				temp.push_back(weapon);
			}
			else if (armor != nullptr)
			{
				temp.push_back(armor);
			}
		}else 
		{
			if (potion != nullptr)
			{
				delete potion;
			}
			else if (weapon != nullptr)
			{
				delete weapon;
			}
			else if (armor != nullptr)
			{
				delete armor;
			}
		}
	}

	
	for (int x = 0; x < number; x++)
	{
		int rand_pos = std::rand() % (temp.size()-1);
		
		if (temp[rand_pos]->Type == ITEM::ItemType::Potion) 
		{
			Potion * temporary = static_cast<Potion*>(temp[rand_pos]);
			Potion* nitem = new Potion();
			nitem->name = temporary->name;
			nitem->amount = temporary->amount;
			nitem->sprite.setTexture(AssetsManager::GetInstance()->GetRe("potion"));
			nitem->sprite.setTextureRect(temporary->sprite.getTextureRect());
			nitem->turns = temporary->turns;
			sf::Vector2i loc = find_location(map);
			nitem->sprite.setPosition(loc.x * 32,loc.y*32);
			items.push_back(ItemBag(nitem,loc));
		}
		else if (temp[rand_pos]->Type == ITEM::ItemType::Weapon)
		{
			Weapon * temporary = static_cast<Weapon*>(temp[rand_pos]);
			Weapon* nitem = new Weapon();
			nitem->name = temporary->name;
			nitem->damage = temporary->damage;
			nitem->sprite.setTexture(AssetsManager::GetInstance()->GetRe("weapon"));
			nitem->sprite.setTextureRect(temporary->sprite.getTextureRect());
			sf::Vector2i loc = find_location(map);
			nitem->sprite.setPosition(loc.x * 32, loc.y * 32);
			items.push_back(ItemBag(nitem, loc));
		}else if(temp[rand_pos]->Type == ITEM::ItemType::Armor)
		{
			Armor * temporary = static_cast<Armor*>(temp[rand_pos]);
			Armor* nitem = new Armor();
			nitem->name = temporary->name;
			nitem->protection = temporary->protection;
			nitem->sprite.setTexture(AssetsManager::GetInstance()->GetRe("armor"));
			nitem->sprite.setTextureRect(temporary->sprite.getTextureRect());
			sf::Vector2i loc = find_location(map);
			nitem->sprite.setPosition(loc.x * 32, loc.y * 32);
			items.push_back(ItemBag(nitem, loc));
		}
	}
	
	for (auto& c: temp) 
	{
		delete c;
	}
	
	

	
	return false;
}

#endif