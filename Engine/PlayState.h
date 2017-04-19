
#ifndef _PLAYSTATE_
#define _PLAYSTATE_

#pragma once

#include <vector>
#include <string>
#include "GameState.h"
#include "Entity.h"
#include "Terrain.h"
#include "Tilemap.h"
#include "Components.h"
#include "AssetsManager.h"
#include "MapNode.h"
#include "EndState.h"
#include "rangeWeapon.h"

typedef std::tuple<int, int> turn;
class PlayState : public GameState
{
	MapNode* DungeonNode;
	Entity* player;
	TileMap map;
	sf::View view;
	sf::Sound sound;
	MenuList* list;
	Label* PHealth;
	Label* PArmor;
	Label* PDamage;
	Label* PStone;
	Label* PMana;
	Label* PLvl;
	Console* console;
	bool input;
	bool _list{false};
	bool throw_weapon{ false };
	bool wear{ false }, drop{ false }, drink{ false }, spells{ false };
	std::vector<turn> potion_turns;
	std::vector<RangeWeapon> range_attacks;

	sf::Vector2i weapon_direction{ 0,0 };
	int stones{3};

	int selected_spell{ 0 };
	bool spell_chosen{ false };

public:

	void Start();
	void Delete();

	void Pause();
	void Resume();


	void Run(Engine* engine);
	void Input(Engine* engine);
	void Draw(Engine* engine);

	void ResetGraphics();

	PlayState();
	PlayState(GenerationType type ,int seed);
	PlayState(MapNode* node);
	~PlayState();
	
};



#endif // !_PLAYSTATE_


