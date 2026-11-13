// cl: /Ireference/shims/bfme2_ascii
//
// ?doNamedBuildStructureAtWaypoint@ScriptActions@@IAEXPAVParameter@@ABVAsciiString@@M1@Z @0x003BC123 125B: script action with waypoint and lookup.
// Evidence: getUnitNamed 0x003588E7 with Parameter then TerrainLogic slot 0x88 getWaypointByName with 4th arg then ThingFactory 0x002D06CA with 2nd arg then AIUpdate at Object+0x258 slot 0x1F8 with Player from getControllingPlayer plus float plus coords; globals g_Va009FE16C TheTerrainLogic g_009FF000; ret 16.

#include "ascii_string.h"

class Parameter;
class Object;
class Player;
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Include/GameLogic/Waypoint.h"

#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;

#include "../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;

class ThingTemplate;
#include "../../../Include/Common/ThingFactory.h"
extern class ThingFactory *TheThingFactory;

#include "../../../Include/GameLogic/Module/AIUpdate.h"

#include "../Object/object.h"

class ScriptActions
{
protected:
	void doNamedBuildStructureAtWaypoint(Parameter *param, const AsciiString &arg2, float f, const AsciiString &wayName);
};

void ScriptActions::doNamedBuildStructureAtWaypoint(Parameter *param, const AsciiString &asciiString, float f, const AsciiString &wayName)
{
	Object *obj = TheScriptEngine->getUnitNamed(param);
	Waypoint *way = TheTerrainLogic->getWaypointByName(wayName);
	const ThingTemplate *lookup = TheThingFactory->findTemplate(asciiString);
	if (!obj || !way || !lookup)
		return;
	AIUpdateInterface *ai = obj->getAI();
	ai->construct(lookup, way->getLocation(), f, obj->getControllingPlayer(), false, 0);
}
