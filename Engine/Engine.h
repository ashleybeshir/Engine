#ifndef _ENGINE_
#define _ENGINE_

#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include "GameState.h"
#include <map>
#include "GUI.h"
#include "AssetsManager.h"

class GameState;

class Engine
{
public:
	std::map<int, int> wtd;
	sf::RenderWindow window;
	GUI* gui;
	sf::View guiview{ sf::Vector2f(960, 540), sf::Vector2f(1920, 1080) };
	//sf::View guiview{ sf::Vector2f(400, 400), sf::Vector2f(800, 800) };
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


