#include "AssetsManager.h"

AssetsManager* AssetsManager::p_instance = NULL;

AssetsManager * AssetsManager::GetInstance()
{
	if (!p_instance)
	{
		p_instance = new AssetsManager;
		
	}
	return p_instance;
	// TODO: insert return statement here
}

AssetsManager::AssetsManager()
{
}


AssetsManager::~AssetsManager()
{
}
