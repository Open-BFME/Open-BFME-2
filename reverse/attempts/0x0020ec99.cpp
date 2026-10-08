// ?ValidateArmyRegionEntry@LivingWorldRegionManager@@QAEHPAULivingWorldArmy@@PAVRva00318C32Ret@@1HH@Z
// partial score=0.82 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc /MD /arch:SSE
// LivingWorldRegionManager.cpp -- region-manager members recovered from
// WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names the
// function and the region overload it calls (0x0020EA58); retail supplies
// the bytes. The region id lookup is the rowed 0x0020EAF6 accessor.

#include "ascii_string.h"

typedef int Int;
typedef bool Bool;

// The center point is 2D: the region overload writes only x and y.
#include "../../Code/Libraries/Include/Lib/Coord2D.h"

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


struct Rva003F71D4Point;
class Rva003F71D4Metric {
public:
 virtual float v00(const Rva003F71D4Point *,const Rva003F71D4Point *);
 virtual float v01(const Rva003F71D4Point *,const Rva003F71D4Point *);
 virtual void v02(const Rva003F71D4Point *);
 virtual bool v03(int,int);
};
enum ObjectID;
namespace _STL { template<class T> class allocator; template<class T,class A> class vector; }
class LivingWorldPathFinder {
public:
 int FindShortestPath(Rva003F71D4Metric *,int,ObjectID,ObjectID,_STL::vector<ObjectID,_STL::allocator<ObjectID> > *,int);
};
struct RegionArmySetPathView {char pad[0x4c];LivingWorldPathFinder *pathFinder;};
struct LivingWorldArmy;
class Rva00318C32Ret;
struct RegionArmyEntryView {char pad[0x18];AsciiString name;char pad1C[0x38];int player;};
struct RegionEntryView {char pad[0x12c];int id;char pad130[0xc];int player;char pad140[0x62];bool enabled;};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
struct RegionLogicModeView {char pad[0xf4];int mode;};
class Rva002E2903Player;
class Rva002BA8F1Logic {public: Rva002E2903Player *find(int,unsigned int *);};
class Rva002E071E {public:int rva002E0BC0(int);};

class LivingWorldRegionManager
{
public:
	int ValidateArmyRegionEntry(LivingWorldArmy *,Rva00318C32Ret *,Rva00318C32Ret *,int,int);
	void EnumeratePendingBattles(PendingBattleVisitor &visitor) const;
	Bool GetRegionCenterPoint(Int regionID, Coord2D *out);
	Bool GetRegionCenterPoint(Rva0020E89C *region, Coord2D *out);	// 0x0020EA58
	Bool GetRegionUiPopupPoint(Int regionID, Coord2D *out);
	void SetRegionReinforcements(Int regionID, const AsciiString &name, Int a, Int b, Int c, Bool d, Bool e);

private:
	Rva0020E89C *rva0020EAF6(Int regionID);				// 0x0020EAF6

	unsigned char m_pad00[8];
	RegionArmySetPathView *m_armySet;
	unsigned char m_pad0C[8];
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

int LivingWorldRegionManager::ValidateArmyRegionEntry(LivingWorldArmy *army,Rva00318C32Ret *from,Rva00318C32Ret *to,int result,int allow) {
 RegionEntryView *target=reinterpret_cast<RegionEntryView *>(to);
 if(target && target->enabled) {
 RegionArmyEntryView *entry=reinterpret_cast<RegionArmyEntryView *>(army);
 unsigned char allied=1;
 if(target->player!=entry->player) {
  Rva002E2903Player *player=reinterpret_cast<Rva002BA8F1Logic *>(TheLivingWorldLogic)->find(entry->player,0);
  if(!player)return -1;
  allied=(unsigned char)reinterpret_cast<Rva002E071E *>(player)->rva002E0BC0(target->player);
 }
 if((reinterpret_cast<StringBase<char> *>(&entry->name)->isEmpty()||reinterpret_cast<RegionLogicModeView *>(TheLivingWorldLogic)->mode==4)&&!allied)return -1;
 if(!from)return 1;
 Rva003F71D4Metric metric;
 int toID=target->id;
 int fromID=reinterpret_cast<RegionEntryView *>(from)->id;
 int playerID=entry->player;
 LivingWorldPathFinder *finder=m_armySet->pathFinder;
 return finder->FindShortestPath(&metric,playerID,(ObjectID)fromID,(ObjectID)toID,reinterpret_cast<_STL::vector<ObjectID,_STL::allocator<ObjectID> > *>(result),allow);
 }
 return -1;
}
