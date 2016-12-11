#pragma once
#ifndef _PLAYSTATE_
#define _PLAYSTATE_
#pragma

#include <vector>
#include "GameState.h"
#include "Entity.h"
#include "Terrain.h"
#include "Tilemap.h"
#include "Components.h"

class PlayState : public GameState
{
	
	std::vector<std::unique_ptr<Entity>> Entities;
	sf::Texture CharTextures;
	TileMap map;
public:

	void Start();
	void Delete();

	void Pause();
	void Resume();


	void Run(Engine* engine);
	void Input(Engine* engine);
	void Draw(Engine* engine);

	PlayState();
	PlayState(GenerationType type);
	~PlayState();
protected:
	void AddEntity(Entity* entity);
};



#endif // !_PLAYSTATE_


