#include "AssetsManager.h"

AssetsManager* AssetsManager::p_instance = NULL;

AssetsManager * AssetsManager::GetInstance()
{
	if (!p_instance)
	{
		p_instance = new AssetsManager;
		p_instance->GetInstance()->LoadTexture("Cave","cave.png");
		p_instance->GetInstance()->LoadTexture("Entity", "monster.png");
	}
	return p_instance;
	// TODO: insert return statement here
}

void AssetsManager::LoadTexture(const std::string & name, const std::string & filename)
{
	sf::Texture temp;
	if (!temp.loadFromFile(filename)) 
	{
		std::cout << "Error loading texture" << std::endl;
	}
	this->data[name] = temp;
}

sf::Texture & AssetsManager::GetRe(const std::string & texture)
{
	return data[texture];
}

AssetsManager::AssetsManager()
{
}


AssetsManager::~AssetsManager()
{
}
