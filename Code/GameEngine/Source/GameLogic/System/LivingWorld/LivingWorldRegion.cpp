// cl: /O1 /EHsc /MD /arch:SSE /ICode/Libraries/Include/Lib /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
#include <vector>
#include "Coord2D.h"
#include "Coord3D.h"
#include "ascii_string.h"
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
struct Rva003F0614BuildingLink
{
    unsigned char prefix[0x2C];
    CreateAHeroData *field2C;
};
class LivingWorldBuilding
{
public:
    unsigned char prefix[0x28];
    Rva003F0614BuildingLink *field28;
};

class LivingWorldBattle;
class LivingWorldRegion;
struct LivingWorldBuildPlot
{
	LivingWorldBuildPlot(Int id, LivingWorldRegion *region, const Coord2D &position);
    Bool HasBuilding() const { return m_building != 0 && !m_hidden; }

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
};

// The unit being spawned; its command-point cost comes from 0x004E1755.
class Rva00319CED
{
public:
	Int rva004E1755();
};

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(Int id, UnsignedInt *outIndex);	// 0x002B51F8
};

class Rva002E071E
{
public:
    bool rva002E071E(const Rva002E071E *other) const;
};

class Rva00318C32Ret;
class Rva0020E89C;
class LivingWorldRegionManager { public:
    Rva00318C32Ret *rva0020FAEA(const Coord2D *,Rva00318C32Ret *);
    Bool GetRegionCenterPoint(Rva0020E89C *,Coord2D *);
};
class LivingWorldLogic
{
public:
    void *rva002B4948(void *owner, void *region, void *exclude);
    char beforeB0[0xb0];
    LivingWorldRegionManager *regions;
};

class Rva00318FBE
{
public:
    Int rva00318FBE();
};
extern LivingWorldLogic *TheLivingWorldLogic;

class LivingWorldRegion
{
public:
	void CreateBuildPlots();
    void PrepareSkirmishOpponents(LivingWorldBattle *battle);
    Bool DebugValidatePlacementSpot(const Coord2D &spot,Coord2D *out,const char *kind);
    Bool IsOwnedByTeam(Int teamID) const;
	Bool CanSpawnUnitWithinCPLimit(Rva00319CED *unit) const;
	LivingWorldBuilding *GetBuildingByIndex(Int index) const;
	Int rva003F05CE();
	Int rva003F0614(CreateAHeroData *key) const;
    LivingWorldBuildPlot *rva003F088C(Int key) const;

private:
	Int rva003EFDB3(Rva002E2903Player *owner) const;	// 0x003EFDB3, command points in use
	Int rva003EFD6F(Rva002E2903Player *owner) const;	// 0x003EFD6F, command-point limit
	Int usedCommandPoints(Rva002E2903Player *owner) const { return rva003EFDB3(owner); }

	unsigned char m_pad00[0x14];
    AsciiString m_name;
    char m_pad18[0xa9-0x18];
    bool m_reservedA9;
    char m_padAA[0xfc-0xaa];
    _STL::vector<Coord2D> m_plotPositions;
    Int m_limit108;
    Int m_limit10C;
    unsigned char m_pad110[0x13c - 0x110];
	Int m_ownerPlayerID;			// +0x13C
	unsigned char m_pad140[0x170 - 0x140];
	BuildPlotVector m_buildPlots;
    int m_plotIndex;
    char m_unknown180[0x1a3-0x180];
    bool m_plotFlag;
};

// LivingWorldRegion::IsOwnedByTeam, retail 0x003EFD3D.
Bool LivingWorldRegion::IsOwnedByTeam(Int teamID) const
{
	if (m_ownerPlayerID == -1)
		return false;
	Rva002E2903Player *owner = reinterpret_cast<Rva002BA8F1Logic *>(TheLivingWorldLogic)->find(m_ownerPlayerID, 0);
	return owner ? owner->m_teamID == teamID : false;
}

// LivingWorldRegion::GetBuildingByIndex, retail 0x003F0711: the index-th
// plot that currently shows a building.
LivingWorldBuilding *LivingWorldRegion::GetBuildingByIndex(Int index) const
{
	Int count = 0;
	for (UnsignedInt i = 0; i < m_buildPlots.size(); ++i)
	{
		if (m_buildPlots[i]->HasBuilding())
		{
			if (count == index)
				return m_buildPlots[i]->m_building;
			++count;
		}
	}
	return 0;
}

// LivingWorldRegion::CanSpawnUnitWithinCPLimit, retail 0x003F0259: an
// unowned region always allows it; the owner's own region counts the new
// unit's cost against the limit.
Bool LivingWorldRegion::CanSpawnUnitWithinCPLimit(Rva00319CED *unit) const
{
	if (m_ownerPlayerID == -1)
		return true;
	Rva002E2903Player *owner = reinterpret_cast<Rva002BA8F1Logic *>(TheLivingWorldLogic)->find(m_ownerPlayerID, 0);
	if (owner == 0)
		return false;
	if (m_ownerPlayerID == owner->m_playerID)
		return rva003EFDB3(owner) + unit->rva004E1755() <= rva003EFD6F(owner);
	return usedCommandPoints(owner) <= rva003EFD6F(owner);
}

// Complete native 3F0614..3F066B RET4. Same +170 plot vector and +20/+34
// building filter as GetBuildingByIndex; the nested +28/+2C pointer is
// compared with the argument. Its identity beyond this relation is unresolved.
Int LivingWorldRegion::rva003F0614(CreateAHeroData *key) const
{
    Int count = 0;
    for (UnsignedInt i = 0; i < m_buildPlots.size(); ++i)
    {
        if (m_buildPlots[i]->HasBuilding() &&
            m_buildPlots[i]->m_building->field28->field2C == key)
            ++count;
    }
    return count;
}

// Native 3EFD6F..3EFDB3 RET4. Calls from CanSpawnUnitWithinCPLimit
// consume the return as a signed command-point limit; the former opaque
// pointer-returning private view described the same +108/+10C slots.
Int LivingWorldRegion::rva003EFD6F(Rva002E2903Player *owner) const
{
    Int key = m_ownerPlayerID;
    if (key != owner->m_playerID)
    {
        Rva002E2903Player *player = reinterpret_cast<Rva002BA8F1Logic *>(TheLivingWorldLogic)->find(key, 0);
        if (player != 0 && reinterpret_cast<const Rva002E071E *>(player)->rva002E071E(
                reinterpret_cast<const Rva002E071E *>(owner)))
            return m_limit10C;
    }
    return m_limit108;
}

// Native 3EFDB3..3EFDD7 RET4. The singleton query takes the player, this
// region and a null exclusion; an army result supplies its used points.
Int LivingWorldRegion::rva003EFDB3(Rva002E2903Player *owner) const
{
    Rva00318FBE *army = static_cast<Rva00318FBE *>(TheLivingWorldLogic->rva002B4948(
        owner, const_cast<LivingWorldRegion *>(this), 0));
    return army ? army->rva00318FBE() : 0;
}

// Native3F088C..3F08D7 RET4 searches the same +170/+174 plot vector
// as GetBuildingByIndex. The key at plot+18 and original method spelling
// remain unresolved; no complete plot allocation layout is asserted.
LivingWorldBuildPlot *LivingWorldRegion::rva003F088C(Int key) const
{
    for (UnsignedInt i=0;i<m_buildPlots.size();++i)
        if (m_buildPlots[i]->m_key18 == key)
            return m_buildPlots[i];
    return 0;
}

// Unnamed WB 0x01040060; native 0x003F05CE / 70 B. The named
// GetBuildingByIndex and HasArmyQueuedInAnyBuilding corroborate that this
// counts the same visible buildings in the +0x170 plot collection.
Int LivingWorldRegion::rva003F05CE()
{
    Int count = 0;
    for (UnsignedInt i = 0; i < m_buildPlots.size(); ++i)
    {
        if (m_buildPlots[i]->HasBuilding())
            ++count;
    }
    return count;
}

class Rva003F3F27 { public: void rva003F2106(); };
class Rva002B3166BumpCounter { public: int bump(); };
void LivingWorldRegion::CreateBuildPlots()
{
    if (m_buildPlots.size() != 0)
        reinterpret_cast<Rva003F3F27 *>(this)->rva003F2106();
    m_buildPlots.reserve(m_plotPositions.size());
    for (unsigned i=0; i<m_plotPositions.size(); ++i) {
        int id = reinterpret_cast<Rva002B3166BumpCounter *>(TheLivingWorldLogic)->bump();
        LivingWorldBuildPlot *plot = new LivingWorldBuildPlot(id, this, m_plotPositions[i]);
        m_buildPlots.push_back(plot);
    }
    m_plotIndex=0;
    m_plotFlag=false;
}




int Rva003F1E2EHook(int,int);
class Gen_00528EC0 {
public:
    Gen_00528EC0(short index) { rva003F2968(index); }
    void rva003F2968(short);
    bool bfmeDiffers(const Gen_00528EC0 &) const;
    Gen_00528EC0 rva003F3133();
    int index() const { return (short)Rva003F1E2EHook(value,value); }
private:
    int head;
    int value;
};
class GameSlot;
class GameInfo { public: GameSlot *getSlot(int); };
extern GameInfo *TheGameInfo;
struct RegionGameSlotPrefix {
    char before4C[0x4c];
    int armyID;
    char before1A4[0x1a4-0x50];
    bool participating;
};
class LivingWorldBattle { public: bool rva003F486C(int); };
struct Rva003EFDDBOut;
class Rva003EFDDBHolder { public: void rva003EFDDB(int,Rva003EFDDBOut *); };
void LivingWorldRegion::PrepareSkirmishOpponents(LivingWorldBattle *battle)
{
    if (!battle || m_reservedA9 || !TheGameInfo) return;
    Gen_00528EC0 i(0);
    while (true) {
        Gen_00528EC0 end(8);
        if (!i.bfmeDiffers(end)) break;
        GameSlot *slot=TheGameInfo->getSlot(i.index());
        RegionGameSlotPrefix *fields=reinterpret_cast<RegionGameSlotPrefix *>(slot);
        int id=fields->armyID;
        fields->participating=battle->rva003F486C(id);
        if (fields->participating)
            reinterpret_cast<Rva003EFDDBHolder *>(this)->rva003EFDDB(id,reinterpret_cast<Rva003EFDDBOut *>(slot));
        i.rva003F3133();
    }
}


// WB 0x0103D540 names the validator; native 3F0DCB..3F0E8A RET12.
// Input x/y become an escaped Coord3D at height 100. The +14 name and +B0
// manager access are retail facts; existing neutral manager ABIs are retained.
Bool LivingWorldRegion::DebugValidatePlacementSpot(const Coord2D &spot,Coord2D *out,const char *kind)
{
    float y=spot.y;
    float x=spot.x;
    LivingWorldLogic *logic=TheLivingWorldLogic;
    Coord3D pos;
    pos.y=y;
    pos.x=x;
    pos.z=100.0f;
    LivingWorldRegionManager *manager=logic->regions;
    if (manager->rva0020FAEA(reinterpret_cast<const Coord2D *>(&pos),reinterpret_cast<Rva00318C32Ret *>(this)) != reinterpret_cast<Rva00318C32Ret *>(this)) {
    AsciiString message;
    message.format("Bad INI data! Region %s has a %s placement spot (%.0f, %.0f) outside its bounds (remember, extra offset points are generated for overlapping opposing armies)! Using region center point",m_name.str(),kind,pos.x,pos.y);
    TheLivingWorldLogic->regions->GetRegionCenterPoint(reinterpret_cast<Rva0020E89C *>(this),out);
    return false;
    }
    return true;
}
