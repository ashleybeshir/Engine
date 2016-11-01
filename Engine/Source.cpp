#include <SFML\Graphics.hpp>
#include "Engine.h"
#include "MenuState.h"
#include "AssetsManager.h"

void main()
{
	//AssetsManager
	Engine engine;

	engine.Start();
	engine.PushState(new MenuState);

	while (engine.window.isOpen())
	{
		engine.Run();
		engine.Input();
		engine.Draw();
	}
}