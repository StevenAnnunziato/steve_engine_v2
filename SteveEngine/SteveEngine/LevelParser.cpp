#include "LevelParser.h"
#include "Entity.h"

// note: functions pointed to must be static
void LevelParser::registerCompFns()
{
	compCreationMap[2] = CreateRectRenderer;
}

void LevelParser::CreateRectRenderer(Entity* ent)
{
	//ent->CreateRenderer(size, color);
}
