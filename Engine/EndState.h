#ifndef _ENDSTATE_
#define _ENDSTATE_

#pragma once

#include <string>
#include <SFML\Graphics.hpp>
#include "GameState.h"


class EndState : public GameState
{
public:
	void Start();
	void Delete();

	void Pause();
	void Resume();


	void Run(Engine* engine);
	void Input(Engine* engine);
	void Draw(Engine* engine);
	EndState();
	EndState(const std::string string,sf::IntRect rect);
	~EndState();
};


#endif // !_ENDSTATE_



