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
	if(!AssetsManager::GetInstance()->GetInventory().empty())
	{
		player->AddComponent<InventoryC>(AssetsManager::GetInstance()->GetInventory());
		if(player->GetComponent<InventoryC>()->hand == nullptr)
		{
			player->GetComponent<InventoryC>()->hand = new Weapon("Fist",5);
		}
	}
	else 
	{ 
		player->AddComponent<InventoryC>(); 
		player->GetComponent<InventoryC>()->hand = new Weapon("Fist", 5);
	}
	
	player->AddComponent<HealthC>(100);
	
}

PlayState::~PlayState()
{
}



void PlayState::Start()
{
	
	console = new Console(0, 0, 9);
	PHealth = new Label(0,0.20,"Health: ",sf::Color::White);
	PArmor = new Label(0, 0.22, "Armor: ", sf::Color::White);
	PDamage = new Label(0, 0.24, "Damage: ", sf::Color::White);
	Label* name = new Label(0.16,0.02, "",sf::Color::White);
	Label* damage = new Label(0.16, 0.04, "", sf::Color::White);
	Label* health = new Label(0.16, 0.06, "", sf::Color::White);
	engine->gui->AddWidget("armor", PArmor);
	engine->gui->AddWidget("damage", PDamage);
	engine->gui->AddWidget("health",PHealth);
	engine->gui->AddWidget("console", console);
	engine->gui->AddWidget("ename", name);
	engine->gui->AddWidget("edamage", damage);
	engine->gui->AddWidget("ehealth", health);
	engine->gui->AddWidget("enemyname", new Label(0.16, 0, "Enemy Info:", sf::Color::White));
	
	
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
		int *health = &player->GetComponent<HealthC>()->health;
		if (*health < 100) *health += 1;
		
		if (!potion_turns.empty())
		{
			if (std::get<0>(potion_turns[0]) > 0) 
			{
				*health += std::get<1>(potion_turns[0]);
				std::get<0>(potion_turns[0]) = std::get<0>(potion_turns[0]) - 1;
			}
			else
			{
				potion_turns.erase(potion_turns.begin());
			}
		}
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
						sound.setBuffer(AssetsManager::GetInstance()->GetSound("death"));
						sound.play();
					}
					else {
						console->AddLog("Damage done to enemy " + std::to_string(static_cast<Weapon*>(inv->hand)->damage));
						sf::Sound sound;
						sound.setBuffer(AssetsManager::GetInstance()->GetSound("Hit"));
						sound.play();
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
				if(player->GetComponent<InventoryC>()->armor != nullptr)
				{
					int armor = static_cast<Armor*>(player->GetComponent<InventoryC>()->armor)->protection;
					damage = damage - (damage - (damage * armor / 100));
					*health -= damage;
				}
				else {
					*health -= damage;
				}
				console->AddLog("you have been damaged for: "+std::to_string(damage));
				sound.setBuffer(AssetsManager::GetInstance()->GetSound("Hurt"));
				sound.play();
				if(*health <= 0)
				{
					engine->ChangeState(new EndState("monster"));
				}
			}
			else
			{
				bool enemy_pos_check{true};
				for (auto& b : *Entities) 
				{
					sf::Vector2i check_pos = b->GetComponent<PositionC>()->Position;
					if ((check_pos.x == _temp->x + _pos->x && check_pos.y == _temp->y + _pos->y))
					{
						enemy_pos_check = false;
						_temp->x = 0;
						_temp->y = 0;
						break;
						
					}
				}
				if (enemy_pos_check)
				{
					if(map.isPassable(_temp->x + _pos->x, _temp->y + _pos->y))
					{
						_pos->x = _temp->x + _pos->x;
						_pos->y = _temp->y + _pos->y;

						sf::Sprite* Egraphics = &e->GetComponent<GraphicC>()->sprite;
						Egraphics->setPosition(_pos->x * 32, _pos->y * 32);
					}
					
				}		
			}
		}
	}
	PHealth->SetText("Health: " + std::to_string(player->GetComponent<HealthC>()->health));
	if (player->GetComponent<InventoryC>()->armor == nullptr)
	{
		PArmor->SetText("Armor: 0");
	}
	else PArmor->SetText("Armor: " + std::to_string(static_cast<Armor*>(player->GetComponent<InventoryC>()->armor)->protection));
	if ((player->GetComponent<InventoryC>()->hand == nullptr))
	{
		PDamage->SetText("Damage: 0");
	}
	else PDamage->SetText("Damage: " + std::to_string(static_cast<Weapon*>(player->GetComponent<InventoryC>()->hand)->damage));
	
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
						AssetsManager::GetInstance()->SetInventory(player->GetComponent<InventoryC>()->inventory);
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
						sound.setBuffer(AssetsManager::GetInstance()->GetSound("Pick"));
						sound.play();
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
			else if (event.key.code == sf::Keyboard::Q)
			{
				if (!_list)
				{
					list = new MenuList(0, 0, 8);
					std::shared_ptr<InventoryC> inv = player->GetComponent<InventoryC>();
					for (auto& c : inv->inventory)
					{
						if (c->Type == ITEM::ItemType::Potion) 
						{
							list->AddButton(c->name);
						}	
					}
					engine->gui->AddWidget("inv", list);
					_list = true;
					drink = true;
				}
				else {
					_list = false;
					delete list;
					engine->gui->DeleteWidget("inv");
					drink = false;
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
											input = true;
											break;
										}
										else
										{
											if (inv->hand->name.toAnsiString().compare("fist") == 0)
											{
												delete inv->hand;
												inv->hand = inv->inventory[i];
												inv->inventory.erase(inv->inventory.begin() + i);
												wear = false;
												_list = false;
												delete list;
												engine->gui->DeleteWidget("inv");
												input = true;
												break;
											}
											else {
												inv->inventory.push_back(inv->hand);
												inv->hand = inv->inventory[i];
												inv->inventory.erase(inv->inventory.begin() + i);
												wear = false;
												_list = false;
												delete list;
												engine->gui->DeleteWidget("inv");
												input = true;
												break;
											}
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
									input = true;
									break;
								}
							}
						}
						else if (drink) 
						{
							sf::String find_item = list->GetString();
							std::shared_ptr<InventoryC> inv = player->GetComponent<InventoryC>();
							
							for (int i = 0; i < inv->inventory.size(); i++)
							{
								if (inv->inventory[i]->name == find_item)
								{
									potion_turns.push_back(std::make_tuple(static_cast<Potion*>(inv->inventory[i])->turns, static_cast<Potion*>(inv->inventory[i])->amount));
									inv->inventory.erase(inv->inventory.begin() + i);
									drink = false;
									_list = false;
									delete list;
									engine->gui->DeleteWidget("inv");
									input = true;
									break;
								}
							}
						}
					}
				}
				else 
				{
					sf::Vector2f e_pos = engine->window.mapPixelToCoords(pixelPos, view);
					sf::Vector2i clicked_pos;
					clicked_pos.x = std::floor(e_pos.x/32);
					clicked_pos.y = std::floor(e_pos.y/32);
					//std::cout << clicked_pos.x << " " << clicked_pos.y << std::endl;
					std::vector<Entity*> *Entities = &DungeonNode->GetEntityForLvl();
					bool enemy_test{ false };
					for (auto& c : *Entities) 
					{
						sf::Vector2i pos = c->GetComponent<PositionC>()->Position;
						if (clicked_pos == pos) 
						{
							enemy_test = true;
							static_cast<Label*>(engine->gui->GetWidget("ename"))->SetText("Name: "+c->GetComponent<NameC>()->name);
							static_cast<Label*>(engine->gui->GetWidget("edamage"))->SetText("Damage: "+std::to_string(c->GetComponent<DamageC>()->damage));
							static_cast<Label*>(engine->gui->GetWidget("ehealth"))->SetText("Health: "+std::to_string(c->GetComponent<HealthC>()->health));
							break;
						}
						
					}
					if (!enemy_test)
					{
						static_cast<Label*>(engine->gui->GetWidget("ename"))->SetText("");
						static_cast<Label*>(engine->gui->GetWidget("edamage"))->SetText("");
						static_cast<Label*>(engine->gui->GetWidget("ehealth"))->SetText("");
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

void PlayState::ResetGraphics()
{
	engine->gui->Clear();
	console = new Console(0, 0, 9);
	PHealth = new Label(0, 0.20, "Health: ", sf::Color::White);
	PArmor = new Label(0, 0.22, "Armor: ", sf::Color::White);
	PDamage = new Label(0, 0.24, "Damage: ", sf::Color::White);
	Label* name = new Label(0.16, 0.02, "", sf::Color::White);
	Label* damage = new Label(0.16, 0.04, "", sf::Color::White);
	Label* health = new Label(0.16, 0.06, "", sf::Color::White);
	engine->gui->AddWidget("armor", PArmor);
	engine->gui->AddWidget("damage", PDamage);
	engine->gui->AddWidget("health", PHealth);
	engine->gui->AddWidget("console", console);
	engine->gui->AddWidget("ename", name);
	engine->gui->AddWidget("edamage", damage);
	engine->gui->AddWidget("ehealth", health);
	engine->gui->AddWidget("enemyname", new Label(0.16, 0, "Enemy Info:", sf::Color::White));
}
