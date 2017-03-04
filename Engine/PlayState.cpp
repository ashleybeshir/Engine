#include "PlayState.h"
#include <iostream>
#include "pathfinder.h"
#include "XmlLoader.h"

PlayState::PlayState()
{
	
}

PlayState::PlayState(GenerationType type,int seed)
{
	
}

PlayState::PlayState(MapNode * node)
{
	DungeonNode = node;
	std::srand(node->GetSeed());
	view.setCenter(sf::Vector2f(350, 300));
	view.setSize(sf::Vector2f(800, 600));
	if (node->GetType() == GenerationType::Cave) 
	{
		map.GenerateCave();
	}
	else map.GenerateDungeon();
	if (node->GetEntityForLvl().empty()) 
	{
		LoadXmlEntity(node->GetEntityForLvl(),node->GetLevel(),map);
	}
	if (node->GetItemForLvl().empty())
	{
		LoadXmlItems(node->GetItemForLvl(),node->GetLevel(),map);
	}
	player = new Entity;
	player->AddComponent<PositionC>(map.GetStairUp().x, map.GetStairUp().y);
	player->AddComponent<DirectionC>();

	sf::Sprite sprite;
	sprite.setTexture(AssetsManager::GetInstance()->GetRe("Entity"));
	sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	sprite.setPosition(map.GetStairUp().x * 32, map.GetStairUp().y * 32);
	player->AddComponent<GraphicC>();
	player->GetComponent<GraphicC>()->sprite = sprite;
	player->AddComponent<InventoryC>();
	player->AddComponent<HealthC>(100);
	
}

PlayState::~PlayState()
{
}



void PlayState::Start()
{
	
	console = new Console(0, 0, 9);
	PHealth = new Label(0,0.20,"Health: ",sf::Color::White);
	engine->gui->AddWidget("health",PHealth);
	engine->gui->AddWidget("console", console);
	
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
	if (input == true)
	{
		std::vector<Entity*> *Entities = &DungeonNode->GetEntityForLvl();
		sf::Vector2i* temp = &player->GetComponent<DirectionC>()->direction;
		sf::Vector2i* pos = &player->GetComponent<PositionC>()->Position;
		bool pos_check{true};
		for (int i=0; i < Entities->size();i++) 
		{
			sf::Vector2i* _pos = &Entities->at(i)->GetComponent<PositionC>()->Position;
			if ((temp->x + pos->x) == _pos->x && (temp->y + pos->y) == _pos->y)
			{
				std::shared_ptr<InventoryC> inv = player->GetComponent<InventoryC>();
				int *health = &Entities->at(i)->GetComponent<HealthC>()->health;
				
		
				if(inv->hand != nullptr)
				{
					*health -= static_cast<Weapon*>(inv->hand)->damage;
					
					if (*health <= 0)
					{
						console->AddLog("Enemy is killed");
						delete Entities->at(i);
						Entities->erase(Entities->begin() + i);
						
					}
					else {
						console->AddLog("Damage done to enemy " + std::to_string(static_cast<Weapon*>(inv->hand)->damage));
						//console->AddLog("Remaining health: " + std::to_string(*health));
					}

				}else
				{
					console->AddLog("U need a weapon to do damage");
				}
				
				pos_check = false;
			}
		}
		if(pos_check)
		{
			pos->x = temp->x + pos->x;
			pos->y = temp->y + pos->y;
			sf::Sprite* graphics = &player->GetComponent<GraphicC>()->sprite;
			graphics->setPosition(pos->x * 32, pos->y * 32);
		}
		

		for (auto& e : *Entities)
		{
			sf::Vector2i* _temp = &e->GetComponent<DirectionC>()->direction;
			sf::Vector2i* _pos = &e->GetComponent<PositionC>()->Position;
			int difference{ heuristic(*pos,*_pos) };
			
			if (difference < 10 && difference != 0) 
			{
				std::string *path = &e->GetComponent<PathC>()->path;
				
					*path = path::pathfinding(Location(_pos->x,_pos->y), Location(player->GetComponent<PositionC>()->Position.x, player->GetComponent<PositionC>()->Position.y), map);
					_temp->x = 0;
					_temp->y = 0;
					
					if (path->at(0) == 'R')
					{
						_temp->x = 1;
						_temp->y = 0;
						path->erase(path->begin());
					}
					else if (path->at(0) == 'L')
					{
						_temp->x = -1;
						_temp->y = 0;
						path->erase(path->begin());
					}
					else if (path->at(0) == 'U')
					{
						_temp->x = 0;
						_temp->y = -1;
						path->erase(path->begin());
					}
					else if (path->at(0) == 'D')
					{
						_temp->x = 0;
						_temp->y = 1;
						path->erase(path->begin());
					}
			}
			if (_temp->x + _pos->x == pos->x && _temp->y + _pos->y == pos->y)
			{
				_temp->x = 0;
				_temp->y = 0;
				e->GetComponent<PathC>()->path = "";
				int damage = e->GetComponent<DamageC>()->damage;
				int *health = &player->GetComponent<HealthC>()->health;
				*health -= damage;
				if (*health > 0) 
				{
					console->AddLog("you have been damaged for: "+std::to_string(damage));
				}
			}
			else
			{
				/*for (auto& b : *Entities) 
				{
					sf::Vector2i check_pos = b->GetComponent<PositionC>()->Position;
					if (!(check_pos.x == _temp->x + _pos->x && check_pos.y == _temp->y + _pos->y))
					{*/
						_pos->x = _temp->x + _pos->x;
						_pos->y = _temp->y + _pos->y;
						sf::Sprite* Egraphics = &e->GetComponent<GraphicC>()->sprite;

						Egraphics->setPosition(_pos->x * 32, _pos->y * 32);
					//}
				//}
				
			}
		}
		PHealth->SetText("Health: "+std::to_string(player->GetComponent<HealthC>()->health));
	}
}

void PlayState::Input(Engine * engine)
{
	input = false;
	player->GetComponent<DirectionC>()->direction.x = 0;
	player->GetComponent<DirectionC>()->direction.y = 0;

	sf::Event event;
	while (engine->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type) {
			engine->window.close();
			
		}
		else if (sf::Event::KeyPressed == event.type) {
			if (event.key.code == sf::Keyboard::Escape) {
				engine->window.close();
			}
			else if (event.key.code == sf::Keyboard::Up)
			{
				input = true;
				player->GetComponent<DirectionC>()->direction.x = 0;
				player->GetComponent<DirectionC>()->direction.y = -1;
			}
			else if (event.key.code == sf::Keyboard::Down)
			{
				input = true;
				player->GetComponent<DirectionC>()->direction.x = 0;
				player->GetComponent<DirectionC>()->direction.y = 1;
			}
			else if (event.key.code == sf::Keyboard::Left)
			{
				input = true;
				player->GetComponent<DirectionC>()->direction.x = -1;
				player->GetComponent<DirectionC>()->direction.y = 0;
			}
			else if (event.key.code == sf::Keyboard::Right)
			{
				input = true;
				player->GetComponent<DirectionC>()->direction.x = 1;
				player->GetComponent<DirectionC>()->direction.y = 0;
			}
			else if (event.key.code == sf::Keyboard::Return)
			{
				input = true;
				int x{ player->GetComponent<PositionC>()->Position.x }, y{ player->GetComponent<PositionC>()->Position.y };
				if (map.getBlock(x, y) == MapType::StairD)
				{
					if (!(DungeonNode->GetLevel() + 1 >= DungeonNode->GetNumberOfLevels())) {
						DungeonNode->SetSeed(DungeonNode->GetSeed() + 1);
						std::srand(DungeonNode->GetSeed());
						DungeonNode->SetLevel(DungeonNode->GetLevel() + 1);
						if (DungeonNode->GetType() == GenerationType::Cave)
						{
							map.GenerateCave();
						}
						else map.GenerateDungeon();
						if (DungeonNode->GetEntityForLvl(DungeonNode->GetLevel()).empty())
						{
							LoadXmlEntity(DungeonNode->GetEntityForLvl(DungeonNode->GetLevel()), DungeonNode->GetLevel(), map);

						}
						else if (DungeonNode->GetItemForLvl(DungeonNode->GetLevel()).empty())
						{
							LoadXmlItems(DungeonNode->GetItemForLvl(DungeonNode->GetLevel()), DungeonNode->GetLevel(), map);
						}


						player->GetComponent<PositionC>()->Position = map.GetStairUp();

					}

				}
				else if (map.getBlock(x, y) == MapType::StairU)
				{
					if (DungeonNode->GetLevel() == 0)
					{
						engine->PopState();
					}
					else {
						DungeonNode->SetSeed(DungeonNode->GetSeed() - 1);
						DungeonNode->SetLevel(DungeonNode->GetLevel() - 1);
						std::srand(DungeonNode->GetSeed());
						if (DungeonNode->GetType() == GenerationType::Cave)
						{
							map.GenerateCave();
						}
						else map.GenerateDungeon();
						player->GetComponent<PositionC>()->Position = map.GetStairDown();
					}
				}

			}
			else if (event.key.code == sf::Keyboard::L)
			{

				input = true;
				player->GetComponent<DirectionC>()->direction.x = 0;
				player->GetComponent<DirectionC>()->direction.y = 0;
				int temp = map.getBlock(player->GetComponent<PositionC>()->Position.x, player->GetComponent<PositionC>()->Position.y);
				/*sf::Vector2i temp{ player->GetComponent<PositionC>()->Position };
				sf::Vector2i temp2;
				temp2.x = temp.x + 5;
				temp2.y = temp.y ;
				std::cout << temp.x << " P " << temp.y << std::endl;
				pathfinding(Location(temp.x,temp.y),Location(temp2.x,temp2.y),map);*/
			}
			else if (event.key.code == sf::Keyboard::G)
			{
				input = true;
				sf::Vector2i loc = player->GetComponent<PositionC>()->Position;
				std::shared_ptr<InventoryC> inv = player->GetComponent<InventoryC>();
				for (int i = 0; i < DungeonNode->GetItemForLvl().size(); i++)
				{
					if (DungeonNode->GetItemForLvl()[i].location == loc)
					{
						Item * item = DungeonNode->GetItemForLvl()[i].items;
						inv->inventory.push_back(item);
						DungeonNode->GetItemForLvl().erase(DungeonNode->GetItemForLvl().begin() + i);
					}
				}
			}
			else if (event.key.code == sf::Keyboard::W)
			{
				if (!_list)
				{
					list = new MenuList(0, 0, 8);
					std::shared_ptr<InventoryC> inv = player->GetComponent<InventoryC>();
					for (auto& c : inv->inventory)
					{
						list->AddButton(c->name);
					}
					engine->gui->AddWidget("inv", list);
					_list = true;
					wear = true;
				}
				else {
					_list = false;
					delete list;
					engine->gui->DeleteWidget("inv");
					wear = false;
				}

			}
			else if (event.key.code == sf::Keyboard::D) 
			{
				if (!_list)
				{
					list = new MenuList(0, 0, 8);
					std::shared_ptr<InventoryC> inv = player->GetComponent<InventoryC>();
					for (auto& c : inv->inventory)
					{
						list->AddButton(c->name);
					}
					engine->gui->AddWidget("inv", list);
					_list = true;
					drop = true;
				}
				else {
					_list = false;
					delete list;
					engine->gui->DeleteWidget("inv");
					drop = false;
				}
			}
		}
		else if (sf::Event::MouseWheelScrolled == event.type) {
			if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
			{

				if (event.mouseWheelScroll.delta == 1)
				{
					view.zoom(0.9f);
				}
				else
				{
					view.zoom(1.1f);
				}
			}
			
		}
		else if (sf::Event::MouseButtonPressed == event.type) {
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2i pixelPos = sf::Mouse::getPosition(engine->window);
				sf::Vector2f worldPos = engine->window.mapPixelToCoords(pixelPos, engine->guiview);
				if (_list)
				{
					if (list->clicked(worldPos.x, worldPos.y))
					{
						if(wear)
						{
							sf::String find_item = list->GetString();
							std::shared_ptr<InventoryC> inv = player->GetComponent<InventoryC>();
							for(int i=0;i < inv->inventory.size();i++)
							{
								if (inv->inventory[i]->name == find_item)
								{
									if(inv->inventory[i]->Type == ITEM::ItemType::Armor)
									{
										if (inv->armor == nullptr)
										{
											inv->armor = inv->inventory[i];
											inv->inventory.erase(inv->inventory.begin()+i);
											wear = false;
											_list = false;
											delete list;
											engine->gui->DeleteWidget("inv");
											break;
										}else
										{
											inv->inventory.push_back(inv->armor);
											inv->armor = inv->inventory[i];
											inv->inventory.erase(inv->inventory.begin() + i);
											wear = false;
											_list = false;
											delete list;
											engine->gui->DeleteWidget("inv");
											break;
										}
										
									}else if(inv->inventory[i]->Type == ITEM::ItemType::Weapon)
									{
										if (inv->hand == nullptr)
										{
											inv->hand = inv->inventory[i];
											inv->inventory.erase(inv->inventory.begin() + i);
											wear = false;
											_list = false;
											delete list;
											engine->gui->DeleteWidget("inv");
											break;
										}
										else
										{
											inv->inventory.push_back(inv->hand);
											inv->hand = inv->inventory[i];
											inv->inventory.erase(inv->inventory.begin() + i);
											wear = false;
											_list = false;
											delete list;
											engine->gui->DeleteWidget("inv");
											break;
										}
									}
								}
							}
							wear = false;
						}else if(drop)
						{
							sf::String find_item = list->GetString();
							std::shared_ptr<InventoryC> inv = player->GetComponent<InventoryC>();
							sf::Vector2i player_pos = player->GetComponent<PositionC>()->Position;
							for (int i=0;i < inv->inventory.size();i++) 
							{
								if (inv->inventory[i]->name == find_item)
								{
									inv->inventory[i]->sprite.setPosition(player_pos.x*32,player_pos.y*32);
									ItemBag bag(inv->inventory[i],player_pos);
									DungeonNode->GetItemForLvl().push_back(bag);
									inv->inventory.erase(inv->inventory.begin()+i);
									drop = false;
									_list = false;
									delete list;
									engine->gui->DeleteWidget("inv");
									break;
								}
							}
						}
					}
				}
			}
			
		}
		else if (sf::Event::MouseMoved == event.type) {
			sf::Vector2i pixelPos = sf::Mouse::getPosition(engine->window);
			sf::Vector2f worldPos = engine->window.mapPixelToCoords(pixelPos, engine->guiview);
			engine->gui->check(worldPos.x, worldPos.y);
			
		}
		
		
	}
	
}

void PlayState::Draw(Engine * engine)
{
	sf::Vector2f pos = player->GetComponent<GraphicC>()->sprite.getPosition();
	view.setCenter(pos);
	engine->window.setView(view);
	map.Draw(engine->window);
	for (auto& e : DungeonNode->GetItemForLvl())
	{
		engine->window.draw(e.items->sprite);
	}
	engine->window.draw(player->GetComponent<GraphicC>()->sprite);

	for (auto& e : DungeonNode->GetEntityForLvl())
	{	
		engine->window.draw(e->GetComponent<GraphicC>()->sprite);
	}
	
}
