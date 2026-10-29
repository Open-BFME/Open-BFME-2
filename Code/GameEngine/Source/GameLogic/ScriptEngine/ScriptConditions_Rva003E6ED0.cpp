// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
//
// ScriptConditions::rva003E6ED0, retail 0x003E6ED0, 378 bytes (caller
// 0x003EB1F0 in the condition dispatcher 0x003EA9AF). The castle form of
// Zero Hour's evaluateTeamEntered/ExitedArea{Entirely,Partially}: the castle
// is the named unit, or (with no name and a player parameter that resolves
// to no player) the closest KindOf-120 object within 1000000 of the team's
// centre for that (null) player through BFME2's partition filter chain;
// its CastleBehavior module's areas 1..7 (0x00395E53) are tested in turn
// with the team's didPartialEnter / didAllEnter / didPartialExit /
// didAllExit (entered and partially picking), any hit answering true.
#include "ascii_string.h"

class Object;
class Player;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// vftable 0x00BFAD28, allow 0x0026137E, slot 2 0x00261368: +0x08 a
// player, +0x0C whether a hit allows.
class Rva0026137EFilter : public Rva000421C8
{
public:
	Rva0026137EFilter(Player *player, bool match) : m_player(player), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
	bool m_match;
};

// The 224-bit KindOf mask; the (unused, bit) constructor is 0x00045411.
struct Rva00045411BitSet
{
public:
	Rva00045411BitSet(int unused, int bit) throw(); // 0x00045411
	unsigned m_bits[7]; // +0x00
};

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the
// first mask and none of the second.
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08; // +0x08
	BfmeFixedStorage0004543D m_24; // +0x24
};
template <int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc,
		Rva000421C8 *filters);	// 0x00625360
};
extern PartitionManager *ThePartitionManager;

#define REALLY_FAR (100000 * 10.0f)

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class PolygonTrigger;

#include "../../../Include/Common/Module.h"

class CastleBehavior
{
public:
	static NameKeyType rva0003955DA();	// 0x003955DA
};

// 0x00395E53, the castle area trigger for an index (row Rva00395E53Get.cpp).
class Rva00395E53
{
public:
	void *rva00395E53(unsigned int index);
};

class Object
{
	friend class ScriptConditions;
protected:
	Module *findModule(NameKeyType key) const;	// 0x0028B6D6
};

class Team
{
public:
	void rva0039E5B9(Coord3D *center);	// 0x0039E5B9
	bool didPartialEnter(PolygonTrigger *trigger, unsigned int whichToConsider);	// 0x0039E20D
	bool didAllEnter(PolygonTrigger *trigger, unsigned int whichToConsider);	// 0x0039E15D
	bool didPartialExit(PolygonTrigger *trigger, unsigned int whichToConsider);	// 0x0039E288
	bool didAllExit(PolygonTrigger *trigger, unsigned int whichToConsider);	// 0x0039E303
};

class PlayerList
{
public:
	Player *getPlayerFromMask(int mask);	// 0x002A7B91
};
extern PlayerList *ThePlayerList;

class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }
	unsigned char m_beforeInt[8];
	int m_int;
	float m_real;		// +0x0C
	AsciiString m_string;	// +0x10
};

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

class ScriptConditions
{
public:
	bool rva003E6ED0(Parameter *teamParm, const AsciiString *unitName, Parameter *playerParm,
		bool entered, bool partially);
};

bool ScriptConditions::rva003E6ED0(Parameter *teamParm, const AsciiString *unitName, Parameter *playerParm,
	bool entered, bool partially)
{
	Team *team = TheScriptEngine->getTeamNamed(teamParm->getString(), false);
	if (!team)
		return false;
	Object *castle;
	if (unitName) {
		castle = TheScriptEngine->getUnitNamed(*unitName);
	} else {
		if (!playerParm)
			return false;
		Player *player = ThePlayerList->getPlayerFromMask(TheScriptEngine->rva00357475(playerParm->getString(), 0));
		if (player)
			return false;
		Coord3D pos;
		team->rva0039E5B9(&pos);
		castle = ThePartitionManager->getClosestObject(&pos, REALLY_FAR, 0,
			Rva0004584D((const BfmeFixedStorage0004543D &)Rva00045411BitSet(0, 0x78), *(const BfmeFixedStorage0004543D *)&KINDOFMASK_NONE)
				.link(&Rva0026137EFilter(player, true)));
	}
	if (!castle)
		return false;
	CastleBehavior *behavior = (CastleBehavior *)castle->findModule(CastleBehavior::rva0003955DA());
	if (!behavior)
		return false;
	int i = 0;
	do {
		++i;
		PolygonTrigger *area = (PolygonTrigger *)((Rva00395E53 *)behavior)->rva00395E53(i);
		if (!area)
			return false;
		if (entered) {
			if (partially) {
				if (team->didPartialEnter(area, 9))
					return true;
			} else {
				if (team->didAllEnter(area, 9))
					return true;
			}
		} else {
			if (partially) {
				if (team->didPartialExit(area, 9))
					return true;
			} else {
				if (team->didAllExit(area, 9))
					return true;
			}
		}
	} while (i < 7);
	return false;
}
