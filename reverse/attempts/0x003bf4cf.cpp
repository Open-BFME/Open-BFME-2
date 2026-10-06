// ?Rva003BF4CFD0@@YGXPBVAsciiString@@0_N1@Z
// partial score=0.97 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /DNDEBUG /MD /arch:SSE
//
// ?Rva003BF4CFD0@@YGXPBVAsciiString@@0_N1@Z @0x003BF4CF 303B (dump range 18).
// Team centroid waypoint dispatch, sibling of banked 0x003BF39F: the zero
// in ESI serves both the lookup flag and the member count (single xor),
// team in EDI, group in EBX, do/if member loop over Object+0x38 positions,
// 1.0f/count average through shared g_Va00BBB8D8, TerrainLogic v36 slot,
// then one of three waypoint calls by two flags. Mirrors landed 0x003BF045
// idioms; flag/global identities unproven.
#include "ascii_string.h"

struct Coord3D
{
	float x;
	float y;
	float z;
};

template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];
public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class Waypoint;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class Object
{
public:
	char m_pad00[0x38];
	Coord3D m_position;
};

class AIGroup;
class Rva0036FAF8;

class Team
{
public:
	void getTeamAsAIGroup(AIGroup *group);
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool exact);
};
extern ScriptEngine *TheScriptEngine;

class AI
{
public:
	AIGroup *createGroup();
};
extern AI *TheAI;

class AIGroup
{
public:
	void rva0036F9FE(const Waypoint *wp, CommandSourceType src, int mode);
	void rva0036FB57(const Waypoint *wp, CommandSourceType src, int mode);
};

class Rva0036FAF8
{
public:
	void rva0036FAF8(const Waypoint *wp, CommandSourceType src, int mode);
};

class TerrainLogic
{
public:
	virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
	virtual void d04(); virtual void d05(); virtual void d06(); virtual void d07();
	virtual void d08(); virtual void d09(); virtual void d10(); virtual void d11();
	virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
	virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
	virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
	virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
	virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
	virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35();
	virtual Waypoint *v36(const Coord3D *pos, const AsciiString *name);
};
extern TerrainLogic *TheTerrainLogic;

extern float g_Va00BBB8D8;

void __stdcall Rva003BF4CFD0(const AsciiString *teamName, const AsciiString *extraName, bool flag10, bool flag14)
{
	int count = 0;
	Team *team = TheScriptEngine->getTeamNamed(*teamName, false);
	if (team == 0)
		return;
	AIGroup *group = TheAI->createGroup();
	if (group == 0)
		return;
	team->getTeamAsAIGroup(group);
	DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
	Coord3D sum;
	sum.z = 0.0f;
	sum.y = 0.0f;
	sum.x = 0.0f;
	Object *cur = iter.cur();
	if (cur == 0)
		return;
	do {
		float x = cur->m_position.x;
		float y = cur->m_position.y;
		float z = cur->m_position.z;
		sum.x += x;
		sum.y += y;
		sum.z += z;
		++count;
		iter.advance();
		cur = iter.cur();
	} while (cur != 0);
	if (count == 0)
		return;
	float inv = g_Va00BBB8D8 / (float)count;
	sum.x *= inv;
	sum.y *= inv;
	sum.z *= inv;
	Waypoint *wp = TheTerrainLogic->v36(&sum, extraName);
	if (wp == 0)
		return;
	if (flag14 != 0)
		group->rva0036FB57(wp, CMD_FROM_SCRIPT, 0);
	else if (flag10 != 0)
		((Rva0036FAF8 *)group)->rva0036FAF8(wp, CMD_FROM_SCRIPT, 0);
	else
		group->rva0036F9FE(wp, CMD_FROM_SCRIPT, 0);
}
