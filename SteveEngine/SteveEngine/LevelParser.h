#pragma once

#include <unordered_map>

class Entity;

class LevelParser
{
public:
	// function pointer, takes an Entity* and returns void
	typedef void (*compFn)(Entity* ent);
	
	void registerCompFns();

	// functions for creating components which will be pointed to in the map.
	static void CreateRectRenderer(Entity* ent);

private:
	// map ints (component IDs) to function pointers
	std::unordered_map<int, compFn> compCreationMap;


};

