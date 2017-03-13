#include "AssetsManager.h"

AssetsManager* AssetsManager::p_instance = NULL;

AssetsManager * AssetsManager::GetInstance()
{
	if (!p_instance)
	{
		p_instance = new AssetsManager;
		p_instance->GetInstance()->LoadTexture("Cave","cave.png");
		p_instance->GetInstance()->LoadTexture("Entity", "monster.png");
		p_instance->GetInstance()->LoadTexture("Item","items.png");
		p_instance->GetInstance()->LoadTexture("Map", "Ground.png");
		p_instance->GetInstance()->LoadTexture("dungeon", "dungeon.png");
		p_instance->GetInstance()->LoadTexture("potion", "potion.png");
		p_instance->GetInstance()->LoadTexture("armor", "armor.png");
		p_instance->GetInstance()->LoadTexture("weapon", "weapon.png");
		p_instance->GetInstance()->LoadMusic("Hurt","hurt.wav");
		p_instance->GetInstance()->LoadMusic("Hit", "hit.wav");
		p_instance->GetInstance()->LoadMusic("Pick", "pickup.wav");
		p_instance->GetInstance()->LoadMusic("death", "death.wav");
		p_instance->GetInstance()->colorsheets[0].Normal = sf::Color::Green;
		p_instance->GetInstance()->colorsheets[0].InView = sf::Color::Blue;
		p_instance->GetInstance()->colorsheets[0].Clicked = sf::Color::Red;
		if (!p_instance->GetInstance()->GetFont().loadFromFile("arvin.ttf"))
		{
			std::cout << "couldnt load font" << std::endl;
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

void AssetsManager::LoadMusic(const std::string & name, const std::string & filename)
{

	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile(filename))
	{

	}
	this->sounds[name] = buffer;
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
