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
	~Component() {}
};



class Entity
{
	std::map<std::type_index, std::shared_ptr<Component>> Components;
public:
	virtual void Update() = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;
	Entity() {};
	~Entity() {};

private:
	template<typename T>
	std::shared_ptr<T> GetComponent()
	{
		std::type_index index(typeid(T));
		if (Components.count(std::type_index(typeid(T))) != 0) return static_pointer_cast<T>(Components[index]);
		else return nullptr;
	}
	template<typename T>
	void AddComponent(T *t)
	{
		Components[std::type_index(typeid(*T))] = t;
	}

};

#endif // !_ENTITY_

