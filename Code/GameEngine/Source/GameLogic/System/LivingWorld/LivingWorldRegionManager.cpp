// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE
// LivingWorldRegionManager.cpp -- region-manager members recovered from
// WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names the
// function and the region overload it calls (0x0020EA58); retail supplies
// the bytes. The region id lookup is the rowed 0x0020EAF6 accessor.

#include "ascii_string.h"

typedef int Int;
typedef bool Bool;

// The center point is 2D: the region overload writes only x and y.
#include "../../../../../Libraries/Include/Lib/Coord2D.h"

// LivingWorldRegion: a region with its own UI popup point (+0xAB) returns
// it through the accessor 0x0020E493, rowed under a placeholder name with an
// explicit out parameter.
struct Out0020E493 : public Coord2D
{
};

class Rva0020E89C
{
public:
	unsigned char m_pad00[0xab];
	bool m_hasUiPopupPoint;				// +0xAB

	// Stores the reinforcement settings (+0x158 name, +0x14C..+0x154,
	// flags +0x1A0/+0x1A1); unrowed and unnamed in WB.
	void rva003F1AB9(const AsciiString &name, Int a, Int b, Int c, Bool d, Bool e);	// 0x003F1AB9
};

class Rva0020E493
{
public:
	Out0020E493 *rva0020E493(Out0020E493 *out);	// 0x0020E493
};

class LivingWorldPendingBattle;

class PendingBattleVisitor
{
public:
	virtual bool Visit(LivingWorldPendingBattle *battle) = 0;
};

class LivingWorldRegionManager
{
public:
	void EnumeratePendingBattles(PendingBattleVisitor &visitor) const;
	Bool GetRegionCenterPoint(Int regionID, Coord2D *out);
	Bool GetRegionCenterPoint(Rva0020E89C *region, Coord2D *out);	// 0x0020EA58
	Bool GetRegionUiPopupPoint(Int regionID, Coord2D *out);
	void SetRegionReinforcements(Int regionID, const AsciiString &name, Int a, Int b, Int c, Bool d, Bool e);

private:
	Rva0020E89C *rva0020EAF6(Int regionID);				// 0x0020EAF6

	unsigned char m_pad00[0x14];
	LivingWorldPendingBattle **m_pendingBattlesStart;		// +0x14
	LivingWorldPendingBattle **m_pendingBattlesFinish;		// +0x18
};

// LivingWorldRegionManager::GetRegionCenterPoint, retail 0x0020F27E.
// ?LivingWorldRegionManager::GetRegionCenterPoint present-unmatched
Bool LivingWorldRegionManager::GetRegionCenterPoint(Int regionID, Coord2D *out)
{
	Rva0020E89C *region = rva0020EAF6(regionID);
	if (region == 0)
		return false;
	return GetRegionCenterPoint(region, out);
}

// LivingWorldRegionManager::EnumeratePendingBattles, retail 0x0020E7BD: visit
// each pending battle until the visitor declines.
void LivingWorldRegionManager::EnumeratePendingBattles(PendingBattleVisitor &visitor) const
{
	LivingWorldPendingBattle **end = m_pendingBattlesFinish;
	for (LivingWorldPendingBattle **it = m_pendingBattlesStart; it != end; ++it)
	{
		LivingWorldPendingBattle *battle = *it;
		if (!visitor.Visit(battle))
			break;
	}
}

// LivingWorldRegionManager::GetRegionUiPopupPoint, retail 0x0020F2A2: the
// region's own popup point when it has one, else its center. WB asserts the
// region exists.
// ?LivingWorldRegionManager::GetRegionUiPopupPoint present-unmatched
Bool LivingWorldRegionManager::GetRegionUiPopupPoint(Int regionID, Coord2D *out)
{
	Rva0020E89C *region = rva0020EAF6(regionID);
	if (region == 0)
		return false;
	if (region->m_hasUiPopupPoint)
	{
		Out0020E493 point;
		*out = *((Rva0020E493 *)region)->rva0020E493(&point);
		return true;
	}
	return GetRegionCenterPoint(regionID, out);
}

// LivingWorldRegionManager::SetRegionReinforcements, retail 0x0020EEC8:
// forwards the settings to the region when it exists (WB logs otherwise).
// ?LivingWorldRegionManager::SetRegionReinforcements present-unmatched
void LivingWorldRegionManager::SetRegionReinforcements(Int regionID, const AsciiString &name, Int a, Int b, Int c, Bool d, Bool e)
{
	Rva0020E89C *region = rva0020EAF6(regionID);
	if (region)
		region->rva003F1AB9(name, a, b, c, d, e);
}
