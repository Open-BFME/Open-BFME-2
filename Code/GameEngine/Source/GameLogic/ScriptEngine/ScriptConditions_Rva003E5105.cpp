// cl: /Ireference/shims/bfme2_ascii
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva003E5105@ScriptConditions@@IAE_NPAVParameter@@0@Z
// retail 0x003E5105 74B leaf free stdcall bool of 2x Parameter ret 8 from 0x003EC0F3. Evidence:
// rowed ScriptEngine::getUnitNamed twice via TheScriptEngine plus pin QuickDoesPathExist via TheAI+0x10
// pathfinder with (object from to 0); Object +0x38 Coord3D; siblings 0x003E4F79 0x003E514F /O1.
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

#include "../../../Include/GameLogic/ScriptConditions.h"

bool ScriptConditions::rva003E5105(Parameter *parameter, Parameter *b)
{
	Object *object = TheScriptEngine->getUnitNamed(parameter);
	if (!object)
		return false;
	Object *o2 = TheScriptEngine->getUnitNamed(b);
	if (!o2)
		return false;
	Pathfinder *pf = TheAI->m_10;
	return pf->QuickDoesPathExist(object, &object->m_38, &o2->m_38, 0);
}
