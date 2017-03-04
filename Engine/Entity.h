#ifndef _ENTITY_
#define _ENTITY_
#pragma once

#include <SFML\Graphics.hpp>
#include <memory>
#include <map>
#include <typeinfo>
#include <typeindex>

struct Component
{
	Component() {}
	virtual ~Component() {}
};



class Entity
{
	std::map<std::type_index, std::shared_ptr<Component>> Components;
public:
	
	Entity() {};
	~Entity()
	{
		Components.clear();
	};

	template<typename T, typename ...Args>
	void AddComponent(Args... args)
	{
		std::type_index tid = std::type_index(typeid(T));
		if (Components[tid] == nullptr) {
			Components[tid] = std::make_shared<T>(args...);
		}
	}
	template<typename T>
	std::shared_ptr<T> GetComponent()
	{
		std::type_index tid = std::type_index(typeid(T));
		return std::dynamic_pointer_cast<T>(Components[tid]);
	}
	

};

#endif // !_ENTITY_

