// cl: /O1 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
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

class UnicodeString;
namespace _STL {
// Existing native specialization: this unit only calls its out-of-line clear.
template <> void _List_base<UnicodeString, allocator<UnicodeString> >::clear();
}

class LivingWorldPlayer;
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

#include "../../../../../Libraries/Include/Lib/Coord2D.h"

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

struct LivingWorldArmy
{
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
struct Rva002B2858Coord
{
	Rva002B2858Coord() {}
	Rva002B2858Coord(const Rva002B2858Coord &that) : x(that.x), y(that.y) {}
	~Rva002B2858Coord() {}
	float x;
	float y;
};

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

class LivingWorldLogic : public Rva002BA82BBase00, public Rva002BA82BObserver10, public Rva002BA82BRegionObserver
{
public:
	virtual void OnRegionChangedOwnership(LivingWorldRegion *region, Int oldOwnerID, Int newOwnerID);

	// 0x002B6DC4: the upgrades the region's armory offers the entry.
	const Rva004E0632 *GetArmoryToUpgradeTroop(ArmySummaryEntry *entry, LivingWorldArmy *army, Rva003F287F *region);
	void ValidatePlayers();
	Bool EndTurn();
	Bool AdvanceTurnPhase();
	Bool IsCurrentTurnPhaseFinished();
	void processArmyDestroyList();
	void MarkTroopForUpgrades(Int entryID, LivingWorldArmy *army, const Rva004E0632 *upgrades);
	void CancelTroopUpgrades(Int entryID, LivingWorldArmy *army);
	void StartAutoResolveBattle(Int battle);
	void rva002BD544(Int campaign);
	void rva002B84CD(Int campaign); // native thiscall, ret 4
	void rva002B47C3(); // native thiscall; WB preserves the receiver
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
	void rva002B26D0(LivingWorldArmy *army, Rva00318C32Ret *target, Rva002B2858Coord pos, Int flags);
	Rva002B2858Coord AdjustArmyMoveTargetPos(Rva00318C32Ret *target, const Coord2D *pos);	// 0x002B2858, pinned
	void armyMoveRequest(LivingWorldArmy *army, Rva00318C32Ret *target, const Coord2D *pos, Int flags);
	void rva002B2834(LivingWorldArmy *army, Int flags);
	void XferDelayedRegionVictories(Xfer *xfer);
	void XferPlayers(Xfer *xfer);
	void AwardOwnershipSetsToPlayers();
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
	unsigned char m_pad9C[0xb0 - 0x9c];
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
	unsigned char m_pad10A[0x10c - 0x10a];
	_STL::vector<void *> m_field10C;		// +0x10C
	_STL::vector<void *> m_armyDestroyList;		// +0x118
	unsigned char m_pad124[0x130 - 0x124];
	_STL::map<Int, class RegionAwardDispute *> m_regionAwardDisputes;	// +0x130
	_STL::multimap<Int, Int> m_spawnedArmies;	// +0x13C, generic army id -> player id
	_STL::vector<DelayedRegionVictory> m_delayedRegionVictories;	// +0x148 (WB member name)
	unsigned char m_pad154[0x178 - 0x154];
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
Bool LivingWorldLogic::EndTurn()
{
	if (TURN_PHASE_LAST_ADVANCEABLE == m_turnPhase)
	{
		((Rva002B7BFB *)this)->rva002B7BFB();
		Int turn = m_turn;
		m_turnListeners.forEach(&Rva002B616FListener::onTurnChanged, (void *)turn, turn + 1);
		m_turnPhase = 0;
		m_field104 = m_field100;
		m_field108 = false;
		m_field109 = false;
		m_turn++;
		((Rva003B8BAA *)TheCampaignManager)->rva003B8CAC();
		CheckTurnPhaseTransitions();
		return true;
	}
	return false;
}

// LivingWorldLogic::AdvanceTurnPhase, retail 0x002BD3D6. WB also logs the
// refused request and the phase transition; retail keeps the logic only.
// The +0x100 value is copied to +0x104 on every advance (names unknown).
Bool LivingWorldLogic::AdvanceTurnPhase()
{
	if (!IsCurrentTurnPhaseFinished() || m_turnPhase >= TURN_PHASE_LAST_ADVANCEABLE)
		return false;
	m_turnPhase = m_turnPhase + 1;
	m_field104 = m_field100;
	CheckTurnPhaseTransitions();
	return true;
}

// LivingWorldLogic::ValidatePlayers, retail 0x002B38D2. WB logs when there
// are no players and when it falls back to the first one.
void LivingWorldLogic::ValidatePlayers()
{
	if (m_players.size() == 0)
		return;
	if (m_localPlayer == 0)
		m_localPlayer = m_players[0];
}

// LivingWorldLogic::LetAIResolveRegionAwardDispute, retail 0x002BAF5D.
void LivingWorldLogic::LetAIResolveRegionAwardDispute(Int regionID, const _STL::vector<Int> &players, UnsignedInt flags)
{
	if (players.empty())
		return;
	flags |= 0x20;
	AddDelayedRegionVictory((Rva003F287F *)regionID, players[0], flags);
}

// LivingWorldLogic::processArmyDestroyList, retail 0x002B7BBB. Destroys every
// queued army through the unrowed per-army worker, then empties the queue.
// The queue clears through the folded pointer-vector range erase (rowed as
// vector<void *>), so it is carried as one.
void LivingWorldLogic::processArmyDestroyList()
{
	for (UnsignedInt i = 0; i < m_armyDestroyList.size(); ++i)
		rva002B5B55(m_armyDestroyList[i]);
	m_armyDestroyList.clear();
}

// LivingWorldLogic::MarkTroopForUpgrades, retail 0x002B3FD3. WB asserts the
// entry is bound; retail skips an absent one.
void LivingWorldLogic::MarkTroopForUpgrades(Int entryID, LivingWorldArmy *army, const Rva004E0632 *upgrades)
{
	ArmySummary *summary = army->m_summary;
	ArmySummaryEntryRef entry = summary->GetEntry(entryID);
	if (entry.m_entry == 0)
		return;
	entry.m_entry->MarkForUpgrades(upgrades);
}

// LivingWorldLogic::CancelTroopUpgrades, retail 0x002B4026.
void LivingWorldLogic::CancelTroopUpgrades(Int entryID, LivingWorldArmy *army)
{
	ArmySummary *summary = army->m_summary;
	ArmySummaryEntryRef entry = summary->GetEntry(entryID);
	if (entry.m_entry == 0)
		return;
	entry.m_entry->CancelUpgrades();
}

// LivingWorldLogic::StartAutoResolveBattle, retail 0x002BD603. WB asserts no
// resolver is already bound.
void LivingWorldLogic::StartAutoResolveBattle(Int battle)
{
	m_autoBattleResolver.reset(new Rva002B74DE(this, battle));
}

// LivingWorldLogic::AutoResolveBattle, retail 0x002BD64F: resolves the whole
// battle at once, then drops the resolver.
void LivingWorldLogic::AutoResolveBattle(Int battle)
{
	m_autoBattleResolver.reset(new Rva002B74DE(this, battle));
	while (m_autoBattleResolver.get()->Update() != 1)
		;
	((Rva002B9099 *)&m_autoBattleResolver)->clear();
}

// LivingWorldLogic::AutoMarkUnitsForUpgrades, retail 0x002B5334: every owned
// army is handed to its player's upgrade marking. WB asserts the player
// exists.
// ?LivingWorldLogic::AutoMarkUnitsForUpgrades present-unmatched
void LivingWorldLogic::AutoMarkUnitsForUpgrades()
{
	Rva002B5334ArmyList *list = m_field0B0->m_armySet;
	for (UnsignedInt i = 0; i < list->m_armies.size(); ++i)
	{
		LivingWorldUpgradeArmy *army = list->m_armies[i];
		if (army->m_playerID != -1)
		{
			Rva002E2903Player *player = ((Rva002BA8F1Logic *)this)->find(army->m_playerID, 0);
			player->rva002E2D8D(army);
		}
	}
}

// LivingWorldLogic::CanMoveArmyMember, retail 0x002B8F8B: an absent entry
// cannot move; otherwise the unrowed check at 0x002B8019 decides.
Bool LivingWorldLogic::CanMoveArmyMember(LivingWorldArmy *army, Int entryID, Int target)
{
	ArmySummary *summary = army->m_summary;
	ArmySummaryEntryRef entry = summary->GetEntry(entryID);
	if (entry.m_entry == 0)
		return false;
	return rva002B8019(army, entry.m_entry, target);
}

// LivingWorldLogic::IsCurrentTurnPhaseFinished, retail 0x002B5390. WB logs
// an unhandled phase; member names are unknown.
Bool LivingWorldLogic::IsCurrentTurnPhaseFinished()
{
	switch (m_turnPhase)
	{
		case 0:
			return m_fieldCC.empty();
		case 1:
		case 5:
			return !((Rva002B4B3D *)this)->rva002B4B3D();
		case 2:
			return !(m_field0B0->m_field14.size() > 0);
		case 3:
			return m_field100 >= m_field104 + 1;
		case 4:
			return m_field10C.empty() || ((Rva002B3288 *)this)->rva002B3288();
		case 6:
			return true;
	}
	return false;
}

// AttackOrders (WB name) keeps its members at +0x08. Each member looks up
// its hero entry by the key at +0x18 (0x0031996D, unrowed and unnamed in WB),
// returned in the same reference-counted holder as army summary entries;
// the hero's rank is at +0x0C.
struct HeroEntryKey;

class AttackOrdersMember
{
public:
	ArmySummaryEntryRef rva0031996D(const HeroEntryKey &key);	// 0x0031996D

	unsigned char m_pad00[0x18];
	HeroEntryKey &key() { return *(HeroEntryKey *)m_key; }

private:
	unsigned char m_key[4];					// +0x18
};

template <class T> inline const T &maxOf(const T &a, const T &b)
{
	return (a < b) ? b : a;
}

class AttackOrders
{
public:
	Int GetMaxHeroLeaderRank();

private:
	unsigned char m_pad00[0x8];
	_STL::vector<AttackOrdersMember *> m_members;		// +0x08
};

// AttackOrders::GetMaxHeroLeaderRank, retail 0x002B3A9C. WB asserts every
// member's hero entry is bound; retail skips unbound ones.
Int AttackOrders::GetMaxHeroLeaderRank()
{
	Int maxRank = 0;
	for (UnsignedInt i = 0; i < m_members.size(); ++i)
	{
		AttackOrdersMember *member = m_members[i];
		ArmySummaryEntryRef heroEntry = member->rva0031996D(member->key());
		if (heroEntry.m_entry)
		{
			Int rank = *(const Int *)((const char *)heroEntry.m_entry + 0xc);
			maxRank = maxOf(maxRank, rank);
		}
	}
	return maxRank;
}

// LivingWorldLogic::CalcAttackingDirection, retail 0x002B4F6C: the direction
// between the centers of the last two regions of a path (both the first
// region when the path is shorter).
// ?LivingWorldLogic::CalcAttackingDirection present-unmatched
void LivingWorldLogic::CalcAttackingDirection(const _STL::vector<Int> &path, Coord2D *direction)
{
	Int last = path.size() - 1;
	Int previous = path.size() - 2;
	if (last < 0 || previous < 0)
	{
		last = 0;
		previous = 0;
	}
	Coord2D from, to;
	m_field0B0->GetRegionCenterPoint(path[last], &from);
	m_field0B0->GetRegionCenterPoint(path[previous], &to);
	*direction = to;
	direction->x -= from.x;
	direction->y -= from.y;
}

// The army summary's keyed value getter (0x0040CBB8, rowed under the
// placeholder Rva0040CB3AIndexedField): the entry for an id, NULL when absent.
class Rva0040CB3AIndexedField
{
public:
	Int get(Int index) const;				// 0x0040CBB8
};

// TheLivingWorldLogic (0x00DFEF10): its rowed int-returning check 0x002B254F,
// tested as a byte by every caller.
class Rva002B254F
{
public:
	Int rva002B254F();					// 0x002B254F
};

class LivingWorldLogic; extern LivingWorldLogic *TheLivingWorldLogic;

// TheLivingWorldCampaignManager's rowed lookup 0x003B8BAA (on g_00E02D6C
// above) returns the object
// whose slot +8 vets an army summary entry.
class Rva003B8BAAEntryVet
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual Bool vetEntry(ArmySummaryEntry *entry);		// +0x08
};

// The thing template's KindOf mask at +0x108 (WB tests bit 90 through the
// BitFlags helper 0x00045623; retail reads the word at +0x110 inline).
struct ThingTemplateKindOf
{
	unsigned char m_pad000[0x108];
	UnsignedInt m_kindOf[6];				// +0x108, observed through bit 190

	Bool isKindOf(Int bit) const { return (m_kindOf[bit >> 5] >> (bit & 31)) & 1; }
};

class AsciiString;

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *name);	// 0x002D06CA, TheThingFactory->findTemplate
};

extern Rva002D06CA *g_00DFF000;

// The army member's template name (entry +0x04) against the army's own
// (+0x18), through the rowed StringBase compare 0x000069D6 (pinned view).
class Rva004525B0String
{
public:
	Int compare(const Rva004525B0String &that) const;	// 0x000069D6
};

// The target army's room for an entry: rowed 0x00319413.
class Rva0037DCA5
{
public:
	void *rva0037DC52();					// 0x0037DC52, template lookup
};
class Rva003193EC
{
public:
	bool rva00319413(Rva0037DCA5 *entry);			// 0x00319413
};



// CanDisbandArmyMember, retail 0x002B3E7E (88 bytes): WB's one-argument
// overload in LivingWorldLogic.cpp (asserts at lines 8110 and 8112). Its
// entry argument arrives in EAX: cl 7.1 gives that convention to a
// file-static whose every caller is in its unit (the rowed DisbandArmy in
// Rva002B3EFA.cpp reaches it through the Rva002B3E7ECheck pin). An entry
// the campaign refuses, one already disbanded, or one whose template is
// missing or of KindOf bit 90 cannot be disbanded.
static Bool CanDisbandArmyMember(ArmySummaryEntry *entry)
{
	if ((unsigned char)((Rva002B254F *)TheLivingWorldLogic)->rva002B254F() != 0)
	{
		if (!((Rva003B8BAAEntryVet *)((Rva003B8BAA *)TheCampaignManager)->rva003B8BAA())->vetEntry(entry))
			return 0;
	}
	if (entry->m_disbanded)
		return 0;
	const ThingTemplateKindOf *thing = (const ThingTemplateKindOf *)g_00DFF000->rva002D06CA((const AsciiString *)((char *)entry + 4));
	if (thing == 0)
		return 0;
	if (thing->isKindOf(90))
		return 0;
	return 1;
}

// CanDisbandArmyMember, retail 0x002B3ED6 (36 bytes): WB's two-argument free
// function in LivingWorldLogic.cpp, asserting the army's summary is bound.
// The summary entry for the id must exist and pass the per-entry check.
Bool CanDisbandArmyMember(LivingWorldArmy *army, Int entryID)
{
	Rva0040CB3AIndexedField *summary = (Rva0040CB3AIndexedField *)army->m_summary;
	ArmySummaryEntry *entry = (ArmySummaryEntry *)summary->get(entryID);
	return entry != 0 && CanDisbandArmyMember(entry);
}

// DisbandArmyMember, retail 0x002B3F3B (100 bytes): WB's free function in
// LivingWorldLogic.cpp. A bound entry that may be disbanded is flagged at
// +0xC4 and has its upgrades cancelled.
void DisbandArmyMember(LivingWorldArmy *army, Int entryID)
{
	ArmySummary *summary = army->m_summary;
	ArmySummaryEntryRef entry = summary->GetEntry(entryID);
	ArmySummaryEntry *bound = entry.m_entry;
	if (bound != 0 && CanDisbandArmyMember(bound))
	{
		entry.m_entry->m_disbanded = 1;
		entry.m_entry->CancelUpgrades();
	}
}

// GameMessage (Zero Hour's GameMessage.h): the argument count byte at +0x18
// and the rowed argument lookup 0x0030F4EA.
union GameMessageArgumentType
{
	Int integer;
};

class GameMessage
{
public:
	const GameMessageArgumentType *getArgument(Int argIndex) const;	// 0x0030F4EA
	UnsignedInt getArgumentCount() const { return m_argCount; }

private:
	unsigned char m_pad00[0x18];
	unsigned char m_argCount;				// +0x18
};

// WB's validateMessageArgumentIndex / validateArmy / validateArmySummaryEntryID
// helpers, which retail inlines into each message getter.
static inline Bool validateMessageArgumentIndex(const GameMessage *msg, Int argIndex)
{
	return argIndex >= 0 && argIndex < (Int)msg->getArgumentCount();
}

static inline Bool validateArmySummaryEntryID(Int entryID, LivingWorldArmy *army)
{
	Rva0040CB3AIndexedField *summary = (Rva0040CB3AIndexedField *)army->m_summary;
	Int entry = summary->get(entryID);
	return entry != 0;
}

// getArmyFromMessage, retail 0x002B543D (58 bytes): WB's file-static in
// LivingWorldLogic.cpp (asserts msg != NULL at line 8381). The army whose id
// is the message argument, through TheLivingWorldLogic's findArmy
// (0x002B488E). Retail passes the message in ECX, cl 7.1's convention for a
// file-static whose callers are all in its unit.
static __declspec(noinline) Bool getArmyFromMessage(LivingWorldArmy **army, const GameMessage *msg, Int argIndex)
{
	if (!validateMessageArgumentIndex(msg, argIndex))
		return 0;
	Int armyID = msg->getArgument(argIndex)->integer;
	*army = (LivingWorldArmy *)((Rva002BA8F1Logic *)((Rva002B254F *)TheLivingWorldLogic))->rva002B488E(armyID);
	return *army != 0;
}

// getArmySummaryEntryIDFromMessage, retail 0x002B4108 (57 bytes): WB's
// file-static; the id must name an entry of the army's summary.
static __declspec(noinline) Bool getArmySummaryEntryIDFromMessage(Int *entryID, const GameMessage *msg, Int argIndex, LivingWorldArmy *army)
{
	if (!validateMessageArgumentIndex(msg, argIndex))
		return 0;
	*entryID = msg->getArgument(argIndex)->integer;
	return validateArmySummaryEntryID(*entryID, army);
}

// HandleUnmarkUnitForUpgradeMessage, retail 0x002B5477 (68 bytes): WB's
// handler in LivingWorldLogic.cpp: argument 0 names the army, argument 1 the
// summary entry whose upgrades TheLivingWorldLogic cancels.
void HandleUnmarkUnitForUpgradeMessage(const GameMessage *msg)
{
	LivingWorldArmy *army;
	Int entryID;
	if (getArmyFromMessage(&army, msg, 0)
		&& getArmySummaryEntryIDFromMessage(&entryID, msg, 1, army))
		((LivingWorldLogic *)((Rva002B254F *)TheLivingWorldLogic))->CancelTroopUpgrades(entryID, army);
}

// The army's region lookup 0x00318C32 (unrowed, pinned under the placeholder
// Rva00318C79Owner): NULL when the army stands in no region.
class Rva00318C32Ret;

class Rva00318C79Owner
{
public:
	Rva00318C32Ret *rva00318C32();				// 0x00318C32
};

// HandleMarkUnitForUpgradeMessage, retail 0x002B6F57 (169 bytes): WB's
// handler in LivingWorldLogic.cpp: argument 0 names an army standing in a
// region, argument 1 its summary entry, which TheLivingWorldLogic marks for
// the upgrades of the region's armory.
void HandleMarkUnitForUpgradeMessage(const GameMessage *msg)
{
	LivingWorldArmy *army;
	if (!getArmyFromMessage(&army, msg, 0))
		return;
	Rva00318C32Ret *region = ((Rva00318C79Owner *)army)->rva00318C32();
	if (region == 0)
		return;
	Int entryID;
	if (!getArmySummaryEntryIDFromMessage(&entryID, msg, 1, army))
		return;
	ArmySummaryEntryRef entry = army->m_summary->GetEntry(entryID);
	if (entry.m_entry == 0)
		return;
	const Rva004E0632 *upgrades = ((LivingWorldLogic *)((Rva002B254F *)TheLivingWorldLogic))->GetArmoryToUpgradeTroop(entry.m_entry, army, (Rva003F287F *)region);
	if (upgrades != 0)
		((LivingWorldLogic *)((Rva002B254F *)TheLivingWorldLogic))->MarkTroopForUpgrades(entryID, army, upgrades);
}

// LivingWorldLogic::GetArmoryToUpgradeTroop, retail 0x002B6DC4 (198 bytes):
// WB names it in LivingWorldLogic.cpp. The army must stand in the region and
// share its owner, and the entry must not be moving; the first of the
// region's armories whose upgrade accepts the entry is returned.
const Rva004E0632 *LivingWorldLogic::GetArmoryToUpgradeTroop(ArmySummaryEntry *entry, LivingWorldArmy *army, Rva003F287F *region)
{
	if ((void *)((Rva00318C79Owner *)army)->rva00318C32() != (void *)region)
		return 0;
	if (army->m_ownerPlayer != region->m_ownerPlayer)
		return 0;
	if (entry->getMoveTarget() != 0)
		return 0;
	_STL::vector<const ModuleData *> armories;
	region->rva003F28DB(armories);
	for (UnsignedInt i = 0; i < armories.size(); ++i)
	{
		const Rva004E0632 *armory = (const Rva004E0632 *)armories[i];
		if (((Rva004E0632Filter *)armory->rva004E0632())->accepts(entry))
			return armory;
	}
	return 0;
}

// LivingWorldLogic::UseGenericSpawnArmyForPlayer, retail 0x002B8660 (74
// bytes; WB name, assert line 1848). Takes the campaign's generic spawn army
// for the player and records (army id, player id); NULL without one.
Rva002B8660Army *LivingWorldLogic::UseGenericSpawnArmyForPlayer(Int a, Rva002B8660Player *player)
{
	Rva002B8660Army *army = (Rva002B8660Army *)((LivingWorldCampaignManager *)TheCampaignManager)->UseGenericSpawnArmyForPlayer(a, (Int)player);
	if (army)
		m_spawnedArmies.insert(_STL::make_pair(army->m_id, player->m_id));
	return army;
}

// LivingWorldLogic::AddDelayedRegionVictory, retail 0x002B9B42 (117 bytes;
// WB name, assert line 3613 against a region already awarded). A region is
// queued once; later awards for it are dropped.
void LivingWorldLogic::AddDelayedRegionVictory(Rva003F287F *region, Int player, UnsignedInt flags)
{
	for (UnsignedInt i = 0; i < m_delayedRegionVictories.size(); ++i)
	{
		if (m_delayedRegionVictories[i].regionID == region->m_regionID)
			return;
	}
	DelayedRegionVictory victory;
	victory.player = player;
	victory.regionID = region->m_regionID;
	victory.flags = flags;
	((_STL::vector<PrereqUnitRec> *)&m_delayedRegionVictories)->push_back(*(const PrereqUnitRec *)&victory);
}

// Retail 0x002B2C12 (46 bytes; WorldBuilder leaves it unnamed, its only
// callees are the army region getter and
// LivingWorldRegionManager::ValidateArmyRegionEntry): checks a move of the
// army from its region to the target army's region.
Int LivingWorldLogic::rva002B2C12(LivingWorldArmy *army, LivingWorldArmy *target)
{
	return m_field0B0->ValidateArmyRegionEntry(army, ((Rva00318C79Owner *)army)->rva00318C32(), ((Rva00318C79Owner *)target)->rva00318C32(), 0, 0);
}

// LivingWorldLogic::CanMoveArmyMember_internal, retail 0x002B6B5B (116
// bytes; WB name, assert line 7861 on the entry's previous army). An entry
// of the army's own kind stays; an entry already moving must be able to
// reach the target from the army it is moving to, otherwise from this one;
// with checkRoom the target must also take it.
Bool LivingWorldLogic::CanMoveArmyMember_internal(LivingWorldArmy *army, ArmySummaryEntry *entry, LivingWorldArmy *target, Bool checkRoom)
{
	if (((const Rva004525B0String *)((char *)entry + 4))->compare(*(const Rva004525B0String *)((char *)army + 0x18)) == 0)
		return false;
	if (entry->getMoveTarget() != 0)
	{
		if (entry->getMoveTarget() != target->m_id)
		{
			LivingWorldArmy *oldSourceArmy = (LivingWorldArmy *)((Rva002BA8F1Logic *)this)->rva002B488E(entry->getMoveTarget());
			if (oldSourceArmy == 0)
				return false;
			Int result = rva002B2C12(oldSourceArmy, target);
			Bool valid = result >= 0 && result <= 1;
			if (!valid)
				return false;
		}
	}
	else
	{
		Int result = rva002B2C12(army, target);
		Bool valid = result >= 0 && result <= 1;
		if (!valid)
			return false;
	}
	if (checkRoom && !((Rva003193EC *)target)->rva00319413((Rva0037DCA5 *)entry))
		return false;
	return true;
}

// canBuildUnit's target views: the nugget's build interface is its +0x0C
// base; the game slot's optional player data begins at +0x64 and is enabled
// by +0x60. The requested unit is a 32-bit token, also collected by
// 0x004FAE34; its enum identity remains unproven.
struct LivingWorldBuildingNuggetSpawnArmy
{
	Rva002E2903Player *rva004FA618();			// 0x004FA618
};
class Rva002B3325BuildInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual Bool build(Int token, Rva004E3184 *spawn);	// +0x10
};
class Rva002B3325Campaign
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual Bool canBuild(LivingWorldBuildingNuggetSpawnArmy *nugget, Int token);	// +0x24
};
class GameSlot
{
public:
	void *GetPlayerData() { return m_hasData ? (void *)m_playerData : 0; }
	unsigned char m_pad00[0x60];
	unsigned char m_hasData;
	unsigned char m_pad61[3];
	unsigned char m_playerData[1];
};
class Rva002E06B8
{
public:
	GameSlot *rva002E06B8();				// 0x002E06B8
};
class Rva00319CED
{
public:
	void *rva004E23C1();					// 0x004E23C1
};
class Rva0040CB2CIndexedField
{
public:
	Int get(Int index) const;					// 0x0040CB2C
};
struct Rva002B3325Summary
{
	struct Entry { Int id; ArmySummaryEntry *entry; };
	unsigned char m_pad00[0x40];
	_STL::vector<Entry> m_entries;
};

// WB LivingWorldLogic::canBuildUnit (asserts 1471..1491); retail 0x002B3325
// checks campaign approval and ownership, then a proposed spawn's first
// entry and KindOf bit 190 when the player's slot has no player data.
Bool LivingWorldLogic::canBuildUnit(LivingWorldBuildingNuggetSpawnArmy *nugget, Int token)
{
	if ((unsigned char)((Rva002B254F *)this)->rva002B254F() != 0)
	{
		Rva002B3325Campaign *campaign = (Rva002B3325Campaign *)((Rva003B8BAA *)TheCampaignManager)->rva003B8BAA();
		if (!campaign->canBuild(nugget, token))
			return false;
	}
	Rva002E2903Player *player = nugget->rva004FA618();
	if (player == 0)
		return false;
	GameSlot *slot = ((Rva002E06B8 *)player)->rva002E06B8();
	if (slot != 0 && slot->GetPlayerData() == 0)
	{
		Rva004E3184 spawn(0);
		if (!((Rva002B3325BuildInterface *)((char *)nugget + 0x0c))->build(token, &spawn))
			return false;
		Rva002B3325Summary *summary = (Rva002B3325Summary *)((Rva00319CED *)&spawn)->rva004E23C1();
		if (summary == 0)
			return false;
		if (summary->m_entries.size() == 0)
			return false;
		Rva0037DCA5 *entry = (Rva0037DCA5 *)((Rva0040CB2CIndexedField *)summary)->get(0);
		const ThingTemplateKindOf *thing = (const ThingTemplateKindOf *)entry->rva0037DC52();
		if (thing == 0)
			return false;
		if ((thing->m_kindOf[5] & (1u << 30)) != 0)
			return false;
	}
	return true;
}

// The armory upgrade's two troop counts (slots +0x00 and +0x08 of the
// object the rowed getter 0x004E0632 yields; the filter above is slot +0x04).
class Rva002B6E8AUpgrade
{
public:
	virtual Int count00();
	virtual void slot04();
	virtual Int count08();
};

// LivingWorldLogic::GetNumUpgradeableTroopsInRegionForPlayer, retail
// 0x002B6E8A (167 bytes; WB name). Both counts start at zero; for the
// region's owner they sum the two counts of every armory's upgrade.
void LivingWorldLogic::GetNumUpgradeableTroopsInRegionForPlayer(Rva003F287F *region, Int player, Int *countA, Int *countB)
{
	*countA = 0;
	*countB = 0;
	if (region->m_ownerPlayer != player)
		return;
	_STL::vector<const ModuleData *> armories;
	region->rva003F28DB(armories);
	for (UnsignedInt i = 0; i < armories.size(); ++i)
	{
		Rva002B6E8AUpgrade *upgrade = (Rva002B6E8AUpgrade *)((const Rva004E0632 *)armories[i])->rva004E0632();
		*countA += upgrade->count08();
		*countB += upgrade->count00();
	}
}

// The player's id at +0x14 and its armies at +0x1B8 (LivingWorldPlayer.cpp's
// m_armyVec), as EnforceArmyRegionOwnership reads them.
struct Rva002B4C35Player
{
	unsigned char m_pad00[0x14];
	Int m_id;						// +0x14
	unsigned char m_pad18[0x1b8 - 0x18];
	_STL::vector<LivingWorldArmy *> m_armies;		// +0x1B8
};

// The two callees, rowed and pinned under placeholder names: the unowned
// region hand-over 0x002B388D (rowed as a BFME 1 donor's
// Refresh0023FA80Primary::scheduleNullable, on this object with
// (region, player)) and the army's eviction 0x0031912E (pinned).
class Refresh0023FA80AI;
class Refresh0023FA80Object;
class Refresh0023FA80Primary
{
public:
	void scheduleNullable(Refresh0023FA80AI *ai, Refresh0023FA80Object *obj);	// 0x002B388D
};
class Rva0031912E
{
public:
	Int rva0031912E();					// 0x0031912E
};

// LivingWorldLogic::EnforceArmyRegionOwnership, retail 0x002B4C35 (184
// bytes; WB name). For every player's armies standing in a region: an
// unowned region is handed to the player, and an army in another player's
// region is moved out. Armies flagged at +0x74 are skipped.
void LivingWorldLogic::EnforceArmyRegionOwnership()
{
	for (UnsignedInt i = 0; i < m_players.size(); ++i)
	{
		Rva002B4C35Player *player = (Rva002B4C35Player *)m_players[i];
		_STL::vector<LivingWorldArmy *> &armies = player->m_armies;
		for (UnsignedInt j = 0; j < armies.size(); ++j)
		{
			LivingWorldArmy *army = armies[j];
			if (army->m_field74)
				continue;
			Rva003F287F *region = (Rva003F287F *)((Rva00318C79Owner *)army)->rva00318C32();
			if (region == 0)
				continue;
			if (region->m_ownerPlayer == -1)
				((Refresh0023FA80Primary *)this)->scheduleNullable((Refresh0023FA80AI *)region, (Refresh0023FA80Object *)player);
			else if (region->m_ownerPlayer != player->m_id)
				((Rva0031912E *)army)->rva0031912E();
		}
	}
}

// The active campaign's move vetting: slot +0x10 of the object the rowed
// lookup 0x003B8BAA returns.
class Rva002B27B5Campaign
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual Bool canArmyMoveTo(LivingWorldArmy *army, Rva00318C32Ret *target);	// +0x10
};

// Retail 0x002B27B5 (87 bytes; WorldBuilder leaves it unnamed, its callees
// are the army region getter, LivingWorldRegionManager::
// ValidateArmyRegionEntry, the rowed check 0x002B254F and the campaign
// lookup 0x003B8BAA; armyMoveRequest calls it): the region manager must
// allow the move from the army's region, and, when 0x002B254F holds, the
// active campaign has the last word.
Bool LivingWorldLogic::rva002B27B5(LivingWorldArmy *army, Rva00318C32Ret *target)
{
	Int result = m_field0B0->ValidateArmyRegionEntry(army, ((Rva00318C79Owner *)army)->rva00318C32(), target, 0, 0);
	Bool valid = result >= 0 && result <= 1;
	if (valid)
	{
		if ((unsigned char)((Rva002B254F *)this)->rva002B254F() != 0)
		{
			Rva002B27B5Campaign *campaign = (Rva002B27B5Campaign *)((Rva003B8BAA *)TheCampaignManager)->rva003B8BAA();
			return campaign->canArmyMoveTo(army, target);
		}
		return true;
	}
	return false;
}

// Retail 0x002B26D0 (50 bytes; WorldBuilder leaves it unnamed, its callees
// are the army region getter and LivingWorldArmy::initiateMove;
// armyMoveRequest calls it): moves an army to another region.
// ?LivingWorldLogic::rva002B26D0 present-unmatched
void LivingWorldLogic::rva002B26D0(LivingWorldArmy *army, Rva00318C32Ret *target, Rva002B2858Coord pos, Int flags)
{
	if (army == 0 || target == 0)
		return;
	if (((Rva00318C79Owner *)army)->rva00318C32() == target)
		return;
	army->initiateMove(*(const Coord2D *)&pos, target, flags);
}

// The rowed army check 0x002B280C (address-named) and the army's unnamed
// handler 0x00319831 (pinned) that 0x002B2834 forwards to.
struct Arg54;
class Rva002B280C
{
public:
	bool rva002B280C(Arg54 *army);				// 0x002B280C
};
class Rva00319831
{
public:
	void rva00319831(Int flags);				// 0x00319831
};

// Retail 0x002B2834 (36 bytes; WorldBuilder leaves it unnamed, its only
// callee is the army's 0x00319831; armyMoveRequest calls it): forwards the
// flags to an army that passes the rowed check 0x002B280C.
void LivingWorldLogic::rva002B2834(LivingWorldArmy *army, Int flags)
{
	if (army == 0)
		return;
	if (!((Rva002B280C *)this)->rva002B280C((Arg54 *)army))
		return;
	((Rva00319831 *)army)->rva00319831(flags);
}

// LivingWorldLogic::armyMoveRequest, retail 0x002B28B1 (142 bytes; WB name,
// asserts army and goalRegion lines 1988..1989). Only in turn phases 0 and
// 4: an army in no region is sent straight to the adjusted position; an army
// in a region must be allowed the move (0x002B27B5), is told the flags
// (0x002B2834), and is sent unless it already stands in the goal region.
// ?LivingWorldLogic::armyMoveRequest present-unmatched
void LivingWorldLogic::armyMoveRequest(LivingWorldArmy *army, Rva00318C32Ret *target, const Coord2D *pos, Int flags)
{
	if (m_turnPhase != 0 && m_turnPhase != 4)
		return;
	if (((Rva00318C79Owner *)army)->rva00318C32() == 0)
	{
		rva002B26D0(army, target, AdjustArmyMoveTargetPos(target, pos), flags);
	}
	else if (rva002B27B5(army, target))
	{
		rva002B2834(army, flags);
		if (((Rva00318C79Owner *)army)->rva00318C32() != target)
			rva002B26D0(army, target, AdjustArmyMoveTargetPos(target, pos), flags);
	}
}

// LivingWorldLogic::XferDelayedRegionVictories, retail 0x002B9BB7 (325
// bytes; WB name). Version 1..2: each victory moves as its player's id, the
// region id and (from version 2 on load) the flags; a loaded victory whose
// player is gone or whose region is unset is dropped.
void LivingWorldLogic::XferDelayedRegionVictories(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	xfer->xferVersion(version);
	if (xfer->IsLoading())
	{
		Int count;
		xfer->xferInt(count);
		for (Int i = 0; i < count; ++i)
		{
			Int playerID;
			XferLivingWorldPlayerID(xfer, &playerID);
			Rva002E2903Player *player = ((Rva002BA8F1Logic *)this)->find(playerID, 0);
			Int regionID;
			Rva003EFE82Get((Rva003EFE82Obj *)xfer, &regionID);
			UnsignedInt flags = 0;
			if (version.m_minimum >= 2)
				Rva002B24F0Get((Rva002B24F0Obj *)xfer, &flags);
			if (player != 0 && regionID != -1)
			{
				DelayedRegionVictory victory;
				victory.player = (Int)player;
				victory.regionID = regionID;
				victory.flags = flags;
				((_STL::vector<PrereqUnitRec> *)&m_delayedRegionVictories)->push_back(*(const PrereqUnitRec *)&victory);
			}
		}
	}
	else
	{
		Int count = m_delayedRegionVictories.size();
		xfer->xferInt(count);
		for (Int i = 0; i < count; ++i)
		{
			Int playerID = ((Rva002B4C35Player *)m_delayedRegionVictories[i].player)->m_id;
			XferLivingWorldPlayerID(xfer, &playerID);
			Int regionID = m_delayedRegionVictories[i].regionID;
			Rva003EFE82Get((Rva003EFE82Obj *)xfer, &regionID);
			UnsignedInt flags = m_delayedRegionVictories[i].flags;
			Rva002B24F0Get((Rva002B24F0Obj *)xfer, &flags);
		}
	}
}

// XferPlayers' collaborators: the player's constructor 0x002E277A (0x3C8
// bytes; pinned under an address name), its observer list at +0x04 (rowed
// append 0x005A0B4C), and this object's player observer base at +0x18, which
// retail reaches with the null-checked derived-to-base adjustment. The
// player vector's clear, reserve and push_back are the ICF-folded pointer
// instantiations rowed as vector<void*>::erase(first, last) 0x0031BD55 and
// vector<const ModuleData*>::reserve 0x002B712E and ::push_back 0x004DFCB0.
struct Rva002BA8F1Listener;
class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *listener);		// 0x005A0B4C
	unsigned char m_pad[0x14];
};
class Rva002E277A
{
public:
	Rva002E277A();						// 0x002E277A
	unsigned char m_pad000[0x4];
	Rva005A0B4CList m_observers;				// +0x04
	unsigned char m_pad018[0x3c8 - 0x18];
};
struct Rva002BAA3DBase18
{
	unsigned char m_pad00[0x18];
};
struct Rva002BA8F1Listener
{
	void *m_vtbl;
};
struct Rva002BAA3DLogic : public Rva002BAA3DBase18, public Rva002BA8F1Listener
{
};

// LivingWorldLogic::XferPlayers, retail 0x002BAA3D (365 bytes; WB name).
// Version 1: the players as snapshots, each new one built on load and
// observed by this object, then the local player's id (raw 4 bytes; -1 for
// none, not written in CRC mode).
void LivingWorldLogic::XferPlayers(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	xfer->xferVersion(version);
	if (xfer->IsLoading())
	{
		Int count;
		xfer->xferInt(count);
		((_STL::vector<void *> *)&m_players)->clear();
		((_STL::vector<const ModuleData *> *)&m_players)->reserve(count);
		for (Int i = 0; i < count; ++i)
		{
			Rva002E277A *player = new Rva002E277A;
			xfer->xferSnapshot(player);
			((_STL::vector<const ModuleData *> *)&m_players)->push_back(*(const ModuleData **)&player);
			player->m_observers.append((Rva002BA8F1Listener *)(Rva002BAA3DLogic *)this);
		}
		Int localPlayerID;
		xfer->XferRawBytes(&localPlayerID, 4);
		m_localPlayer = (LivingWorldPlayer *)((Rva002BA8F1Logic *)this)->find(localPlayerID, 0);
	}
	else
	{
		Int count = m_players.size();
		xfer->xferInt(count);
		for (Int i = 0; i < count; ++i)
			xfer->xferSnapshot(m_players[i]);
		if (!xfer->IsCRC())
		{
			Int id = m_localPlayer ? ((Rva002B4C35Player *)m_localPlayer)->m_id : -1;
			Int localPlayerID = id;
			xfer->XferRawBytes(&localPlayerID, 4);
		}
	}
}

// The active campaign's ownership sets (campaign +0x1C, reached through
// TheCampaignManager's campaign vector +0x14 at index +0x10 without a range
// check): the regions a player's base region brings (0x004FD699) and the
// award itself (0x004FCA11), both pinned under address names; and the
// region manager's region lookup by the player's base region name (+0x2C;
// rowed 0x002104B6).
class Rva002B7582Sets
{
public:
	void rva004FD699(void *baseRegion, _STL::vector<const ModuleData *> *regions);	// 0x004FD699
	void rva004FCA11(void *baseRegion, Rva002E2903Player *player);	// 0x004FCA11
};
struct Rva002B7582Campaign
{
	Rva002B7582Sets *GetOwnershipSets() const { return m_ownershipSets; }

	unsigned char m_pad00[0x1c];
	Rva002B7582Sets *m_ownershipSets;			// +0x1C
};
struct Rva002B7582CampaignManager
{
	Rva002B7582Campaign *GetCurrentCampaign() { return m_campaigns[m_campaignIndex]; }

	unsigned char m_pad00[0x10];
	Int m_campaignIndex;					// +0x10
	_STL::vector<Rva002B7582Campaign *> m_campaigns;	// +0x14
};
class Rva002104B6
{
public:
	void *rva002104B6(void *name);				// 0x002104B6
};

// LivingWorldLogic::AwardOwnershipSetsToPlayers, retail 0x002B7582 (269
// bytes; WB name, asserts player and baseRegion lines 1893..1896). Every
// player with a base region is handed the regions its ownership set brings,
// and the set is awarded.
void LivingWorldLogic::AwardOwnershipSetsToPlayers()
{
	Rva002B7582Sets *sets = ((Rva002B7582CampaignManager *)TheCampaignManager)->GetCurrentCampaign()->GetOwnershipSets();
	if (sets == 0)
		return;
	_STL::vector<const ModuleData *> regions;
	for (UnsignedInt i = 0; i < m_players.size(); ++i)
	{
		Rva002E2903Player *player = (Rva002E2903Player *)m_players[i];
		if (player == 0)
			continue;
		void *baseRegion = ((Rva002104B6 *)m_field0B0)->rva002104B6((char *)player + 0x2c);
		if (baseRegion == 0)
			continue;
		((_STL::vector<void *> *)&regions)->clear();
		sets->rva004FD699(baseRegion, &regions);
		for (UnsignedInt j = 0; j < regions.size(); ++j)
		{
			const ModuleData *region = regions[j];
			((Refresh0023FA80Primary *)this)->scheduleNullable((Refresh0023FA80AI *)region, (Refresh0023FA80Object *)player);
		}
		sets->rva004FCA11(baseRegion, player);
	}
}

// Two lookups callers reach through the opaque Rva002BA8F1Logic view of this
// class (rowed under that view's names):
// 0x002B2579 23B: null for id 0, else the rowed 0x0020EEF4 search on the
// container held at +0xB0 (tail call). Callers: the audio event owner-position
// reader, the 0x0040C351 ctor, the 0x005F88D6 getter.
// 0x002B2B2D 18B: the pinned region-manager lookup 0x0020EAF6 on that same
// +0xB0 object, keyed by the +0xB8 field.
struct Rva002B2579Result;
struct Rva002B3740Item;
class Rva0020EEF4Outer
{
public:
	int rva0020EEF4(int id);
};

Rva002B2579Result *Rva002BA8F1Logic::rva002B2579(int id)
{
	if (id == 0)
		return 0;
	return (Rva002B2579Result *)((Rva0020EEF4Outer *)m_containerB0)->rva0020EEF4(id);
}

Rva002B3740Item *Rva002BA8F1Logic::rva002B2B2D()
{
	return (Rva002B3740Item *)((LivingWorldRegionManager *)m_containerB0)->rva0020EAF6(m_keyB8);
}

// LivingWorldLogic::CreateEmptyGarrisonArmy, retail 0x002B6A04 (158 bytes;
// WB name, asserts the spawned garrison and its summary lines 4935..4938).
// The player's army already in the region is returned; otherwise an empty
// army is spawned at the region's garrison spot under the player template's
// names.
LivingWorldArmy *LivingWorldLogic::CreateEmptyGarrisonArmy(Rva002B6A04Player *player, LivingWorldRegion *region)
{
	LivingWorldArmy *army = (LivingWorldArmy *)rva002B4948(player, region, 0);
	if (army == 0)
	{
		Rva004E3184 spawn(0);
		spawn.m_flag54 = false;
		spawn.m_name.set(player->m_template->m_name24);
		Rva003F0F13Elem spot;
		region->GetGarrisonArmyPlacementSpot(&spot);
		spawn.m_pos = spot;
		army = spawnArmy(&spawn, player, true);
		Rva002B6A04Template *playerTemplate = player->m_template;
		Rva002B6A04Summary *summary = (Rva002B6A04Summary *)army->m_summary;
		summary->m_name64 = playerTemplate->m_name34;
	}
	return army;
}

// The player relations rowed under placeholder names: 0x002E071E compares
// two players (WB asserts !newOwner->IsAllyOf(oldOwnerID) around it) and
// 0x002E0BC0 tests a player id; 0x002B8A9F queues an army for destruction
// (the +0x118 list processArmyDestroyList drains).
class Rva002E071E
{
public:
	bool rva002E071E(const Rva002E071E *other) const;	// 0x002E071E
	Int rva002E0BC0(Int playerID);				// 0x002E0BC0
};
class Rva002B8A9F
{
public:
	void rva002B8A9F(ModuleData *army);			// 0x002B8A9F
};

// LivingWorldLogic::OnRegionChangedOwnership, retail 0x002BA82B (198 bytes;
// WB name, asserts lines 4865..4871; entered through the region observer
// base at +0x14). The new owner's allies get an empty garrison army in the
// region; unless the new owner sides with the old one, the armies of
// players not allied to the new owner there are queued for destruction.
void LivingWorldLogic::OnRegionChangedOwnership(LivingWorldRegion *region, Int oldOwnerID, Int newOwnerID)
{
	const Rva002E071E *newOwner = (const Rva002E071E *)((Rva002BA8F1Logic *)this)->find(newOwnerID, 0);
	if (newOwnerID != -1)
	{
		for (UnsignedInt i = 0; i < m_players.size(); ++i)
		{
			LivingWorldPlayer *player = m_players[i];
			if (newOwner->rva002E071E((const Rva002E071E *)player))
				CreateEmptyGarrisonArmy((Rva002B6A04Player *)player, region);
		}
	}
	if (oldOwnerID != -1)
	{
		if (newOwner != 0 && (unsigned char)((Rva002E071E *)newOwner)->rva002E0BC0(oldOwnerID) != 0)
			return;
		for (UnsignedInt i = 0; i < m_players.size(); ++i)
		{
			LivingWorldPlayer *player = m_players[i];
			if (newOwner != 0 && !newOwner->rva002E071E((const Rva002E071E *)player))
			{
				void *army = rva002B4948(player, region, 0);
				if (army != 0)
					((Rva002B8A9F *)this)->rva002B8A9F((ModuleData *)army);
			}
		}
	}
}

// spawnBuilding's request: the player's name at +0x04, the building
// template token at +0x08, the region's name at +0x0C and whether the
// building is captured at +0x10.
class AsciiString;
struct Rva002B99F8Request
{
	void *m_vtbl;
	unsigned char m_player[4];				// +0x04, AsciiString
	Int m_templateToken;					// +0x08
	unsigned char m_region[4];				// +0x0C, AsciiString
	Bool m_captured;					// +0x10
};

// TheLivingWorldBuildingTemplateStore (0x009FF09C) and its token lookup
// 0x002B931C, pinned under these names; the player lookup by name (rowed
// 0x002B6AEC); and the region's building slot calls, pinned under address
// names (0x003F0588 the free slot, 0x003F2A8C the owner change, 0x003EFE72
// the captured placement, thiscall spelling of its stdcall row) except
// WorldBuilder's LivingWorldRegion::BuildBuilding (0x003F1C56); see the
// LivingWorldRegion view above.
struct Rva0059E647Factory
{
	Rva0059E647Entry *Lookup(Int *token);			// 0x002B931C
};
extern Rva0059E647Factory *g_rva0059E647Factory;

// LivingWorldLogic::spawnBuilding, retail 0x002B99F8 (141 bytes; WB name,
// asserts region and buildingTemplate lines 1095..1098). The building goes
// into the region's free slot: a captured one first hands the region to the
// player, an ordinary one is built.
void LivingWorldLogic::spawnBuilding(const Rva002B99F8Request *request)
{
	Rva002104B6 *regions = (Rva002104B6 *)TheLivingWorldLogic->m_field0B0;
	LivingWorldRegion *region = (LivingWorldRegion *)regions->rva002104B6((void *)request->m_region);
	Rva0059E647Entry *buildingTemplate = g_rva0059E647Factory->Lookup((Int *)&request->m_templateToken);
	Rva002B4C35Player *player = (Rva002B4C35Player *)((Rva002BA8F1Logic *)TheLivingWorldLogic)->find(*(const AsciiString *)request->m_player, 0);
	void *slot = region->rva003F0588();
	if (slot == 0)
		return;
	if (request->m_captured)
	{
		if (region->m_ownerPlayer != player->m_id)
			region->rva003F2A8C(player->m_id);
		region->rva003EFE72(slot, buildingTemplate);
	}
	else
	{
		region->BuildBuilding(slot, buildingTemplate);
	}
}

// LivingWorldLogic::AdjustArmyMoveTargetPos, retail 0x002B2858 (89 bytes;
// WB name, logs when the point lies outside the target region): a position
// outside the target region is replaced by the region's center point.
Rva002B2858Coord LivingWorldLogic::AdjustArmyMoveTargetPos(Rva00318C32Ret *target, const Coord2D *pos)
{
	Rva002B2858Coord adjusted;
	if (m_field0B0->rva0020FAEA(pos, target) != target)
		m_field0B0->GetRegionCenterPoint((Rva0020E89C *)target, (Coord2D *)&adjusted);
	else
	{
		adjusted.x = pos->x;
		adjusted.y = pos->y;
	}
	return adjusted;
}

// A region award dispute (WorldBuilder RegionAwardDispute): settled at
// +0x1C; GetResolvableBy (0x004FBED6, pinned under its WorldBuilder name)
// names the player id that can settle it.
class RegionAwardDispute
{
public:
	Int GetResolvableBy();					// 0x004FBED6

	unsigned char m_pad00[0x1c];
	Bool m_resolved;					// +0x1C
};

// Retail 0x002B5CBB (64 bytes; WorldBuilder leaves it unnamed, its callees
// are the map iterator step and RegionAwardDispute::GetResolvableBy;
// CheckTurnPhaseTransitions calls it): whether an unsettled region award
// dispute (+0x130) waits on the player.
Bool LivingWorldLogic::rva002B5CBB(const Rva002B4C35Player *player)
{
	_STL::map<Int, RegionAwardDispute *>::iterator it = m_regionAwardDisputes.begin();
	_STL::map<Int, RegionAwardDispute *>::iterator end = m_regionAwardDisputes.end();
	for (; it != end; ++it)
	{
		RegionAwardDispute *dispute = (*it).second;
		if (!dispute->m_resolved)
		{
			Int playerID = player->m_id;
			if (dispute->GetResolvableBy() == playerID)
				return true;
		}
	}
	return false;
}

// GameLogic_tacticalBattleComplete's collaborators. The battle (current one
// from the region manager, pinned 0x0020E6B7): its side at +0x38 (-1 none),
// the 0x1C-byte side table at +0x18 and the rowed or pinned per-side,
// per-army and per-unit getters (0x003F4DAE army count, 0x003F468D army,
// 0x003F4DCA unit count, 0x003F48FE unit, GetTeamNumberForSide 0x003F458A).
// The unit: its template name at +0x18 (rowed StringBase isEmpty
// 0x00001E2F) and two unnamed calls pinned under address names (0x003190A5
// a test, 0x00319A12 its action). ConsumeGarrisonUnitsFromRTS (0x002BBD52)
// and OnBattleComplete (0x002BAF7E) are pinned under their WorldBuilder
// names.
class Rva003F468D;
class LivingWorldBattle
{
public:
	Int GetTeamNumberForSide(Int side);			// 0x003F458A
	Int rva003F48FE(Int side, Int army, Int unit);		// 0x003F48FE
	Int GetRetreatedPlayerCount(Int side);			// 0x003F46A8
	Int GetRetreatedPlayerID(Int side, Int index);		// 0x003F46C1
	Int rva003F47E6(Int side);				// 0x003F47E6
	Int rva003F459A();					// 0x003F459A, total army count (pinned)
	void *rva003F4ABB(Int side, Int army);			// 0x003F4ABB, the army object or null (pinned)
	void AddArmy(Int player, void *army);			// 0x003F6DF9 (WorldBuilder name, pinned)

	unsigned char m_pad00[0x18];
	struct Rva002BC1DASide { unsigned char m_data[0x1c]; } *m_sides;	// +0x18
	Rva002BC1DASide *m_sidesEnd;				// +0x1C
	unsigned char m_pad20[0x24 - 0x20];
	Rva003F287F *m_region;					// +0x24
	unsigned char m_pad28[0x38 - 0x28];
	Int m_side;						// +0x38, the winning side
};
class Rva003F468D
{
public:
	Int rva003F468D(Int side, Int army);			// 0x003F468D
	Int rva003F4DAE(Int side);				// 0x003F4DAE
};
class Rva003F4DCA
{
public:
	Int rva003F4DCA(Int side, Int army);			// 0x003F4DCA
};
class Rva0020E6B7RegionManager
{
public:
	LivingWorldBattle *rva0020E6B7();			// 0x0020E6B7
};
struct Rva002BC1DAArmy
{
	unsigned char m_pad00[0x34];
	Int m_team;						// +0x34
};
class Rva002BC1DAUnit
{
public:
	Bool rva003190A5();					// 0x003190A5
	void rva00319A12();					// 0x00319A12

	unsigned char m_pad00[0x18];
	StringBase<char> m_templateName;			// +0x18
};
void ConsumeGarrisonUnitsFromRTS(Rva002BC1DAUnit *unit, Rva002BC1DAArmy *army, LivingWorldBattle *battle);	// 0x002BBD52

// LivingWorldLogic::GameLogic_tacticalBattleComplete, retail 0x002BC1DA (351
// bytes; WB name). With a current battle that has a side and a battle
// region: every unit of every army of every side is settled (units of the
// winning team with no template feed the RTS garrison; losing units with a
// template are kept for the +0x10C list, the rest are destroyed); then the
// battle completes and the battle listeners hear of it.
void LivingWorldLogic::GameLogic_tacticalBattleComplete()
{
	void *region = ((Rva002BA8F1Logic *)this)->rva002B2B2D();
	m_fieldB6 = true;
	LivingWorldBattle *battle = ((Rva0020E6B7RegionManager *)m_field0B0)->rva0020E6B7();
	if (battle != 0 && battle->m_side != -1 && region != 0)
	{
		Int team = battle->GetTeamNumberForSide(battle->m_side);
		Int sideCount = battle->m_sidesEnd - battle->m_sides;
		for (Int side = 0; side < sideCount; ++side)
		{
			Int armyCount = ((Rva003F468D *)battle)->rva003F4DAE(side);
			for (Int a = 0; a < armyCount; ++a)
			{
				Rva002BC1DAArmy *army = (Rva002BC1DAArmy *)((Rva003F468D *)battle)->rva003F468D(side, a);
				Int unitCount = ((Rva003F4DCA *)battle)->rva003F4DCA(side, a);
				for (Int u = 0; u < unitCount; ++u)
				{
					Rva002BC1DAUnit *unit = (Rva002BC1DAUnit *)battle->rva003F48FE(side, a, u);
					if (army->m_team != team)
					{
						if (!unit->m_templateName.isEmpty())
						{
							if (unit->rva003190A5())
								unit->rva00319A12();
							((_STL::vector<const ModuleData *> *)&m_field10C)->push_back((const ModuleData *)unit);
						}
						else
						{
							((Rva002B8A9F *)this)->rva002B8A9F((ModuleData *)unit);
						}
					}
					else if (unit->m_templateName.isEmpty())
					{
						ConsumeGarrisonUnitsFromRTS(unit, army, battle);
					}
				}
			}
		}
		OnBattleComplete(battle);
		m_battleListeners.forEach(&Rva002B616FListener::onTurnChanged, this, (int)battle);
	}
	m_fieldB8 = -1;
}

// OnBattleComplete's region manager calls, pinned under address names
// (0x0020FB8B ends the battle, WorldBuilder LivingWorldRegionManager::
// UpdateBattleMarkers 0x0020EBA0 under its name), the unnamed contested
// award 0x002B9A90 and the battle cleanup 0x002B37FF (address names).
struct Rva002BAF7EArmy
{
	unsigned char m_pad00[0x14];
	Int m_owner;						// +0x14
};
struct Rva002BAF7EWinner
{
	unsigned char m_pad00[0x34];
	Int m_team;						// +0x34
};

// LivingWorldLogic::OnBattleComplete, retail 0x002BAF7E (481 bytes; WB
// name). With a winning side: unless the region's owner is on the winning
// team, the award flags record the owner (1), armies of the other sides
// that are (2) or are not (4) the owner's, and players that retreated who
// are (8) or are not (0x10) the owner; one winning army takes the region
// (delayed victory), several dispute it (0x20; settled by the AI unless the
// battle says otherwise). The battle is then cleaned up and its markers
// refreshed.
void LivingWorldLogic::OnBattleComplete(LivingWorldBattle *battle)
{
	m_field0B0->rva0020FB8B(battle);
	Int winner = battle->m_side;
	if (winner == -1)
		return;
	UnsignedInt flags = 0;
	Rva003F287F *region = battle->m_region;
	if (region->m_ownerPlayer != -1)
	{
		flags = 1;
		Rva002BAF7EWinner *owner = (Rva002BAF7EWinner *)((Rva002BA8F1Logic *)this)->find(region->m_ownerPlayer, 0);
		if (owner->m_team == battle->GetTeamNumberForSide(winner))
			goto done;
	}
	{
		Int sideCount = battle->m_sidesEnd - battle->m_sides;
		for (Int side = 0; side < sideCount; ++side)
		{
			if (side == battle->m_side)
				continue;
			Int i = 0;
			Int armyCount = ((Rva003F468D *)battle)->rva003F4DAE(side);
			for (; i < armyCount; ++i)
			{
				if (((Rva002BAF7EArmy *)((Rva003F468D *)battle)->rva003F468D(side, i))->m_owner == region->m_ownerPlayer)
					flags |= 2;
				else
					flags |= 4;
			}
			i = 0;
			Int retreatedCount = battle->GetRetreatedPlayerCount(side);
			for (; i < retreatedCount; ++i)
			{
				Int owner = region->m_ownerPlayer;
				if (battle->GetRetreatedPlayerID(side, i) == owner)
					flags |= 8;
				else
					flags |= 0x10;
			}
		}
		UnsignedInt winnerCount = ((Rva003F468D *)battle)->rva003F4DAE(winner);
		if ((Int)winnerCount > 1)
		{
			_STL::vector<const ModuleData *> players;
			players.reserve(winnerCount);
			for (UnsignedInt w = 0; w < winnerCount; ++w)
				players.push_back((const ModuleData *)((Rva003F468D *)battle)->rva003F468D(winner, w));
			flags |= 0x20;
			const _STL::vector<Int> &playerIDs = *(const _STL::vector<Int> *)&players;
			if (battle->rva003F47E6(winner) == 0)
			{
				Int regionID = (Int)battle->m_region;
				LetAIResolveRegionAwardDispute(regionID, playerIDs, flags);
			}
			else
			{
				Int regionID = (Int)battle->m_region;
				rva002B9A90(regionID, playerIDs, flags);
			}
		}
		else
		{
			Int army = ((Rva003F468D *)battle)->rva003F468D(winner, 0);
			AddDelayedRegionVictory(region, army, flags);
		}
	}
done:
	rva002B37FF(battle);
	m_field0B0->UpdateBattleMarkers();
}

// PrepareBattleForLoading's views: the campaign's +0x38 spacing (current
// campaign of TheCampaignManager, or none); an army's summary at +0x78 with
// its battle state word at +0x2C, offset setter 0x0040CA3A and engage
// 0x0040C985 (rowed under the placeholder Rva0040C985; WorldBuilder
// ArmySummary::EngageBattle); and the army's placement in the region
// (rowed 0x00318BA5).
struct Rva002B792ECampaign
{
	unsigned char m_pad00[0x38];
	Int m_spacing;						// +0x38
};
struct Rva002B792ECampaignManager
{
	Rva002B792ECampaign *GetCurrentCampaign() { return m_campaigns[m_campaignIndex]; }

	unsigned char m_pad00[0x10];
	Int m_campaignIndex;					// +0x10
	_STL::vector<Rva002B792ECampaign *> m_campaigns;	// +0x14
};
class Rva0040C985
{
public:
	void rva0040C985(Int arg);				// 0x0040C985
	void rva0040CA3A(Int offset);				// 0x0040CA3A

	unsigned char m_pad00[0x2c];
	Int m_battleState;					// +0x2C
};
struct Rva002B792EArmy
{
	unsigned char m_pad00[0x18];
	StringBase<char> m_templateName;			// +0x18
	unsigned char m_pad1C[0x78 - 0x1c];
	Rva0040C985 *m_summary;					// +0x78
};
class Rva00318BA5
{
public:
	void rva00318BA5(LivingWorldRegion *region);		// 0x00318BA5
};

// LivingWorldLogic::PrepareBattleForLoading, retail 0x002B792E (503 bytes;
// WB name). Every side's armies are collected (an absent one is replaced by
// an empty garrison army joined to the battle); then every templated unit
// past the first of an army is engaged at the campaign's spacing while the
// first (or all, without spacing) is placed in the battle region, and
// untemplated units are marked out (state 4).
void LivingWorldLogic::PrepareBattleForLoading(LivingWorldBattle *battle)
{
	_STL::vector<const ModuleData *> armies;
	armies.reserve(battle->rva003F459A());
	Int k = 0;
	for (Int side = 0; side < battle->m_sidesEnd - battle->m_sides; ++side)
	{
		for (Int a = 0; a < ((Rva003F468D *)battle)->rva003F4DAE(side); ++a, ++k)
		{
			void *army = battle->rva003F4ABB(side, a);
			if (army == 0)
			{
				Int player = ((Rva003F468D *)battle)->rva003F468D(side, a);
				army = CreateEmptyGarrisonArmy((Rva002B6A04Player *)player, (LivingWorldRegion *)battle->m_region);
				if (army != 0)
					battle->AddArmy(player, army);
			}
			armies.begin()[k] = (const ModuleData *)army;
		}
	}
	Int spacing = 0;
	if (TheCampaignManager != 0)
		spacing = ((Rva002B792ECampaignManager *)TheCampaignManager)->GetCurrentCampaign()->m_spacing;
	k = 0;
	for (Int side = 0; side < battle->m_sidesEnd - battle->m_sides; ++side)
	{
		Int armyCount = ((Rva003F468D *)battle)->rva003F4DAE(side);
		for (Int a = 0; a < armyCount; ++a, ++k)
		{
			Int engaged = 0;
			Int unitCount = ((Rva003F4DCA *)battle)->rva003F4DCA(side, a);
			Int u = 0;
			if (u < unitCount)
			{
				Int offset = 0;
				do
				{
					Rva002B792EArmy *unit = (Rva002B792EArmy *)battle->rva003F48FE(side, a, u);
					if (!unit->m_templateName.isEmpty())
					{
						if (engaged > 0 && spacing > 0)
						{
							unit->m_summary->rva0040CA3A(offset);
							Rva0040C985 *summary = unit->m_summary;
							summary->rva0040C985(0);
						}
						else
						{
							Rva0040C985 *summary = unit->m_summary;
							summary->m_battleState = 4;
							((Rva00318BA5 *)armies[k])->rva00318BA5((LivingWorldRegion *)battle->m_region);
						}
						++engaged;
						offset += spacing;
					}
					else
					{
						Rva0040C985 *summary = unit->m_summary;
						summary->m_battleState = 4;
					}
				} while (++u < unitCount);
			}
		}
	}
}

// Native 0x002BD544..0x002BD603 (191 bytes). WB 0x00D7DD50 carries
// the same reset sequence and receiver calls; its original method name is
// unknown. The offsets, argument ABI and dispatch slots below are native
// facts. No donor layout or method name is inferred from the byte match.
class GameLogic; extern GameLogic *TheGameLogic;
class Rva0023D2D8DwordClearer { public: void clear(); };
class Rva00210C66CmpBoolField { public: Bool get() const; };
void Rva00437E9C(Int);
class BfmeAptWindowManager; extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class Rva00222A8BTarget { public: void rva00222F55(Bool); };
class Rva002BBBE7 { public: void rva002BC39D(); };
extern UnsignedInt g_Va00E04544;
class Rva002D3627Host; extern Rva002D3627Host *g_00DFEF18;
class LivingWorldResetDispatch
{
public:
    virtual void slot00(); virtual void slot04();
    virtual void slot08(); virtual void slot0C();
    virtual void slot10(); virtual void slot14();
    virtual void slot18(); virtual void slot1C();
    virtual void slot20(); virtual void slot24();
    virtual void slot28(); virtual void slot2C();
    virtual void slot30(); virtual void slot34();
    virtual void slot38(); virtual void slot3C();
    virtual void slot40(); virtual void slot44();
    virtual void slot48(); virtual void slot4C(Bool, Bool);
};
void HideControlBar(Bool);
class Rva0020EE29 { public: void rva0020F483(); };
class Rva002B6151Listener { public: virtual void notify(void *); };
class Rva002B6151List
{
public:
    void forEach(void (Rva002B6151Listener::*notify)(void *), void *arg);
};
struct TreeHintRef00217D4C;
class Rva001FF3A9
{
public:
    void rva001FF3A9(const TreeHintRef00217D4C &);
};
// The already-pinned 4-byte forwarder at 0x001FF3A9 dispatches slot zero
// without inspecting its stack argument; reuse the established call view.
// ?LivingWorldLogic::rva002BD544 present-unmatched
void LivingWorldLogic::rva002BD544(Int campaign)
{
    ((Rva0023D2D8DwordClearer *)TheGameLogic)->clear();
    if (((Rva00210C66CmpBoolField *)TheGameLogic)->get())
    {
        Rva00437E9C(1);
        ((Rva00222A8BTarget *)g_bfmeAptWindowManager)->rva00222F55(false);
    }
    ((Rva002BBBE7 *)&g_Va00E04544)->rva002BC39D();
    ((LivingWorldResetDispatch *)g_00DFEF18)->slot1C();
    ((LivingWorldResetDispatch *)g_00DFEF18)->slot4C(true, true);
    HideControlBar(true);
    slot04();
    rva002B84CD(campaign);
    rva002B47C3();
    ((_STL::_List_base<UnicodeString, _STL::allocator<UnicodeString> > *)((char *)this + 0xf0))->clear();
    ((Rva0020EE29 *)m_field0B0)->rva0020F483();
    m_turnPhase = 0;
    m_fieldF8 = -1;
    ((Rva002B9099 *)&m_autoBattleResolver)->clear();
    CheckTurnPhaseTransitions();
    ((Rva002B6151List *)((char *)this + 0x4c))->forEach(
        (void (Rva002B6151Listener::*)(void *))&Rva001FF3A9::rva001FF3A9, this);
}
