// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// ?Rva003BD884Set@@YGXPAVParameter@@PBVAsciiString@@@Z @0x003BD884 129B
// (dump range 18). Unit-plus-mask team wiring: resolves the unit through
// rowed ScriptEngine 0x003588E7 getUnitNamed, builds the mask from the name
// through rowed 0x00357475, takes the rowed 0x002A7B91 getPlayerFromMask
// player, bails when unit/player/team is null, then routes the controlling
// player through rowed Object 0x00298AE4 (team), the pinned cdecl 0x003BA83F
// (unit, 0), and, unless rowed testStatus 0x0004E536 bit 0x26 is set, the
// rowed Object 0x00290DBB dual-dict with (controller, player).
#include "ascii_string.h"

class Parameter;
class Team;
struct Rva002A9B58;

enum ObjectID
{
	OBJECTID_NONE = 0
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_0 = 0
};

class Player
{
public:
	unsigned char m_pad[0x2EC];
	Team *m_team; // +0x2EC
};

class Object
{
public:
	Player *getControllingPlayer() const;
	void setTeam(Team *team);
	bool testStatus(ObjectStatusTypes bit) const;
	void rva00290DBB(Rva002A9B58 *a, Rva002A9B58 *b);
};

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *p);
	int rva00357475(const AsciiString &name, bool *matchedSpecialName);
};
extern ScriptEngine *TheScriptEngine;

class PlayerList
{
public:
	Player *getPlayerFromMask(int mask);
};
extern PlayerList *ThePlayerList;

int __cdecl rva003BA83F(void *p, int v);

void __stdcall Rva003BD884Set(Parameter *p1, const AsciiString *name)
{
	Object *obj = TheScriptEngine->getUnitNamed(p1);
	int mask = TheScriptEngine->rva00357475(*name, 0);
	Player *pl = ThePlayerList->getPlayerFromMask(mask);
	if (obj == 0)
		return;
	if (pl == 0)
		return;
	Team *team = pl->m_team;
	if (team == 0)
		return;
	Player *ctrl = obj->getControllingPlayer();
	obj->setTeam(team);
	rva003BA83F(obj, 0);
	if (!obj->testStatus((ObjectStatusTypes)0x26))
		obj->rva00290DBB((Rva002A9B58 *)ctrl, (Rva002A9B58 *)pl);
}
