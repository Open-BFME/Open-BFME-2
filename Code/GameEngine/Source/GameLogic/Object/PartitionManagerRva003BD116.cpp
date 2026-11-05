// stlport
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
#include "GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BD116Set@ScriptActions@@QAEXPAVParameter@@PAX@Z retail 0x003BD116 61 bytes.
// Teleport-like set: obj = g_Va009FE16C->getUnitNamed(p1); pos = TheTerrainLogic slot 0x88(p2); if pos then obj->rva0029660C(pos+0xC, 0). Evidence: callees rowed 0x003588E7 pin 0x0029660C; caller 0x003CE7AC; neighbours Rva003BD0C8 prev Rva003BD153 next same /O1.
class Parameter;
class Object;
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "object.h"
#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;
#include "../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;

void ScriptActions::Rva003BD116Set(Parameter *parameter, void *p2)
{
	Object *obj = TheScriptEngine->getUnitNamed(parameter);
	if (obj == 0)
		return;
	void *base = TheTerrainLogic->getWaypointByName(*(const AsciiString *)p2);
	if (base == 0)
		return;
	obj->teleportTo((const Coord3D *)((const char *)base + 0xC), false);
}

// Member ABI proved at each native executeAction3CA4BE call site: ECX=this.
// Canonical ScriptActions owner; address-derived verbs remain uncertain.
