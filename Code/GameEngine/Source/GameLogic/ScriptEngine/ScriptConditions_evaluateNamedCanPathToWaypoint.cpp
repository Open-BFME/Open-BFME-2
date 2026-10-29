// cl: /Ireference/shims/bfme2_ascii
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?evaluateNamedCanPathToWaypoint@ScriptConditions@@IAE_NPAVParameter@@0@Z
// retail 0x003E50B4 81B leaf free stdcall bool of 2x Parameter ret 8. Evidence:
// rowed ScriptEngine::getUnitNamed via TheScriptEngine plus TerrainLogic slot 0x88
// getWaypointByName via TheTerrainLogic with (Parameter+0x10) plus pin
// QuickDoesPathExist via TheAI+0x10 pathfinder with (object from to 0);
// Object +0x38 Coord3D; Waypoint +0x0c Coord3D; siblings 0x003E4F79 0x003E5105 /O1.
#include "../../../../Libraries/Include/Lib/Coord3D.h"

class Parameter
{
};

class Object
{
public:
	char m_pad[0x38];
	Coord3D m_38;
};

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

class Waypoint
{
public:
	char m_pad[0x0c]; // +0x00
	Coord3D m_0c; // +0x0C
};

class AsciiString;
class TerrainLogic
{
public:
	virtual void _d00();
	virtual void _d01();
	virtual void _d02();
	virtual void _d03();
	virtual void _d04();
	virtual void _d05();
	virtual void _d06();
	virtual void _d07();
	virtual void _d08();
	virtual void _d09();
	virtual void _d10();
	virtual void _d11();
	virtual void _d12();
	virtual void _d13();
	virtual void _d14();
	virtual void _d15();
	virtual void _d16();
	virtual void _d17();
	virtual void _d18();
	virtual void _d19();
	virtual void _d20();
	virtual void _d21();
	virtual void _d22();
	virtual void _d23();
	virtual void _d24();
	virtual void _d25();
	virtual void _d26();
	virtual void _d27();
	virtual void _d28();
	virtual void _d29();
	virtual void _d30();
	virtual void _d31();
	virtual void _d32();
	virtual void _d33();
	virtual Waypoint *getWaypointByName(const AsciiString &name);
};
extern TerrainLogic *TheTerrainLogic;

class Pathfinder
{
public:
	bool QuickDoesPathExist(Object *obj, const Coord3D *from, const Coord3D *to, int x);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_10; }
	char m_pad[0x10]; // +0x00
	Pathfinder *m_10; // +0x10
};
extern AI *TheAI;

class ScriptConditions
{
protected:
	bool evaluateNamedCanPathToWaypoint(Parameter *a, Parameter *b);
};

bool ScriptConditions::evaluateNamedCanPathToWaypoint(Parameter *parameter, Parameter *b)
{
	Object *object = TheScriptEngine->getUnitNamed(parameter);
	if (!object)
		return false;
	Waypoint *way = TheTerrainLogic->getWaypointByName(*(const AsciiString *)((const char *)b + 0x10));
	if (!way)
		return false;
	Pathfinder *pf = TheAI->m_10;
	return pf->QuickDoesPathExist(object, &object->m_38, &way->m_0c, 0);
}
