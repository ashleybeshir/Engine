#include <SFML\Graphics.hpp>
#include "Engine.h"
#include "MenuState.h"
#include "AssetsManager.h"
#include "Entity.h"
#include "PlayState.h"
#include "Terrain.h"

void main()
{
	
	Engine engine;

	engine.Start();
	engine.PushState(new WorldState(50));

	while (engine.window.isOpen())
	{
		
		engine.Run();
		engine.Input();
		engine.Draw();
	}
}