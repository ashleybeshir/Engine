#pragma once
#ifndef _WORLDSTATE_
#define _WORLDSTATE_

#include <vector>
#include <SFML\Graphics.hpp>
#include "GameState.h"
#include "Terrain.h"
#include "PlayState.h"

class WorldState : public GameState
{
	
	int seed{0};
	std::vector<std::vector<TerrainType>> Terrain;
	sf::VertexArray GTerrain;
	sf::View view;
	
	sf::VertexArray Gplayer;
	sf::Vector2i player;
	sf::Texture* texture;
	sf::Texture* tplayer{ &AssetsManager::GetInstance()->GetRe("Entity") };

	Label* name;
public:
	void Start();
	void Delete();

	void Pause();
	void Resume();


	void Run(Engine* engine);
	void Input(Engine* engine);
	void Draw(Engine* engine);

	void ResetGraphics();

	WorldState(int seed);
	WorldState();
	~WorldState();
};


#endif // !_WORLDSTATE_





