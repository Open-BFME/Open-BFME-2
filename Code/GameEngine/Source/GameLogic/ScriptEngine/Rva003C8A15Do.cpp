// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -GX -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
//
// ?Rva003C8A15Do@ScriptActions@@QAEXPAVParameter@@ABVAsciiString@@1@Z @0x003C8A15 (128B).
// Unit guard in trigger area via getQualifiedTriggerAreaByName plus
// getUnitNamed plus waypoint 0x88 plus aiGuardAreaFromPosition else aiGuardArea.
// Evidence: callees rowed 0x0035768D 0x003588E7, caller 0x003CB6CD 0x003CB708.
// Precedent Rva003C8B62Do Rva003C87F1Do.
#include "ascii_string.h"

#include "../../../../Libraries/Include/Lib/Coord3D.h"
class Parameter;
class Object;
class Waypoint;
class PolygonTrigger;
enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

#include "../../../Include/GameLogic/ScriptEngine.h"

class TerrainLogicByValue
{
public:
	virtual void _0()=0; virtual void _1()=0; virtual void _2()=0; virtual void _3()=0;
	virtual void _4()=0; virtual void _5()=0; virtual void _6()=0; virtual void _7()=0;
	virtual void _8()=0; virtual void _9()=0; virtual void _10()=0; virtual void _11()=0;
	virtual void _12()=0; virtual void _13()=0; virtual void _14()=0; virtual void _15()=0;
	virtual void _16()=0; virtual void _17()=0; virtual void _18()=0; virtual void _19()=0;
	virtual void _20()=0; virtual void _21()=0; virtual void _22()=0; virtual void _23()=0;
	virtual void _24()=0; virtual void _25()=0; virtual void _26()=0; virtual void _27()=0;
	virtual void _28()=0; virtual void _29()=0; virtual void _30()=0;
	virtual void _31()=0; virtual void _32()=0; virtual void _33()=0;
	virtual Waypoint *getWaypointByName(const AsciiString &name) = 0;
};

class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;

#include "../../../Include/GameLogic/Module/AIUpdate.h"

#include "../Object/object.h"

#include "../../../Include/GameLogic/Waypoint.h"

extern class ScriptEngine *TheScriptEngine;

void ScriptActions::Rva003C8A15Do(Parameter *unitParam, const AsciiString &areaName, const AsciiString &wayName)
{
	PolygonTrigger *area = TheScriptEngine->getQualifiedTriggerAreaByName(areaName);
	Object *obj = TheScriptEngine->getUnitNamed(unitParam);
	if (!obj)
		return;
	if (!obj->getAI())
		return;
	if (!area)
		return;
	Waypoint *wp = ((TerrainLogicByValue *&)TheTerrainLogic)->getWaypointByName(wayName);
	AIUpdateInterface *ai = obj->getAI();
	if (wp)
		ai->aiGuardAreaFromPosition(area, 0, CMD_FROM_SCRIPT, wp->getLocation());
	else
		ai->aiGuardArea(area, 0, CMD_FROM_SCRIPT);
}
