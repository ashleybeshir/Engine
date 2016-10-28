#ifndef _ENGINE_
#define _ENGINE_

#pragma once

#include <vector>
#include "GameState.h"

class GameState;

class Engine
{
public:
	void Start();
	void Delete();

	void ChangeState(GameState* state);
	void PushState(GameState* state);
	void PopState();



	void Run();
	void Input();
	void Draw();

	bool Running() { return running; }
	void Quit() { running = false; }

	Engine();
	~Engine();
private:
	std::vector<GameState*> states;
	bool running;
};


#endif // !_ENGINE_


