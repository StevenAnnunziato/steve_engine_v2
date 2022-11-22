#include <fstream>
#include <sstream>
#include <string>

#include "LevelParser.h"
#include "Entity.h"
#include "Game.h"
#include "Utils.h"

LevelParser::LevelParser()
{
	// On startup, init the component creation function map
	registerCompFns();
}

void LevelParser::LoadLevel(EngineState* engine)
{
	std::ifstream inStream("level01.dat");

	if (!inStream.good())
	{
		std::cout << "Failed to load level01.dat." << std::endl;
		engine->system->ShowError(ERROR_LOAD_FILE);
		return;
	}

	// for each line in the file...
	// (one line is one Entity)
	while (!inStream.eof()) {
		std::string input;
		getline(inStream, input);
		
		// create the stringstream
		std::stringstream line(input);

		// create the entity
		Entity* ent = Game::getInstance()->createNewEntity();
		
		// for each component in the line...
		while (!line.eof())
		{
			// read the int component ID value
			int compID;
			line >> compID;

			// let this component load its data
			addAndLoadComponent(ent, (ComponentID)compID, line);
		}
	}
}

// Set up the map with the correct functions.
// note: functions pointed to must be static.
void LevelParser::registerCompFns()
{
	compCreationMap[ComponentID::Transform] = initTransform;
	compCreationMap[ComponentID::RectRenderer] = createRectRenderer;
	compCreationMap[ComponentID::RectCollider] = createRectCollider;
	compCreationMap[ComponentID::PlayerController] = createPlayerController;
	compCreationMap[ComponentID::ColliderColorChanger] = createColliderColorChanger;
}

void LevelParser::addAndLoadComponent(Entity* ent, ComponentID compID, std::istream& file)
{
	// is this an invalid component index?
	if ((int)compID <= 0 || (int)compID >= (int)ComponentID::NUM_IDS)
	{
		std::cout << "Error: read an invalid component ID while reading level data from disc." << std::endl;
	}

	Component* comp = compCreationMap[compID](ent);
	comp->LoadFromFile(file);
}

// methods for creating / initializing new components on an entity
// Note that we don't need to pass it any data yet, this will happen with LoadFromFile
// on a per-component basis
Component* LevelParser::initTransform(Entity* ent)
{
	// do nothing with the transform component for now
	return ent->GetTransform();
}

Component* LevelParser::createRectRenderer(Entity* ent)
{
	return ent->CreateRenderer(Vector2(0, 0), Color(0, 0, 0));
}

Component* LevelParser::createRectCollider(Entity* ent)
{
	return ent->CreateCollider(0, 0);
}

Component* LevelParser::createPlayerController(Entity* ent)
{
	return ent->CreatePlayerController();
}

Component* LevelParser::createColliderColorChanger(Entity* ent)
{
	return ent->CreateColliderColorChanger(Color(0, 0, 0));
}
