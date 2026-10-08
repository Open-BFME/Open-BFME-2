// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003E50B4Check@@YG_NPAVParameter@@0@Z
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

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *p);
};
extern ScriptEngine *TheScriptEngine;

struct Waypoint
{
	char m_pad[0x0c];
	Coord3D m_0c;
};

class TerrainLogic
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual Waypoint *getWaypointByName(const void *p);
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
	char m_pad[0x10];
	Pathfinder *m_10;
};
extern AI *TheAI;

bool __stdcall Rva003E50B4Check(Parameter *a, Parameter *b)
{
	Object *o1 = TheScriptEngine->getUnitNamed(a);
	if (!o1)
		return false;
	Waypoint *way = TheTerrainLogic->getWaypointByName((const void *)((const char *)b + 0x10));
	if (!way)
		return false;
	Pathfinder *pf = TheAI->m_10;
	return pf->QuickDoesPathExist(o1, &o1->m_38, &way->m_0c, 0);
}
