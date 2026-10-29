// cl: /Ireference/shims/bfme2_ascii /MD /GX
// ?evaluateTeamCanPathToNamed@ScriptConditions@@IAE_NPAVParameter@@0@Z @0x003E8535 105B: free stdcall two Parameters team+unit path test.
// Evidence: ret 8 two params; Parameter+0x10 AsciiString by-value plus false to ScriptEngine::getTeamNamed row; null je; Team::rva0039E8EB row null je; Parameter+? to getUnitNamed row null jne; TheAI+0x10 Pathfinder::QuickDoesPathExist pin with teamObj UnitObj positions plus 0; caller 0x003EC13F.
#include "ascii_string.h"
class Parameter
{
public:
	char m_unknown[8];
	int m_int;
	float m_real;
	AsciiString m_string;
};
#include "../../../../Libraries/Include/Lib/Coord3D.h"
class Object
{
public:
	char m_pad[0x38];
	Coord3D m_pos;
};
class Team
{
public:
	Object *rva0039E8EB();
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

class ScriptConditions
{
protected:
	bool evaluateTeamCanPathToNamed(Parameter *p0, Parameter *p1);
};

bool ScriptConditions::evaluateTeamCanPathToNamed(Parameter *parameter, Parameter *p1)
{
	Team *team = TheScriptEngine->getTeamNamed(parameter->m_string, false);
	if (!team)
		return false;
	Object *teamObj = team->rva0039E8EB();
	if (!teamObj)
		return false;
	Object *unitObj = TheScriptEngine->getUnitNamed(p1);
	if (!unitObj)
		return false;
	Pathfinder *pf = TheAI->m_10;
	return pf->QuickDoesPathExist(teamObj, &teamObj->m_pos, &unitObj->m_pos, 0);
}
