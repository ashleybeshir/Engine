#include "Entity.h"
#include "Components.h"
#include "PlayState.h"
#include "tinyxml2.h"
static void LoadXmlEntity() 
{
	tinyxml2::XMLDocument doc = new tinyxml2::XMLDocument();
	doc.LoadFile("Entity.xml");
	for (tinyxml2::XMLElement* root = doc.RootElement(); root != NULL;root = root->NextSiblingElement())
	{
		for (tinyxml2::XMLElement* child = root->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
		{
			Entity* entity = new Entity;
			//std::cout << child->GetText() << std::endl;
			if (strcmp(child->Value(),"name") == 0) 
			{
				entity->AddComponent<NameC>(child->GetText());
			}
			else if (strcmp(child->Value(), "health") == 0)
			{
			}
			else if (strcmp(child->Value(), "energy") == 0)
			{
			}
			else if (strcmp(child->Value(), "damage") == 0)
			{
			}
			else if (strcmp(child->Value(), "sprite") == 0)
			{
			}
		}
	}

}