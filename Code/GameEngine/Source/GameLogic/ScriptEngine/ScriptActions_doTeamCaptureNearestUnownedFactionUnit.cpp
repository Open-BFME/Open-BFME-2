// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
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

#include "../../../Include/GameLogic/PartitionFilter.h"

// vftable 0x00C004D8, allow 0x00261409: the player's relationship to the
// object's team against the +0x10 flags (ZH's PartitionFilterRelationship
// analogue), +0x0C whether a hit allows.
#include "../../../Include/GameLogic/Rva00261409Filter.h"

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

#include "../../../../Libraries/Include/Lib/Coord3D.h"

enum CommandSourceType
{
	CMD_FROM_SCRIPT = 1
};

enum DistanceCalculationType
{
	FROM_CENTER_3D = 0
};

#include "../../../Include/Common/TeamBFME2.h"

#include "../../../Include/GameLogic/AIGroup.h"

#include "../../../Include/GameLogic/AI.h"
extern AI *TheAI;

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

#include "../../Common/PartitionRangeQueryCallView.h"
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
