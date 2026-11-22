// cl: /MD /GX /Ireference/shims/bfme2_ascii
//
// AISpellBookShroudReveal.cpp (the unit retail's random-range asserts name,
// 0x00C75EF0).
//
//   0x005D7FA6  AoE target picker slot: once the game frame passes
//               g_00E06648, pick one of the picker's waypoint IDs at random
//               and, when that waypoint is still shrouded for the caster
//               and an alive object allied (flags 4) to the caster stands
//               within 300 of it, offer the waypoint pushed 30..180 along
//               a random direction (0x005EE317) to 0x005EE8DD
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents).

#include "ascii_string.h"

class Object;
class Player;

#include "../../../../../Include/GameLogic/PartitionFilter.h"

// vftable 0x00C004D8, allow 0x00261409: the player's relationship to the
// object's team against the +0x10 flags, +0x0C whether a hit allows.
#include "../../../../../Include/GameLogic/Rva00261409Filter.h"

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
#include "../../../../../Include/GameLogic/Rva0026119DFilter.h"


// Coord3D: shared header/view; no private copy.
#include "../../../../../../Libraries/Include/Lib/Coord3DInline.h"

#include "../../../../../Include/Common/Player.h"

#include "../../../Object/object.h"

#include "../../../../../Include/GameLogic/Waypoint.h"

#include "../../../../../Include/GameLogic/TerrainLogic.h"

#include "../../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

enum CellShroudStatus
{
	CELLSHROUD_CLEAR = 0
};

#include "../../../../Common/PartitionRangeQueryCallView.h"

extern PartitionManager *ThePartitionManager;
extern PartitionManager *TheShroudManager;

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);
float GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);

// g_00E06648: the frame this unit's picker waits for; only 0x005D7FA6 reads
// it (zero-filled .bss). Retail builds it at startup with this unit's
// .text$yc initializer 0x007B4BC6, the only entry of its run (LINK-236).
extern int BfmeLogicFramesPerSecond;
unsigned int g_00E06648 = BfmeLogicFramesPerSecond * 10;

// The waypoint IDs at picker +0x28: a count, then the IDs.
struct Rva005D7FA6Waypoints
{
	int m_count;
	int m_ids[1];
};

// The AoE special-power target picker (AISPecialPowerTargetAoE.cpp holds
// 0x005EE317 and 0x005EE8DD).
#include "../../../../../Include/Common/Rva005EE816.h"

// Slot 6 of vftable 0x00C75ED0, the shouldActivate slot of the sibling
// AISpellBook powers; its asserts name this unit (lines 57 and 73).
class AISpellBookShroudReveal
{
public:
	virtual bool shouldActivate(Object *source);
private:
	char m_pad04[0x28 - 0x04];
	Rva005D7FA6Waypoints m_waypoints;	// +0x28
};

bool AISpellBookShroudReveal::shouldActivate(Object *source)
{
	if (TheGameLogic->getFrame() > g_00E06648) {
		int index = GetGameLogicRandomValue(0, m_waypoints.m_count - 1, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AISpecialPowers\\AISpellBookPowers\\AISpellBookShroudReveal.cpp", 57);
		Waypoint *wp = TheTerrainLogic->getWaypointByID(m_waypoints.m_ids[index]);
		if (TheShroudManager->getShroudStatusForPlayer(source->getControllingPlayer()->getPlayerIndex(), wp->getLocation()) != CELLSHROUD_CLEAR) {
			BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(wp->getLocation(), 300.0f, 0,
				Rva0026119DFilter().link(&Rva00261409Filter(source->getControllingPlayer(), true, 4)), 0);
			if (hits.next()) {
				Coord3D target;
				target.set(wp->getLocation());
				Coord3D dir;
				((Rva005EE816 *)this)->rva005EE317(&dir);
				dir.scaleInlined(GetGameLogicRandomValueReal(30.0f, 180.0f, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AISpecialPowers\\AISpellBookPowers\\AISpellBookShroudReveal.cpp", 73));
				target.add(&dir);
				return ((Rva005EE816 *)this)->rva005EE8DD(&target, source);
			}
		}
	}
	return false;
}

// Native RVA 0x005D7E45..0x005D7E98, 83B; the preceding destructor ends
// exactly at this entry. The clean inline lookup in the verified initializer
// Rva005D7E98WaypointStarts.cpp is the C++ guide. Retail independently proves
// the first-waypoint slot 33, name +8, next +0x1C and by-value key cleanup.
// The original standalone function name remains unproved.
Waypoint *findWaypointByName(AsciiString key)
{
	Waypoint *waypoint = TheTerrainLogic->getFirstWaypoint();
	for (; waypoint; waypoint = waypoint->m_pNext)
		if (((const StringBase<char> &)waypoint->m_name).compare(*(const StringBase<char> *)&key) == 0) break;
	return waypoint;
}
