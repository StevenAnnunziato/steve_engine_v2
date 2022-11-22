#pragma once

#include <unordered_map>
#include <string>
#include <iostream>

#include "Component.h"

class Entity;
class EngineState;

class LevelParser
{
public:
	LevelParser();

	// function pointer, takes an Entity* and returns a Component*
	typedef Component* (*compFn)(Entity* ent);
	
	void LoadLevel(EngineState* engine);

	void registerCompFns();
	void addAndLoadComponent(Entity* ent, ComponentID compID, std::istream& file);

	// functions for creating components which will be pointed to in the map.
	static Component* initTransform(Entity* ent);
	static Component* createRectRenderer(Entity* ent);
	static Component* createRectCollider(Entity* ent);
	static Component* createPlayerController(Entity* ent);
	static Component* createColliderColorChanger(Entity* ent);

private:
	// map ints (component IDs) to function pointers to creation functions
	std::unordered_map<ComponentID, compFn> compCreationMap;


};

