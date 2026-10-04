// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ScriptActions::doTeamCaptureNearestUnownedFactionUnit, retail 0x003C1D70,
// 249 bytes (called from the action dispatcher 0x003CA4BE at 0x003CD45F).
// Zero Hour's body over BFME2's partition filter chain: the team's group
// enters the object closest to its centre that is an enemy or neutral of the
// team's controlling player (relationship flags 0xC), unmanned, and on the
// map. BFME2 links the three filters (built in reverse) instead of Zero
// Hour's array and measures from the 3D centre. Callees: getTeamNamed
// 0x003584E9, createGroup 0x002FEC4B, getTeamAsAIGroup 0x003A0F62,
// getCenter 0x0036D035, Team::getControllingPlayer 0x0039D7CF, groupEnter
// 0x00370198.
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after allow (slot 1), the ctors being inline.
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

// vftable 0x00C004D8, allow 0x00261409: the player's relationship to the
// object's team against the +0x10 flags (ZH's PartitionFilterRelationship
// analogue), +0x0C whether a hit allows.
class Rva00261409Filter : public Rva000421C8
{
public:
	Rva00261409Filter(Player *player, bool match, int flags)
		: m_player(player), m_match(match), m_flags(flags) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
	bool m_match;
	int m_flags;
};

// The base filter's slot 2 is the trivial virtual retail shares across many
// vftable slots (0x0036CC7A); bind the declaration to that row.
#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

// vftable 0x00BFAD1C, allow 0x002611DD: no members of its own (Zero Hour's
// PartitionFilterOnMap in this caller).
class Rva002611DDFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00C1FE28, allow 0x00261C58: +0x08 a flag (Zero Hour's
// PartitionFilterUnmannedObject in this caller).
class Rva00261C58Filter : public Rva000421C8
{
public:
	Rva00261C58Filter(bool match) : m_match(match) {}
	virtual bool allow(Object *obj);
	bool m_match;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum CommandSourceType
{
	CMD_FROM_SCRIPT = 1
};

enum DistanceCalculationType
{
	FROM_CENTER_3D = 0
};

class Team
{
public:
	Player *getControllingPlayer() const;	// 0x0039D7CF
	void getTeamAsAIGroup(class AIGroup *group);	// 0x003A0F62
};

class AIGroup
{
public:
	bool getCenter(Coord3D *center);	// 0x0036D035
	void groupEnter(Object *obj, CommandSourceType source);	// 0x00370198
};

class AI
{
public:
	AIGroup *createGroup();	// 0x002FEC4B
};
extern AI *TheAI;

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool flag);	// 0x003584E9
};
extern ScriptEngine *TheScriptEngine;

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc,
		Rva000421C8 *filters);	// 0x00625360
};
extern PartitionManager *ThePartitionManager;

#define REALLY_FAR (100000 * 10.0f)

class ScriptActions
{
protected:
	void doTeamCaptureNearestUnownedFactionUnit(const AsciiString &teamName);
};

void ScriptActions::doTeamCaptureNearestUnownedFactionUnit(const AsciiString &teamName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;

	AIGroup *theGroup = TheAI->createGroup();
	team->getTeamAsAIGroup(theGroup);

	Coord3D pos;
	theGroup->getCenter(&pos);

	Object *obj = ThePartitionManager->getClosestObject(&pos, REALLY_FAR, FROM_CENTER_3D,
		Rva00261409Filter(team->getControllingPlayer(), true, 0xC)
			.link(Rva00261C58Filter(true).link(&Rva002611DDFilter())));
	if (!obj)
		return;

	theGroup->groupEnter(obj, CMD_FROM_SCRIPT);
}
