// cl: /MD
// Dump lane range 13: ?FindBrokenBridge @0x002E99F9 211B. Two-position cell
// resolution (TerrainLogic layers, then Pathfinder cells) feeding the
// union-find subobject at +0x460 through the pinned 0x0053241F/0x00531FD4
// thunks. Param a2 is overwritten with a ushort result (dead after the
// ret 0xc pop); the function returns 0. Identities unproven.
#include "../../../../Libraries/Include/Lib/Coord3D.h"
class Object;
enum PathfindLayerEnum
{
	PATHFIND_LAYER_GROUND = 0
};
#include "../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;
#include "../../../Include/GameLogic/PathfindCell.h"
class Rva005310E3
{
public:
	int rva005310E3();
private:
	char m_lead[4];
	unsigned char m_4;
	unsigned char m_5;
	char m_pad[2];
	int m_8;
};
struct PathfindZoneParams;
// WB12D2AB0/12D2C50 and native531757/5317D7 establish predicate owners.
#include "../../../Include/GameLogic/PathfindZoneManager.h"
#include "../../../Include/GameLogic/Rva002E99F9Sub460.h"
struct Rva002E99F9Arg1
{
	char m_pad0[0x10];
	int m_validLocomotorSurfaces;
	char m_pad14;
	unsigned char m_15;
};
struct Rva002E99F9Query
{
	int m_acceptableSurfaces;
	unsigned char m_4;
	unsigned char m_5;
	char m_pad6[2];
	int m_8;
	unsigned char m_C;
};
class Pathfinder
{
public:
	PathfindCell *rva002E8BF8(PathfindLayerEnum layer, const Coord3D *pos);
	int FindBrokenBridge(Rva002E99F9Arg1 *locoSet, const Coord3D * volatile startPos, const Coord3D *endPos);
private:
	char m_pad0[0x460];
	Rva002E99F9Sub460 m_sub460;
};
// ?FindBrokenBridge@Pathfinder@@QAEHPAURva002E99F9Arg1@@RBUCoord3D@@PBU3@@Z
// @0x002E99F9 211B. a2 is top-level volatile: retail observably writes the
// dead param slot (mov [ebp+0xc]) after the fifth sub-call, and the
// qualifier keeps that store. Flags /O1 /MD /G7: /G7 lowers the ushort
// cell-field loads as plain 16-bit mov (no movzx) like the rowed
// Rva00531A44 find in the same family.
int Pathfinder::FindBrokenBridge(Rva002E99F9Arg1 *locoSet, const Coord3D * volatile startPos, const Coord3D *endPos)
{
	PathfindLayerEnum endLayer = TheTerrainLogic->getLayerForDestination(0, endPos);
	PathfindLayerEnum startLayer = TheTerrainLogic->getLayerForDestination(0, startPos);
	PathfindCell *pathfindCell = rva002E8BF8(startLayer, startPos);
	PathfindCell *m_endCell = rva002E8BF8(endLayer, endPos);
	Rva002E99F9Query zoneParams;
	zoneParams.m_8 |= -1;
	zoneParams.m_acceptableSurfaces = locoSet->m_validLocomotorSurfaces;
	zoneParams.m_C = locoSet->m_15;
	zoneParams.m_4 = 0;
	zoneParams.m_5 = 0;
	unsigned short wB;
	unsigned short wA;
	wB = pathfindCell->getZone();
	unsigned int startZone = m_sub460.rva0053241F(&zoneParams, wB);
	wA = m_endCell->getZone();
	unsigned int endZone = m_sub460.rva0053241F(&zoneParams, wA);
	unsigned int startZoneRoot = m_sub460.rva00531FD4(&zoneParams, startZone);
	unsigned int endZoneRoot = m_sub460.rva00531FD4(&zoneParams, endZone);
	unsigned int r5 = m_sub460.rva0053241F(&zoneParams, startZoneRoot);
	startPos = (const Coord3D *)r5;
	m_sub460.rva0053241F(&zoneParams, endZoneRoot);
	return 0;
}

// ?rva00531FE6@Rva002E99F9Sub460@@QAEG_NPAXG@Z @0x00531FE6 91B
// Target evidence: item bit 3 returns 1; rowed 0x005310E3 supplies a signed count; the
// GetCollapseIndex (0x0053123A) lookup maps negative -1 to 1 and other negative values to 0;
// nonnegative indexes select an Rva00531A44 slot ending in rowed 0x00531B20.
// Structural inference: the class relation to Rva002E99F9Sub460 is supported by thunk
// 0x0053241F which forwards (true, item, value) to this body; item identity remains unknown.
unsigned short Rva002E99F9Sub460::rva00531FE6(bool force, void *item, unsigned short value)
{
	if (*((unsigned char *)item) & 0x08)
		return 1;

	int count = ((Rva005310E3 *)item)->rva005310E3();
	if (force)
		++count;
	int index = PathfindZoneManager::GetCollapseIndex(*(const PathfindZoneParams *)item);
	if (index < 0)
		return index == -1;

	unsigned int slot = count * 7 + index + 0x15E1;
	Rva00531A44 *entry = (Rva00531A44 *)((char *)this + slot * 0x14);
	return entry->rva00531B20(value);
}

// ?rva0053241F@Rva002E99F9Sub460@@QAEGPAXG@Z @0x0053241F 18B
// Forwarder pushing (true, s, w) to rowed 0x00531FE6 ret 8. Evidence: pin
// ?rva0053241F@Rva002E99F9Sub460@@QAEGPAXG@Z; callers in FindBrokenBridge
// 0x002E9A6C 0x002E9A7F 0x002E9AAC 0x002E9ABE plus 0x002E7C4E; sibling
// 0x00531FD4 forwards false. noinline keeps FindBrokenBridge calling the
// thunk as retail does instead of inlining the push-1.
__declspec(noinline) unsigned short Rva002E99F9Sub460::rva0053241F(void *s, unsigned short w)
{
	return rva00531FE6(true, s, w);
}

// ?rva005318DB@Rva002E99F9Sub460@@QAE_NPAX00@Z @0x005318DB 157B. The item
// bit 3 returns true; otherwise rowed 0x005310E3 supplies a count and the
// GetCollapseIndex (0x0053123A) supplies an index. Two input records each
// contribute their word at +8 to the two rowed 0x00531720 checks, then the
// WB-proven CouldBeInEquivSet531757 and InEquivSet5317D7 checks. The receiver
// association with Rva002E99F9Sub460 is structural; item and record types
// remain unknown.
bool Rva002E99F9Sub460::rva005318DB(void *item, void *first, void *second)
{
	if (*((unsigned char *)item) & 0x08)
		return true;

	unsigned int count = ((Rva005310E3 *)item)->rva005310E3();
	int index = PathfindZoneManager::GetCollapseIndex(*(const PathfindZoneParams *)item);
	if (index < 0)
		return index == -1;

	unsigned int firstValue = *(unsigned short *)((char *)first + 8);
	unsigned int secondValue = *(unsigned short *)((char *)second + 8);
	PathfindZoneManager *slot = (PathfindZoneManager *)this;
	if (slot->rva00531720(count, firstValue) &&
		slot->rva00531720(count, secondValue) &&
		((PathfindZoneManager *)this)->CouldBeInEquivSet(index, firstValue) &&
		((PathfindZoneManager *)this)->CouldBeInEquivSet(index, secondValue))
		return ((PathfindZoneManager *)this)->InEquivSet(index, firstValue, secondValue);
	return 0;
}
