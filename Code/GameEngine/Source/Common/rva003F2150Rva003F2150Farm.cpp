// ?rva003F2150@LivingWorldRegion@@QAEXPAVRva003F7BB4@@@Z
// ?rva003F2150@LivingWorldRegion@@QAEXPAVRva003F7BB4@@@Z
// Whole home TU Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldRegion.cpp with the body appended.
// cl: /O1 /EHsc /MD /arch:SSE /ICode/Libraries/Include/Lib /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include "Coord2D.h"
#include "Coord3D.h"
#include "ascii_string.h"

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
}
// LivingWorldRegion.cpp -- LivingWorldRegion queries recovered from
// WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names each
// function and the member m_buildPlots at +0x170; retail supplies the bytes.
//
// Layout (target evidence): owner player id at +0x13C (-1 when unowned),
// m_buildPlots (vector of plot pointers) at +0x170/+0x174; a plot's building
// is at +0x20 with a flag at +0x34 that hides it. The living-world logic
// global (0x00DFEF10) resolves player ids through its rowed find (0x002B51F8);
// the player's team id is at +0x34.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class CreateAHeroData;
class Xfer;
class ModuleData;
enum ScienceType { RegionOpaqueScienceValue=0 };
// Native scalar-vector cleanup uses the rowed game-memory free wrapper.
void __cdecl Rva00030830GameFree(void *);
namespace _STL {
template <> inline _Vector_base<ScienceType, allocator<ScienceType> >::~_Vector_base()
{ if (_M_start) Rva00030830GameFree(_M_start); }
}
// WB DoXfer treats each 12-byte hero slot as an army-vector. The existing
// rowed transfer helper retains its neutral ModuleData pointer element ABI.
struct RegionHeroSlot { _STL::vector<const ModuleData *> armies; };
class LivingWorldBuilding;

class LivingWorldBattle;
class LivingWorldRegion;
struct LivingWorldBuildPlot
{
	LivingWorldBuildPlot(Int id, LivingWorldRegion *region, const Coord2D &position);
    Bool IsOccupied() const { return m_building != 0; }
    Bool HasBuilding() const { return m_building != 0 && !m_hidden; }
    Bool HasHiddenBuilding() const { return m_hidden && m_building != 0; }

	unsigned char m_pad00[0x18];
    Int m_key18;
    unsigned char m_pad1C[4];
	LivingWorldBuilding *m_building;	// +0x20
	unsigned char m_pad24[0x34 - 0x24];
	Bool m_hidden;				// +0x34
};

typedef _STL::vector<LivingWorldBuildPlot *> BuildPlotVector;

class Rva002E2903Player
{
public:
	unsigned char m_pad00[0x14];
	Int m_playerID;				// +0x14
	unsigned char m_pad18[0x34 - 0x18];
	Int m_teamID;				// +0x34
	unsigned char m_pad38[0x40 - 0x38];
	Int m_score;				// +0x40
	Int getScore() const { return m_score; }
};

// The unit being spawned; its command-point cost comes from 0x004E1755.
#include "../../Include/Common/SpawnArmy.h"

#include "../../Include/GameLogic/Rva002BA8F1Logic.h"
#include "../../Include/GameLogic/LivingWorldBuilding.h"

class Rva00318C32Ret;
class Rva0020E89C;
struct Pair8;
#include "../../Include/GameLogic/LivingWorldRegionManager.h"

// The rowed 0x20FAEA finder (Rva0020EE29 view) and the rowed 0x3F3B28
// vector-resize owner (Rva003F3AB5 view) spellings.
#include "../../Include/GameLogic/Rva0020EE29.h"
#include "../../Include/Common/Rva003F3AB5.h"
#include "../../Include/GameLogic/LivingWorldLogic.h"

extern LivingWorldLogic *TheLivingWorldLogic;

// Native3F0F48/91 and WB103E4A0 preserve a nested12-byte range of
// pointer slots and erase the first matching pointer through the owned
// void-pointer vector erase1FF51F. Original element types remain unknown.
struct PlacementSlot {void **first,**finish,**end;};
struct PlacementRange {PlacementSlot *first,*finish,*end;};
class LivingWorldRegion
{
	friend class Rva003F2A8C;
public:
	void CreateBuildPlots();
    void rva003F0F48(PlacementRange *,void *);
    void rva003F0FA3(void *);
    void PrepareSkirmishOpponents(LivingWorldBattle *battle);
    Bool DebugValidatePlacementSpot(const Coord2D &spot,Coord2D *out,const char *kind);
    void DoXfer(Xfer *);
    Bool IsOwnedByTeam(Int teamID) const;
	Bool CanSpawnUnitWithinCPLimit(SpawnArmy *unit) const;
	Bool rva003F0201(SpawnArmy *unit) const;
	LivingWorldBuilding *GetBuildingByIndex(Int index) const;
	Int rva003F05CE();
	void *rva003F0588();
	Int rva003F1053();
	Int rva003F0614(CreateAHeroData *key) const;
	Int rva003F066B(CreateAHeroData *key) const;
	Int rva003F06C2(CreateAHeroData *key) const;
    LivingWorldBuildPlot *rva003F088C(Int key) const;
    void rva003F2150(class Rva003F7BB4 *bonus);
    Int getBonusPercent9C() const { return m_bonusPercent9C; }
    Int getOwnerPlayerID() const { return m_ownerPlayerID; }
    Int getBonusPercentA0() const { return m_bonusPercentA0; }
    Int getBonusPercentA4() const { return m_bonusPercentA4; }

private:
	Int rva003EFDB3(Rva002E2903Player *owner) const;	// 0x003EFDB3, command points in use
	Int rva003EFD6F(Rva002E2903Player *owner) const;	// 0x003EFD6F, command-point limit
	Int usedCommandPoints(Rva002E2903Player *owner) const { return rva003EFDB3(owner); }

	unsigned char m_pad00[0x14];
    AsciiString m_name;
    char m_pad18[0x9c-0x18];
    Int m_bonusPercent9C, m_bonusPercentA0, m_bonusPercentA4; // +0x9C..+0xA4
    char m_padA8[0xa9-0xa8];
    bool m_reservedA9;
    char m_padAA[0xfc-0xaa];
    _STL::vector<Coord2D> m_plotPositions;
    Int m_limit108;
    Int m_limit10C;
    unsigned char m_pad110[0x11c-0x110];
    bool m_ownerBuildsArmies;	// +0x11C
    unsigned char m_pad11D[0x12c-0x11d];
    int m_regionID;
    int unknown130;
    int value134,value138;
	Int m_ownerPlayerID;			// +0x13C
	int m_player140;
    Coord2D m_position;
    int value14C,value150,value154;
    _STL::vector<ScienceType> values158,values164;
	BuildPlotVector m_buildPlots;
    LivingWorldBuildPlot *m_plotIndex;
    _STL::vector<RegionHeroSlot> m_heroSlots;
    char m_unknown18C[0x1a0-0x18c];
    bool flag1A0,flag1A1,flag1A2;
    bool m_plotFlag;
};

// The LivingWorldRegion methods and helper owners this unit used to copy are rowed
// in GameLogic/System/LivingWorld/LivingWorldRegion.cpp; this unit owns only
// rva003F2150 and declares the rest, so the copies no longer duplicate them.
// WB 103CED0 and native 0x003F3B4F..0x003F3BFF (176B, RET0), the reset half of
// DoXfer's hero-slot load: size the +0x180 and +0x18C hero-slot vectors to the
// +0xE4 and +0xF0 position counts (rowed resize 0x003F3B28) and empty every
// slot's army vector (the folded pointer-vector erase 0x0031BD55). Callers
// 0x003F3F27/0x003F3F03 and DoXfer reach it under this view's pinned spelling.
// 0x003F2106 is rowed as Rva003F2106::rva003F2106 (Rva002B7B71DeleteAll.cpp).
#include "../../Include/Common/Rva003F2106.h"
int Rva003F1E2EHook(int,int);
class GameSlot;
// PrepareSkirmishOpponents reads native VA E02EF0, the existing owned
// TheSkirmishGameInfo global. TheGameInfo is a different pointer at E02EEC.
class SkirmishGameInfo; extern SkirmishGameInfo *TheSkirmishGameInfo;
class LivingWorldBattle { public: bool rva003F486C(int); };
struct Rva003EFDDBOut;
// 0x003F0E8A..0x003F0F13: thiscall, index and output arguments, ret 8.
// Target evidence proves the pair vector at +0x74/+0x78, the +0xB0
// singleton helper and both call targets. The receiver's identity remains
// uncertain, so retain an address-derived class and method name.
struct Pair8
{
	Pair8 &operator+=(const Pair8 &other) { x += other.x; y += other.y; return *this; }
	float x;
	float y;
};

struct RegionXferVersionFields { unsigned char minimum,current; };
union RegionXferVersion { RegionXferVersionFields fields; unsigned value; };
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
class Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../Include/Common/BfmeXfer.h"
struct Rva003EFE82Obj;
int Rva003EFE82Get(Rva003EFE82Obj *,void *);
void XferLivingWorldPlayerID(Xfer *,int *);
Xfer *Rva003F2394Xfer(Xfer *,_STL::vector<ScienceType> *);
class Rva004E075FObj;
int Rva004E075FGet(Rva004E075FObj *,int);
class Rva003F3B28View { public: void rva003F3B28(int); };
// Native construction tracks an eight-byte zero coordinate temporary in the
// EH bitmap and then clears its bit without a cleanup call. Keep that lifetime
// here while using the canonical Coord2D layout and plot-constructor ABI.
// The region's ownership listeners, told (region, old owner, new owner)
// through their slot 1 (vcall thunk 0x005CB260) by the rowed walk
// 0x003F1A03; a plot's rowed owner setter 0x004FC176 and the region's
// rowed 0x003F1AFF take the new owner. Address-derived names.
class Rva003F119CListener
{
public:
	virtual void slot00();
	virtual void onOwnerChanged(void *region, Int oldOwner, Int newOwner);	// +0x04
};
// Retail 0x003F2A8C, 127 bytes (RET 4; callers RemovePlayer, spawnBuilding,
// 0x0020F832 and 0x003F300A): the region's owner change. Unless the owner
// is unchanged it notifies the listeners, hands each build plot the new
// owner, clears the region (0x003F2106), its +0x17C plot index and +0x1A3
// flag, applies the owner (0x003F1AFF), then rebuilds the plots for a real
// owner or clears again for none (-1).
#include "../../Include/GameLogic/Rva003F2A8C.h"

// Native 2B3769..2B37B4 RET4: the rva003F088C search shape over another
// owner's pointer vector at +0xBC, matching the entry's +0x08 id. No direct
// caller; owner and entry types unknown (address-derived names).
// ?rva003F2150@LivingWorldRegion@@QAEXPAVRva003F7BB4@@@Z, retail 0x003F2150
// (480 bytes, EH, RET4). Native evidence: every visible building of the
// +0x170 plots adds to the bonus record through the rowed 0x004E0860; when
// the record names this region (+0) and its owner player (+4, id +0x14),
// its three rowed scale setters (0x003F7465/0x003F7478/0x003F74A0) take
// 1 + percent * 0.01 from +0x9C/+0xA0/+0xA4; with the +0x11C flag, every
// building template of the owner's score (TheLivingWorldBuildingTemplateStore
// 0x002E02F0 / 0x002B6498) of kind 1 with its +0x09 flag adds a new
// ArmySummaryEntry (0xC8 bytes, rowed ctor 0x0040C351) named from the
// template's +0x0C string, through a counted holder (count +0xB0, release
// 0x0007DEEF on +0xAC), to the record (rowed 0x003F7BB4). Names by address.
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref); // 0x0007DEEF
#include "../../Include/Common/ArmySummaryEntry.h"
struct Rva003F7B22Element
{
	Rva003F7B22Element(ArmySummaryEntry *entry) : m_entry(entry) { if (m_entry) ++m_entry->Rva0007DF07::m_04; }
	~Rva003F7B22Element() { if (m_entry) ReleaseTreeHintRef00217D4C(reinterpret_cast<TargetRef00217D4C *>(static_cast<Rva0007DF07 *>(m_entry))); }
	ArmySummaryEntry *m_entry;
};
class Rva003F7BB4
{
public:
	LivingWorldRegion *m_region;		// +0x00
	Rva002E2903Player *m_player;		// +0x04
	void rva003F7BB4(const Rva003F7B22Element &entry);
};
class Rva003F7478 { public: void rva003F7465(float scale); void rva003F7478(float scale); };
class Rva003F74A0 { public: void rva003F74A0(float scale); };
enum NameKeyType { NAMEKEY_NONE = 0 };
class ArmorTemplate;
class Rva002B6498 { public: ArmorTemplate *rva002B6498(NameKeyType key); };
class Rva002E02F0 { public: void rva002E02F0(Int score, _STL::vector<ScienceType> *out); };
class Rva0022C0CDSubsystem; extern Rva0022C0CDSubsystem *TheLivingWorldBuildingTemplateStore;
struct Rva003F2150Template
{
	unsigned char m_pad00[9];
	Bool m_09;					// +0x09
	unsigned char m_pad0A[2];
	AsciiString m_name;			// +0x0C
	unsigned char m_pad10[0x2C - 0x10];
	Int m_kind;					// +0x2C
};

static __forceinline void Rva003F2150ScanPlots(BuildPlotVector &plots, Rva003F7BB4 *bonus)
{
	for (BuildPlotVector::iterator it = plots.begin(); it != plots.end(); ++it) {
		LivingWorldBuildPlot *plot = *it;
		if (plot->HasBuilding())
			plot->m_building->rva004E0860(bonus);
	}
}
void LivingWorldRegion::rva003F2150(Rva003F7BB4 *bonus)
{
	bonus = *(Rva003F7BB4 * volatile *)&bonus;
	for (BuildPlotVector::iterator it = m_buildPlots.begin(); it != m_buildPlots.end(); ++it) {
		LivingWorldBuildPlot *plot = *it;
		if (plot->HasBuilding())
			plot->m_building->rva004E0860(bonus);
	}
	if (bonus->m_region != this || bonus->m_player->m_playerID != m_ownerPlayerID)
		return;
	float p9c = (float)getBonusPercent9C();
	p9c *= 0.01f;
	p9c += 1.0f;
	float pA0 = (float)getBonusPercentA0();
	pA0 *= 0.01f;
	pA0 += 1.0f;
	float pA4 = (float)getBonusPercentA4();
	pA4 *= 0.01f;
	pA4 += 1.0f;
	float scale9C = p9c;
	float scaleA0 = pA0;
	float scaleA4 = pA4;
	((Rva003F7478 *)bonus)->rva003F7465(scale9C);
	((Rva003F7478 *)bonus)->rva003F7478(scaleA0);
	((Rva003F74A0 *)bonus)->rva003F74A0(scaleA4);
	if (!m_ownerBuildsArmies)
		return;
	Rva002E2903Player *owner = ((Rva002BA8F1Logic *)TheLivingWorldLogic)->find(getOwnerPlayerID(), 0);
	if (!owner)
		return;
	_STL::vector<ScienceType> buildings;
	((Rva002E02F0 *)TheLivingWorldBuildingTemplateStore)->rva002E02F0(owner->getScore(), &buildings);
	_STL::vector<ScienceType>::iterator end = buildings.end();
	for (_STL::vector<ScienceType>::iterator b = buildings.begin(); b != end; ++b) {
		Rva003F2150Template *buildingTemplate = (Rva003F2150Template *)((Rva002B6498 *)TheLivingWorldBuildingTemplateStore)->rva002B6498((NameKeyType)*b);
		if (buildingTemplate && buildingTemplate->m_kind == 1 && buildingTemplate->m_09) {
			Rva003F7B22Element entry(new ArmySummaryEntry);
			entry.m_entry->m_name = buildingTemplate->m_name;
			bonus->rva003F7BB4(entry);
		}
	}
}
