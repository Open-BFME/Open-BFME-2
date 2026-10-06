// cl: /Ireference/shims/bfme2_ascii /O1 /MD /GX /arch:SSE
// ?Rva003E8535Get@@YG_NPAVParameter@@0@Z @0x003E8535 105B: free stdcall two Parameters team+unit path test.
// Evidence: ret 8 two params; Parameter+0x10 AsciiString by-value plus false to ScriptEngine::getTeamNamed row; null je; Team::rva0039E8EB row null je; Parameter+? to getUnitNamed row null jne; TheAI+0x10 Pathfinder::rva002F477E pin with teamObj UnitObj positions plus 0; caller 0x003EC13F.
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
class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool b);
	Object *getUnitNamed(Parameter *p);
};
extern class ScriptEngine *TheScriptEngine;
class Pathfinder
{
public:
	bool rva002F477E(Object *obj, const Coord3D *from, const Coord3D *to, int v);
};
class AI
{
public:
	char m_pad[0x10];
	Pathfinder *m_pf;
};
extern class AI *TheAI;

bool __stdcall Rva003E8535Get(Parameter *p0, Parameter *p1)
{
	Team *team = TheScriptEngine->getTeamNamed(p0->m_string, false);
	if (!team)
		return false;
	Object *teamObj = team->rva0039E8EB();
	if (!teamObj)
		return false;
	Object *unitObj = TheScriptEngine->getUnitNamed(p1);
	if (!unitObj)
		return false;
	Pathfinder *pf = TheAI->m_pf;
	return pf->rva002F477E(teamObj, &teamObj->m_pos, &unitObj->m_pos, 0);
}
