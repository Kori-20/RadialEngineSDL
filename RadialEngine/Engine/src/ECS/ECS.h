/*This file is not a class
instead it is a collection of functions and 
templates that are used by the ECS system.*/

#pragma once
#include <bitset>
#include <array>
#include "Aid/Logger.h"

class Entity;
class Component;

using ComponentID = std::size_t;

inline ComponentID GetUniqueComponentTypeID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T>// T is a component
inline ComponentID GetComponentTypeID() noexcept
{
	static_assert(std::is_base_of<Component, T>::value, "Not a valid Component");
	static ComponentID typeID = GetUniqueComponentTypeID();
	return typeID;
}

//Defines limit counters
constexpr std::size_t MAX_OBJECTS = 5000;
constexpr std::size_t MAX_COMPONENTS = 60;

//Defines a bitset for each layer
using ComponentBitset = std::bitset<MAX_COMPONENTS>;
//Defines an array of components
using ComponentArray = std::array<Component*, MAX_COMPONENTS>;
