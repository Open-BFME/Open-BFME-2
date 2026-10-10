// ?rva002B676D@LivingWorldLogic@@QAEXXZ
// partial score=0.9532692307692308 date=2026-10-10
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// cl: /I. /O1 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// LivingWorldLogic.cpp -- LivingWorldLogic members recovered from WorldBuilder
// leads (reverse/wb_name_leads.csv): WB's debug build names the function and
// its callee and asserts !players.empty(); retail supplies the bytes.
//
// The dispute is settled for the first listed player, with flag 0x20 added
// to the victory flags. The element type of the player list is not proven;
// it is carried as a 32-bit value.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#include <vector>
#include <map>
#include <list>
#include <set>

class UnicodeString;
namespace _STL {
// Existing native specialization: this unit only calls its out-of-line clear.
template <> void _List_base<UnicodeString, allocator<UnicodeString> >::clear();
}

class LivingWorldPlayer { public: bool rva002E0B30(); };
class LivingWorldLogic;
struct LivingWorldBuildingNuggetSpawnArmy;

// The singleton at 0x009FEF10 (VA 0x00DFEF10): GameEngine::init registers it
// under the literal "TheLivingWorldLogic" (initSubsystem call site 0x0022F331),
// and no unit defined it, so the callers reading it could not link.
LivingWorldLogic *TheLivingWorldLogic = 0;

// LivingWorldLogic::AutoBattleResolver (WB name), 0x28 bytes; rowed in the
// ledger under the placeholder Rva002B74DE (dtor 0x002B74DE). Its ctor
// (0x002BD40D) and Update (0x002BB7D6) are unrowed.
class Rva002B74DE
{
public:
	Rva002B74DE(LivingWorldLogic *logic, Int battle);	// 0x002BD40D
	~Rva002B74DE();						// 0x002B74DE
	Int Update();						// 0x002BB7D6, 1 when done

private:
	unsigned char m_data[0x28];
};

// m_autoBattleResolver at +0x178: an owning pointer whose reset and clear
// are rowed under placeholder names (OwnedPointerResets.cpp).
class Rva002B90B3
{
public:
	void reset(Rva002B74DE *resolver);			// 0x002B90B3
	Rva002B74DE *get() const { return m_ptr; }

private:
	Rva002B74DE *m_ptr;
};

// Player lookup by id (0x002B51F8) and the per-player upgrade marking
// (0x002E2D8D, WB LivingWorldPlayer::MarkUnitsForUpgrades) are pinned under
// placeholder names for this object and the player.
class Rva002E2903Player
{
public:
	void rva002E2D8D(void *army);				// 0x002E2D8D
};

class AsciiString;
class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *rva002B52A8(Int index);
	Rva002E2903Player *find(Int playerID, UnsignedInt *index);	// 0x002B51F8
	Rva002E2903Player *find(const AsciiString &name, UnsignedInt *index);	// 0x002B6AEC
	struct Rva002B488EResult *rva002B488E(Int armyID);	// 0x002B488E, WB LivingWorldLogic::findArmy
	struct Rva002B2579Result *rva002B2579(int id);	// 0x002B2579
	struct Rva002B3740Item *rva002B2B2D();	// 0x002B2B2D
private:
	char m_pad00[0xB0];
	void *m_containerB0;	// +0xB0
	int m_padB4;
	int m_keyB8;	// +0xB8
};

struct LivingWorldUpgradeArmy
{
	unsigned char m_pad000[0x13c];
	Int m_playerID;						// +0x13C, -1 when unowned
};

// The army set reached through +0xB0 then +0x08. Retail converts it to the
// army list base at +0x2C with a NULL check, the shape of a derived-to-base
// cast, so the list is modelled as a second base.
struct Rva002B5334Base
{
	unsigned char m_pad00[0x2c];
};

struct Rva002B5334ArmyList
{
	_STL::vector<LivingWorldUpgradeArmy *> m_armies;
};

struct Rva002B5334ArmySet : public Rva002B5334Base, public Rva002B5334ArmyList
{
};

#include "Code/Libraries/Include/Lib/Coord2D.h"

// The region manager at +0xB0 (WB: GetRegionCenterPoint is called on it);
// its pending battles vector is at +0x14.
class LivingWorldRegionManager
{
public:
	Bool GetRegionCenterPoint(Int regionID, Coord2D *out);	// 0x0020F27E
	// The region overload (0x0020EA58, pinned under this WorldBuilder name)
	// and the region under a world position (0x0020FAEA, rowed as
	// Rva0020EE29::rva0020FAEA; this spelling returns the region).
	Bool GetRegionCenterPoint(class Rva0020E89C *region, Coord2D *out);
	class Rva00318C32Ret *rva0020FAEA(const Coord2D *pos, class Rva00318C32Ret *hint);
	void rva0020FB8B(class LivingWorldBattle *battle);	// 0x0020FB8B, ends the battle (pinned)
	void UpdateBattleMarkers();				// 0x0020EBA0 (WorldBuilder name, pinned)
	// The check of an army's move between two regions (WorldBuilder name,
	// 0x0020EC99, pinned): 0 or 1 when the move is allowed.
	Int ValidateArmyRegionEntry(struct LivingWorldArmy *army, class Rva00318C32Ret *from, class Rva00318C32Ret *to, Int a, Int b);

	unsigned char m_pad00[0x8];
	Rva002B5334ArmySet *m_armySet;				// +0x08
	unsigned char m_pad0C[0x14 - 0xc];
	_STL::vector<void *> m_field14;				// +0x14
private:
	class Rva0020E89C *rva0020EAF6(int key);		// 0x0020EAF6, pinned
	friend class Rva002BA8F1Logic;
};

// Any-of / all-of walks over this object's vectors, rowed under placeholder
// names (Rva002B4B3D.cpp, Rva002B3288.cpp).
class Rva002B4B3D
{
public:
	Bool rva002B4B3D();					// 0x002B4B3D
};

class Rva002B3288
{
public:
	Bool rva002B3288();					// 0x002B3288
};

class Rva002B9099
{
public:
	void clear();						// 0x002B9099
};

// Army summary entries are reference counted through the counter at +0xAC,
// released by the rowed fastcall 0x0007DEEF; the army's summary at +0x78
// looks an entry up by id and returns it in a holder (0x0040CBD7, WB
// ArmySummary::GetEntry), NULL when absent.
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);	// 0x0007DEEF

class Rva004E0632;

class ArmySummaryEntry
{
public:
	void MarkForUpgrades(const Rva004E0632 *upgrades);	// 0x0040C430
	void CancelUpgrades();					// 0x0040C45C

	// The pending move target at +0xB8 (cleared by WB's
	// CancelArmyMemberMove); an entry already moving takes no upgrades.
	Int getMoveTarget() const { return m_moveTarget; }

	unsigned char m_pad00[0xac];
	unsigned char m_padAC[0xb8 - 0xac];
	Int m_moveTarget;					// +0xB8
	unsigned char m_padBC[0xc4 - 0xbc];
	Bool m_disbanded;					// +0xC4, set by DisbandArmyMember
};

struct ArmySummaryEntryRef
{
	~ArmySummaryEntryRef()
	{
		if (m_entry)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)((char *)m_entry + 0xac));
	}

	ArmySummaryEntry *m_entry;
};

class ArmySummary
{
public:
	ArmySummaryEntryRef GetEntry(Int entryID);		// 0x0040CBD7
};

class Rva004E3184;
struct Rva002B6A04Player;
// Existing native setter318D14, rowed in Disp8ByteFieldSetters.cpp.
class Rva00318D14ByteSlot {public:void set(unsigned char);};
struct LivingWorldArmy
{
 // Native543B constructor31A372/WB1029DF0: caller pushes ID/spawn/player.
 // The reference parameter names remain the existing provisional views.
 LivingWorldArmy(Int,Rva004E3184 *,Rva002B6A04Player *);
	// WorldBuilder LivingWorldArmy::initiateMove (0x0031A591, pinned): starts
	// the army toward the region and position.
	void initiateMove(const Coord2D &pos, class Rva00318C32Ret *target, Int flags);

	unsigned char m_pad00[0x20];
	Int m_id;						// +0x20 (WB LivingWorldArmy::GetID, inlined)
	unsigned char m_pad24[0x54 - 0x24];
	Int m_ownerPlayer;					// +0x54
	unsigned char m_pad58[0x74 - 0x58];
	Bool m_field74;						// +0x74, set: left alone by EnforceArmyRegionOwnership
	unsigned char m_pad75[0x78 - 0x75];
	ArmySummary *m_summary;					// +0x78
 // Native spawnCity allocates98B; opaque tail preserves the existing prefix.
 unsigned char m_pad7C[0x98-0x7C];
};

// Turn listeners at +0x1C are told (old turn, new turn) through the slot +4
// virtual (vcall thunk 0x005CB260); the list's forEach (0x002B616F) and the
// per-turn cleanup at 0x002B7BFB are rowed under placeholder names
// (Rva002B55F2ListenerWalks.cpp, Rva002B7BFB.cpp).
class Rva002B616FListener
{
public:
	virtual void slot00();
	virtual void onTurnChanged(void *oldTurn, int newTurn);	// +0x04
};

class Rva002B616FList
{
public:
	void forEach(void (Rva002B616FListener::*notify)(void *, int), void *arg, int value);	// 0x002B616F

private:
	unsigned char m_data[0x10];
};

class Rva002B7BFB
{
public:
	void rva002B7BFB();					// 0x002B7BFB
};

// TheLivingWorldCampaignManager (0x00E02D6C, rowed lookup 0x003B8BAA); the
// end-of-turn notification at 0x003B8CAC is unrowed, unnamed in WB and pinned.
class Rva003B8BAA
{
public:
	void *rva003B8BAA();					// 0x003B8BAA, see CanDisbandArmyMember
	void rva003B8CAC();					// 0x003B8CAC
};

class Rva00E02D6C; extern Rva00E02D6C *TheCampaignManager;

// The same global as LivingWorldCampaignManager.cpp's view: its generic
// spawn army lookup (rowed 0x003B8CE0) takes the player as its second word.
class LivingWorldCampaignManager
{
public:
	void *UseGenericSpawnArmyForPlayer(Int a, Int b);	// 0x003B8CE0
	void StartNewCampaign(const AsciiString &name);
	void StartNewCampaign(Int campaign);
};

// The generic spawn army's id at +0x4C and the player's id at +0x14, the
// pair this object's +0x13C multimap records (WB asserts
// !HasSpawnedArmyForPlayer(*army, player) before recording it).
struct Rva002B8660Army
{
	unsigned char m_pad00[0x4c];
	Int m_id;						// +0x4C
};

struct Rva002B8660Player
{
	unsigned char m_pad00[0x14];
	Int m_id;						// +0x14
};

class ModuleData;

// The upgrade module behind an armory's module data: the rowed const getter
// 0x004E0632 yields the object whose slot +4 tests an entry.
class Rva004E0632Filter
{
public:
	virtual void slot00();
	virtual Bool accepts(ArmySummaryEntry *entry);		// +0x04
};

class Rva004E0632
{
public:
	Int rva004E0632() const;				// 0x004E0632
};

// The region: its armories through the rowed filter 0x003F28DB, its owning
// player at +0x13C.
class Rva003F287F
{
public:
	void rva003F287F(_STL::vector<const ModuleData *> &out);
 void rva003F28DB(_STL::vector<const ModuleData *> &out);	// 0x003F28DB

	unsigned char m_pad000[0x12c];
	Int m_regionID;						// +0x12C
	unsigned char m_pad130[0x13c - 0x130];
	Int m_ownerPlayer;					// +0x13C
};

// One delayed region victory (WB m_delayedRegionVictories element, 12
// bytes): the player, the region's id and the award flags. Its push_back is
// the ICF-folded 12-byte element instantiation retail calls at 0x002DF89B,
// rowed as vector<PrereqUnitRec>::push_back; the list is appended through
// that view (this unit's exception-enabled copy could not reproduce it).
struct DelayedRegionVictory
{
	Int player;
	Int regionID;
	UnsignedInt flags;
};

struct PrereqUnitRec
{
	unsigned int m_data[3];
	~PrereqUnitRec() {}
};

namespace _STL {
// Existing verified 52B no-EH provider2DF89B owns this specialization.
// The delayed-victory view calls it without emitting an EH-enabled copy.
template <> void vector<PrereqUnitRec, allocator<PrereqUnitRec> >::push_back(const PrereqUnitRec &);
}


// The save/load stream: the slots XferDelayedRegionVictories reaches
// (System/XferEnumHelpers.cpp's model: IsLoading +0x04, the version
// operator +0x28, the int operator +0x7C), and the labelled helpers that
// move a player id (rowed XferLivingWorldPlayerID), a region id and the
// victory flags (rowed under placeholder names, label slot +0x94).
class Xfer
{
public:
	class Version
	{
	public:
		Version(unsigned char current, unsigned char minimum) : m_current(current), m_minimum(minimum) {}
		unsigned char m_current;
		unsigned char m_minimum;
	};

	virtual void slot00();
	virtual Bool IsLoading() const;				// +0x04
	virtual void slot08();
	virtual Bool IsCRC() const;				// +0x0C
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual Xfer &XferRawBytes(void *data, UnsignedInt size);	// +0x24
	virtual Xfer &xferVersion(Version &value);		// +0x28
	virtual void slot2C();
	virtual Xfer &xferSnapshot(void *snapshot);		// +0x30, operator==(Snapshot &)
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual Xfer &xferInt(Int &value);			// +0x7C
};
void XferLivingWorldPlayerID(Xfer *xfer, int *playerID);	// 0x002034C4
struct Rva003EFE82Obj;
int __cdecl Rva003EFE82Get(Rva003EFE82Obj *obj, void *out);	// 0x003EFE82, "LivingWorldRegionID"
struct Rva002B24F0Obj;
int __cdecl Rva002B24F0Get(Rva002B24F0Obj *obj, void *out);	// 0x002B24F0, "LivingWorldRegionVictoryFlags"

// CreateEmptyGarrisonArmy's collaborators: the narrow string copy (rowed
// StringBase<char>::set 0x000366F0); the spawn description (WorldBuilder
// SpawnArmy; ctor pinned at 0x004E30D5 and virtual dtor rowed 0x004E3184
// under the address name Rva004E3184) with its name at +0x04, position at
// +0x20 and flag at +0x54; the player's template strings at +0x24 and
// +0x34 (player +0x40); the region's garrison spot (rowed
// LivingWorldRegion::GetGarrisonArmyPlacementSpot 0x003F0F13); and the
// rowed stdcall lookup 0x002B4948 of the player's army in a region.
template <class T> class StringBase
{
public:
	void set(const StringBase &that);			// 0x000366F0
	bool isEmpty() const;					// 0x00001E2F
	StringBase &operator=(const StringBase &that) { set(that); return *this; }

private:
	T *m_data;
};
struct Rva003F0F13Elem
{
	float a;
	float b;
};
struct Rva0059E647Entry;
class LivingWorldRegion
{
public:
	void rva003F0FA3(void *army);
	void GetGarrisonArmyPlacementSpot(Rva003F0F13Elem *out);	// 0x003F0F13
	void *rva003F0588();					// 0x003F0588, the free building slot
	void rva003F2A8C(Int playerID);				// 0x003F2A8C, owner change
	void rva003EFE72(void *slot, Rva0059E647Entry *buildingTemplate);	// 0x003EFE72, captured placement
	void BuildBuilding(void *slot, Rva0059E647Entry *buildingTemplate);	// 0x003F1C56

	unsigned char m_pad000[0x13c];
	Int m_ownerPlayer;					// +0x13C
};
class Rva004E3184
{
public:
	Rva004E3184(void *arg);					// 0x004E30D5
	virtual ~Rva004E3184();					// 0x004E3184

	StringBase<char> m_name;				// +0x04
	unsigned char m_pad08[0x20 - 0x8];
	Rva003F0F13Elem m_pos;					// +0x20
	unsigned char m_pad28[0x54 - 0x28];
	// Caller-only getter preserves native AL evaluation before the city branch.
	Bool flagged()const{return m_flag54;}
	Bool m_flag54;						// +0x54
	unsigned char m_pad55[0x58 - 0x55];
};
struct Rva002B6A04Template
{
	unsigned char m_pad00[0x24];
	StringBase<char> m_name24;				// +0x24
	unsigned char m_pad28[0x34 - 0x28];
	StringBase<char> m_name34;				// +0x34
};
struct Rva002B6A04Player
{
	unsigned char m_pad00[0x40];
	Rva002B6A04Template *m_template;			// +0x40
};
struct Rva002B6A04Summary
{
	unsigned char m_pad00[0x64];
	StringBase<char> m_name64;				// +0x64
};
void *__stdcall Rva002B4948Find(void *player, void *region, void *arg);	// 0x002B4948

// A world position as the army move helpers pass and return it: Coord2D's
// layout, but returned through a hidden pointer and passed by value the way
// BFME2's Coord2D is (retail 0x002B28B1 builds it in the argument slot), so
// the TU view carries a user-declared constructor.
#include "Code/GameEngine/Source/Common/ArmyMoveDispatchView.h"
#include "Code/GameEngine/Source/Common/RegionCenterPointDispatchView.h"

// LivingWorldLogic's bases: a 0x10-byte primary base, then observer
// interfaces at +0x10 and +0x14 (and the player observer at +0x18, see
// XferPlayers) whose handlers retail enters with this adjusted
// (0x002BA82B reads the logic at -0x14).
class Rva002BA82BBase00
{
public:
	virtual void slot00();
	virtual void slot04();

private:
	unsigned char m_pad04[0x10 - 0x4];
};

class Rva002BA82BObserver10
{
public:
	virtual void slot00();
};

class Rva002BA82BRegionObserver
{
public:
	virtual void OnRegionChangedOwnership(LivingWorldRegion *region, Int oldOwnerID, Int newOwnerID) = 0;
};

// Native player fields read by the unique-player collector. The vector's
// LivingWorldPlayer type is established by this unit; original field names
// and the meaning of the +0x3c4 byte remain unknown.
struct LivingWorldCollectorPlayerView
{
 char pad00[0x34];
 Int key34;
 char pad38[0x3c4-0x38];
 unsigned char flag3C4;
};
class Rva00072FE6 { public: void rva00072FE6(); };

struct TurnPhasePairView {void *begin,*end;bool empty()const{return begin==end;}};
struct Parent00575E4E;
struct Parent0057605D;struct Parent00575EEA;
class LivingWorldLogic : public Rva002BA82BBase00, public Rva002BA82BObserver10, public Rva002BA82BRegionObserver
{
public:
	virtual void OnRegionChangedOwnership(LivingWorldRegion *region, Int oldOwnerID, Int newOwnerID);

	// 0x002B6DC4: the upgrades the region's armory offers the entry.
	const Rva004E0632 *GetArmoryToUpgradeTroop(ArmySummaryEntry *entry, LivingWorldArmy *army, Rva003F287F *region);
	void UpdateTurnPhase();
	void AdjustArmyTargetLocations();
	void ValidatePlayers();
	void rva002B693F(void *keys);
	UnsignedInt rva002B77B2();
	UnsignedInt rva002B77F7();
	void rva002B5AF7();
	void rva002B768F();
	void rva002B676D();
	Bool rva002B3484(Parent0057605D*);
	Bool rva002B3416(Parent00575EEA*);
	Bool rva002B5A5F(Parent00575E4E*);
	bool rva002B4B83();
	Bool EndTurn();
	Bool AdvanceTurnPhase();
	Bool IsCurrentTurnPhaseFinished();
	void processArmyDestroyList();
	void MarkTroopForUpgrades(Int entryID, LivingWorldArmy *army, const Rva004E0632 *upgrades);
	void CancelTroopUpgrades(Int entryID, LivingWorldArmy *army);
	void StartAutoResolveBattle(Int battle);
	void rva002BD90D(UnsignedInt flags, Int battle);
	Bool rva002B89E1(Int battle);
	void rva002BD544(Int campaign);
	void rva002B84CD(Int campaign); // native thiscall, ret 4
	void rva002B47C3(); // native thiscall; WB preserves the receiver
	void rva002B83E5();
	void rva002B49A8();
	void AutoResolveBattle(Int battle);
	void AutoMarkUnitsForUpgrades();
	void CalcAttackingDirection(const _STL::vector<Int> &path, Coord2D *direction);
	Bool CanMoveArmyMember(LivingWorldArmy *army, Int entryID, Int target);
	Bool rva002B8019(LivingWorldArmy *army, ArmySummaryEntry *entry, Int target);	// 0x002B8019
	void LetAIResolveRegionAwardDispute(Int regionID, const _STL::vector<Int> &players, UnsignedInt flags);
	Rva002B8660Army *UseGenericSpawnArmyForPlayer(Int a, Rva002B8660Player *player);
	Bool CanMoveArmyMember_internal(LivingWorldArmy *army, ArmySummaryEntry *entry, LivingWorldArmy *target, Bool checkRoom);
	Bool canBuildUnit(LivingWorldBuildingNuggetSpawnArmy *nugget, Int token);
	Int rva002B2C12(LivingWorldArmy *army, LivingWorldArmy *target);
	void GetNumUpgradeableTroopsInRegionForPlayer(Rva003F287F *region, Int player, Int *countA, Int *countB);
	void EnforceArmyRegionOwnership();
	Bool rva002B27B5(LivingWorldArmy *army, Rva00318C32Ret *target);
	Rva002B2858Coord AdjustArmyMoveTargetPos(Rva00318C32Ret *target, const Coord2D *pos);	// 0x002B2858, pinned
	void armyMoveRequest(LivingWorldArmy *army, Rva00318C32Ret *target, const Coord2D *pos, Int flags);
	void rva002B2834(LivingWorldArmy *army, Int flags);
	void XferDelayedRegionVictories(Xfer *xfer);
	void XferPlayers(Xfer *xfer);
	void AwardOwnershipSetsToPlayers();
	void spawnCity(Rva004E3184 *city);
	LivingWorldArmy *spawnArmy(Rva004E3184 *spawn, Rva002B6A04Player *player, Bool flag);	// 0x002B65B7, pinned
	LivingWorldArmy *CreateEmptyGarrisonArmy(Rva002B6A04Player *player, LivingWorldRegion *region);
	void *rva002B4948(void *player, LivingWorldRegion *region, Int arg);	// 0x002B4948 (rowed as the stdcall Rva002B4948Find)
	void spawnBuilding(const struct Rva002B99F8Request *request);
	Bool rva002B5CBB(const struct Rva002B4C35Player *player);
	void GameLogic_tacticalBattleComplete();
	void OnBattleComplete(class LivingWorldBattle *battle);
	void rva002B9A90(Int regionID, const _STL::vector<Int> &players, UnsignedInt flags);	// 0x002B9A90
	void rva002B37FF(class LivingWorldBattle *battle);	// 0x002B37FF
	void PrepareBattleForLoading(class LivingWorldBattle *battle);

private:
	void AddDelayedRegionVictory(Rva003F287F *region, Int player, UnsignedInt flags);	// 0x002B9B42
	void CheckTurnPhaseTransitions();		// 0x002BD23E
	void rva002B5B55(void *army);			// 0x002B5B55, destroys one army

	unsigned char m_pad18[0x1c - 0x18];
	Rva002B616FList m_turnListeners;		// +0x1C
	unsigned char m_pad2C[0x3c - 0x2c];
	Rva002B616FList m_battleListeners;		// +0x3C, told (logic, battle) when a battle completes
	unsigned char m_pad4C[0x8c - 0x4c];
	_STL::vector<LivingWorldPlayer *> m_players;	// +0x8C
	LivingWorldPlayer *m_localPlayer;		// +0x98 (WB member name)
	Int m_field9C, m_fieldA0, m_fieldA4, m_fieldA8, m_fieldAC; // native reset words
	LivingWorldRegionManager *m_field0B0;		// +0xB0, region manager
	unsigned char m_padB4[0xb6 - 0xb4];
	Bool m_fieldB6;					// +0xB6, set when a tactical battle completes
	unsigned char m_padB7[0xb8 - 0xb7];
	Int m_fieldB8;					// +0xB8, the battle region index, reset to -1
	unsigned char m_padBC[0xcc - 0xbc];
	_STL::vector<void *> m_fieldCC;			// +0xCC
	unsigned char m_padD8[0xf4 - 0xd8];
	Int m_turnPhase;				// +0xF4 (WB member name)
	Int m_fieldF8; // reset to -1 by native 0x002BD544
	Int m_turn;					// +0xFC
	UnsignedInt m_field100;				// +0x100
	UnsignedInt m_field104;				// +0x104
	Bool m_field108;				// +0x108
	Bool m_field109;				// +0x109
	Bool m_native10A; unsigned char m_pad10B;
	_STL::vector<void *> m_field10C;		// +0x10C
	_STL::vector<void *> m_armyDestroyList;		// +0x118
	unsigned char m_pad124[0x130 - 0x124];
	_STL::map<Int, class RegionAwardDispute *> m_regionAwardDisputes;	// +0x130
	_STL::multimap<Int, Int> m_spawnedArmies;	// +0x13C, generic army id -> player id
	_STL::vector<DelayedRegionVictory> m_delayedRegionVictories;	// +0x148 (WB member name)
	TurnPhasePairView m_pending154; unsigned char m_pad15C[0x178 - 0x15c];
	Rva002B90B3 m_autoBattleResolver;		// +0x178 (WB member name)
};

enum { TURN_PHASE_LAST_ADVANCEABLE = 6 };

// LivingWorldLogic::EndTurn, retail 0x002BD36D (WB name). From the last
// advanceable phase: run the per-turn cleanup, tell the turn listeners
// (old turn, new turn), reset the phase, copy +0x100 to +0x104, clear the two
// flags, advance the turn, notify the campaign manager and recheck phase
// transitions. The turn increment written after the field stores is what
// keeps cl from hoisting &m_turn into a register (retail addresses it off
// this, scheduled before the stores).
class Rva004E071D {public:void rva004E071D(Bool);};
class Rva004FC275 {public:void rva004FC275(unsigned char);};
struct LocalCampaignRegions2C {char pad2c[0x2c];_STL::vector<Rva003F287F*>regions;};
struct LocalPlayerId14 {char pad14[0x14];Int id;};
struct LocalRegionOwner13C {char pad13c[0x13c];Int owner;};
struct LocalRegionPlots170 {char pad13c[0x13c];Int owner;char pad140[0x170-0x140];_STL::vector<Parent00575EEA*>plots;};
void LivingWorldLogic::rva002B676D(){
 if(m_localPlayer){
 LocalCampaignRegions2C*campaign=reinterpret_cast<LocalCampaignRegions2C*>(m_field0B0->m_armySet);
 _STL::vector<Rva003F287F*>*regions;if(campaign)regions=&campaign->regions;else regions=0;
 if(regions){
 _STL::vector<const ModuleData*>unusedModules;
 for(unsigned i=0;i<regions->size();++i){
  LocalRegionPlots170*region=reinterpret_cast<LocalRegionPlots170*>((*(m_localPlayer?regions:regions))[i]);
  if(region->owner==reinterpret_cast<LocalPlayerId14*>(m_localPlayer)->id){
   int count=region->plots.size();
   for(int j=0;j<count;++j){
    Parent00575EEA*entry=region->plots[j];
    Bool show=rva002B3416(entry);
    reinterpret_cast<Rva004FC275*>(entry)->rva004FC275(show);
   }
  }
 }
 }
 }
}
