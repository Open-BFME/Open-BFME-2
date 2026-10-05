// cl: /Ireference/shims/bfme2_ascii /O1 /MD /GX /arch:SSE
// ?Rva003E84C5Get@@YG_NPAVParameter@@0@Z @0x003E84C5 112B: free stdcall two Parameters team+waypoint path test.
// Evidence: ret 8 two params; Parameter+0x10 AsciiString by-value plus false to ScriptEngine::getTeamNamed row; null je; Team::rva0039E8EB row null je; Parameter+0x10 to TheTerrainLogic slot 0x88 returning Waypoint with Coord3D at +0xc null jne; TheAI+0x10 Pathfinder::rva002F477E pin with teamObj positions plus 0; caller 0x003EC119.
#include "ascii_string.h"
class Parameter
{
public:
	char m_unknown[8];
	int m_int;
	float m_real;
	AsciiString m_string;
};
struct Coord3D
{
	float x;
	float y;
	float z;
};
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
};
extern ScriptEngine *g_Va009FE16C;
class Waypoint
{
public:
	char m_pad[0x0c];
	Coord3D m_location;
};
class TerrainLogic
{
public:
	virtual void _d00(), _d01(), _d02(), _d03(), _d04(), _d05(), _d06();
	virtual void _d07(), _d08(), _d09(), _d10(), _d11(), _d12(), _d13();
	virtual void _d14(), _d15(), _d16(), _d17(), _d18(), _d19(), _d20();
	virtual void _d21(), _d22(), _d23(), _d24(), _d25(), _d26(), _d27();
	virtual void _d28(), _d29(), _d30(), _d31(), _d32(), _d33();
	virtual Waypoint *findWaypoint(const AsciiString &name);
};
extern TerrainLogic *TheTerrainLogic;
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
extern AI *g_Va009FF0F8;

bool __stdcall Rva003E84C5Get(Parameter *p0, Parameter *p1)
{
	Team *team = g_Va009FE16C->getTeamNamed(p0->m_string, false);
	if (!team)
		return false;
	Object *teamObj = team->rva0039E8EB();
	if (!teamObj)
		return false;
	Waypoint *way = TheTerrainLogic->findWaypoint(p1->m_string);
	if (!way)
		return false;
	Pathfinder *pf = g_Va009FF0F8->m_pf;
	return pf->rva002F477E(teamObj, &teamObj->m_pos, &way->m_location, 0);
}
