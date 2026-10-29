// cl: /Ireference/shims/bfme2_ascii /MD /GX
// ?evaluateTeamCanPathToWaypoint@ScriptConditions@@IAE_NPAVParameter@@0@Z @0x003E84C5 112B: free stdcall two Parameters team+waypoint path test.
// Evidence: ret 8 two params; Parameter+0x10 AsciiString by-value plus false to ScriptEngine::getTeamNamed row; null je; Team::rva0039E8EB row null je; Parameter+0x10 to TheTerrainLogic slot 0x88 returning Waypoint with Coord3D at +0xc null jne; TheAI+0x10 Pathfinder::QuickDoesPathExist pin with teamObj positions plus 0; caller 0x003EC119.
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
class Waypoint
{
public:
	char m_pad[0x0c]; // +0x00
	Coord3D m_0c; // +0x0C
};
class TerrainLogic
{
public:
	virtual void _d00(), _d01(), _d02(), _d03(), _d04(), _d05(), _d06();
	virtual void _d07(), _d08(), _d09(), _d10(), _d11(), _d12(), _d13();
	virtual void _d14(), _d15(), _d16(), _d17(), _d18(), _d19(), _d20();
	virtual void _d21(), _d22(), _d23(), _d24(), _d25(), _d26(), _d27();
	virtual void _d28(), _d29(), _d30(), _d31(), _d32(), _d33();
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
	bool evaluateTeamCanPathToWaypoint(Parameter *p0, Parameter *p1);
};

bool ScriptConditions::evaluateTeamCanPathToWaypoint(Parameter *parameter, Parameter *p1)
{
	Team *team = TheScriptEngine->getTeamNamed(parameter->m_string, false);
	if (!team)
		return false;
	Object *teamObj = team->rva0039E8EB();
	if (!teamObj)
		return false;
	Waypoint *way = TheTerrainLogic->getWaypointByName(p1->m_string);
	if (!way)
		return false;
	Pathfinder *pf = TheAI->m_10;
	return pf->QuickDoesPathExist(teamObj, &teamObj->m_pos, &way->m_0c, 0);
}
