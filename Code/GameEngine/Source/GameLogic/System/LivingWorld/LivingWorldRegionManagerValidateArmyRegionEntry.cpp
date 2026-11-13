// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /EHsc /MD
// LivingWorldRegionManager::ValidateArmyRegionEntry, split from the
// LivingWorldRegionManager.cpp home: WorldBuilder names it.

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

#include "../../../../Include/GameClient/Rva0020E89C.h"

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
class LivingWorldSearchCallback;
class Rva003EF8E1 {
public:
 int FindShortestPath(LivingWorldSearchCallback *,int,int,int,_STL::vector<ObjectID,_STL::allocator<ObjectID> > *,bool);
};
struct RegionArmySetPathView {char pad[0x4c];Rva003EF8E1 *pathFinder;};
struct LivingWorldArmy;
class Rva00318C32Ret;
struct RegionArmyEntryView {char pad[0x18];AsciiString name;char pad1C[0x38];int player;};
struct RegionEntryView {char pad[0x12c];int id;char pad130[0xc];int player;char pad140[0x62];bool enabled;};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
struct RegionLogicModeView {char pad[0xf4];int mode;};
class Rva002E2903Player;
#include "../../../../Include/GameLogic/Rva002BA8F1Logic.h"
#include "../../../../Include/GameLogic/Rva002E071E.h"

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

// LivingWorldRegionManager::ValidateArmyRegionEntry, retail 0x0020EC99 (184 B;
// WB 0x00B57CA0, LivingWorldRegionManager.cpp:1687): -1 when the army may not
// enter the target region (missing or disabled, its owner's player gone, or
// not allied when the army is unnamed or the logic is in mode 4), 1 when there
// is no source region, else the shortest path length from the region path
// finder (+0x08 army set, +0x4C) with the stack distance metric (vtable
// 0x00BE4340). Offsets: region id +0x12C, owner +0x13C, enabled +0x1A2; army
// name +0x18, player +0x54; logic mode +0xF4.
int LivingWorldRegionManager::ValidateArmyRegionEntry(LivingWorldArmy *army,Rva00318C32Ret *from,Rva00318C32Ret *to,int result,int allow)
{
	RegionEntryView *target = reinterpret_cast<RegionEntryView *>(to);
	if (!target)
		return -1;
	if (!target->enabled)
		return -1;

	RegionArmyEntryView *entry = reinterpret_cast<RegionArmyEntryView *>(army);
	unsigned char owned = 1;
	if (target->player != entry->player)
	{
		Rva002E2903Player *player = reinterpret_cast<Rva002BA8F1Logic *>(TheLivingWorldLogic)->find(entry->player, 0);
		if (!player)
			return -1;
		owned = (unsigned char)reinterpret_cast<Rva002E071E *>(player)->rva002E0BC0(target->player);
	}

	if (!reinterpret_cast<StringBase<char> *>(&entry->name)->isEmpty())
	{
		if (reinterpret_cast<RegionLogicModeView *>(TheLivingWorldLogic)->mode == 4 && !owned)
			return -1;
	}
	else
	{
		if (!owned)
			return -1;
	}

	if (!from)
		return 1;

	Rva003F71D4Metric metric;
	int toID = target->id;
	int fromID = reinterpret_cast<RegionEntryView *>(from)->id;
	int playerID = entry->player;
	Rva003EF8E1 *finder = m_armySet->pathFinder;
	return finder->FindShortestPath((LivingWorldSearchCallback *)&metric, playerID, fromID, toID,
		reinterpret_cast<_STL::vector<ObjectID,_STL::allocator<ObjectID> > *>(result), *(bool *)&allow);
}
