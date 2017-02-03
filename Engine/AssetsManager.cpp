#include "AssetsManager.h"

AssetsManager* AssetsManager::p_instance = NULL;

AssetsManager * AssetsManager::GetInstance()
{
	if (!p_instance)
	{
		p_instance = new AssetsManager;
		p_instance->GetInstance()->LoadTexture("Cave","cave.png");
		p_instance->GetInstance()->LoadTexture("Entity", "monster.png");
		p_instance->GetInstance()->LoadTexture("Items","item.png");
		p_instance->GetInstance()->colorsheets[0] = new ColorSheet(sf::Color::Black, sf::Color::Blue, sf::Color::Magenta);
		if (p_instance->GetInstance()->GetFont()->loadFromFile("arvin.ttf"))
		{

		}
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

void AssetsManager::AddDungeon(MapNode * node)
{
	dungeons[node->GetSeed()] = node;
}

MapNode * AssetsManager::GetDungeon(int seed)
{
	if (dungeons.find(seed) != dungeons.end()) 
	{
		return dungeons[seed];
	}else return nullptr;
	
}

AssetsManager::AssetsManager()
{
}


AssetsManager::~AssetsManager()
{
}
