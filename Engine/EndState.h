#ifndef _ENDSTATE_
#define _ENDSTATE_

#pragma once

#include <string>
#include <SFML\Graphics.hpp>
#include "GameState.h"
#include "MenuState.h"

class EndState : public GameState
{
	std::string death;
public:
	void Start();
	void Delete();

	void Pause();
	void Resume();


	void Run(Engine* engine);
	void Input(Engine* engine);
	void Draw(Engine* engine);

	void ResetGraphics();

	EndState();
	EndState(const std::string string);
	~EndState();
};


#endif // !_ENDSTATE_



