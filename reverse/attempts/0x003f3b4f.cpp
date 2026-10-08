// ?rva003F3B4F@Rva003F3F27@@QAEXXZ
// partial score=0.8 date=2026-10-08
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
class Xfer;
class ModuleData;
enum ScienceType { RegionOpaqueScienceValue=0 };
// WB DoXfer treats each 12-byte hero slot as an army-vector. The existing
// rowed transfer helper retains its neutral ModuleData pointer element ABI.
typedef _STL::vector<const ModuleData *> RegionHeroSlot;
struct Rva003F0614BuildingLink
{
    unsigned char prefix[0x2C];
    CreateAHeroData *field2C;
};
class LivingWorldBuilding
{
public:
    unsigned char prefix[0x18];
    int id;
    char before28[0xc];
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
	void rva002B8D06(Xfer *,_STL::vector<const ModuleData *> *);
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
    void DoXfer(Xfer *);
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
    unsigned char m_pad110[0x12c-0x110];
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

class Rva003F3F27 { public: void rva003F2106(); void rva003F3B4F();
    char prefix[0xe4];
    _STL::vector<Coord2D> positions,enemyPositions;
    char before180[0x180-0xfc];
    _STL::vector<RegionHeroSlot> heroes,enemyHeroes;
};
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

struct RegionXferVersionFields { unsigned char minimum,current; };
union RegionXferVersion { RegionXferVersionFields fields; unsigned value; };
class Xfer {
public:
    virtual void slot00();
    virtual bool IsLoading() const;
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void Version(RegionXferVersion *);
    virtual void slot11();
    virtual void Snapshot(void *);
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void Coord(Coord2D *);
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void Int(int *);
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void Bool(bool *);
    virtual void slot37();
};
struct Rva003EFE82Obj;
int Rva003EFE82Get(Rva003EFE82Obj *,void *);
void XferLivingWorldPlayerID(Xfer *,int *);
Xfer *Rva003F2394Xfer(Xfer *,_STL::vector<ScienceType> *);
class Rva004E075FObj;
int Rva004E075FGet(Rva004E075FObj *,int);
class Rva003F1093 { public: CreateAHeroData *rva003F083A(void *); char prefix[0x170]; BuildPlotVector plots; };
class Rva003F3B28View { public: void rva003F3B28(int); };
// Native construction tracks an eight-byte zero coordinate temporary in the
// EH bitmap and then clears its bit without a cleanup call. Keep that lifetime
// here while using the canonical Coord2D layout and plot-constructor ABI.
class RegionPlacementCoordTemporary : public Coord2D { public: RegionPlacementCoordTemporary() { x=0; y=0; } ~RegionPlacementCoordTemporary() {} };
// WB 0x01041590 names DoXfer; native 3F3BFF..3F3F03 RET4. Slot numbers,
// field addresses, version branches and helper ABIs come from retail.
// Region/building IDs and nested vector element identities remain neutral.
void LivingWorldRegion::DoXfer(Xfer *xfer)
{
    RegionXferVersion version;
    version.fields.minimum=1; version.fields.current=3;
    xfer->Version(&version);
    Rva003EFE82Get(reinterpret_cast<Rva003EFE82Obj *>(xfer),&m_regionID);
    xfer->Bool(&flag1A2);
    XferLivingWorldPlayerID(xfer,&m_ownerPlayerID);
    XferLivingWorldPlayerID(xfer,&m_player140);
    if(version.fields.current<2) { int zero=0; xfer->Int(&zero); }
    xfer->Coord(&m_position);
    xfer->Bool(&flag1A0);
    xfer->Bool(&flag1A1);
    xfer->Int(&value14C);
    xfer->Int(&value150);
    xfer->Int(&value154);
    if(version.fields.current<2) { Coord2D zero={0,0}; xfer->Coord(&zero); }
    Rva003F2394Xfer(xfer,&values164);
    Rva003F2394Xfer(xfer,&values158);
    if(xfer->IsLoading()) {
        reinterpret_cast<Rva003F3F27 *>(this)->rva003F2106();
        m_plotIndex=0; m_plotFlag=false;
        if(m_ownerPlayerID!=-1) {
            int count;
            xfer->Int(&count);
            for(int i=0;i<count;++i) {
                LivingWorldBuildPlot *plot=new LivingWorldBuildPlot(0,this,RegionPlacementCoordTemporary());
                xfer->Snapshot(plot);
                m_buildPlots.push_back(plot);
            }
            int buildingID;
            Rva004E075FGet(reinterpret_cast<Rva004E075FObj *>(xfer),reinterpret_cast<int>(&buildingID));
            if(!buildingID) m_plotIndex=0;
            else m_plotIndex=reinterpret_cast<LivingWorldBuildPlot *>(reinterpret_cast<Rva003F1093 *>(this)->rva003F083A(reinterpret_cast<void *>(buildingID)));
        }
    } else if(m_ownerPlayerID!=-1) {
        int count=m_buildPlots.size();
        xfer->Int(&count);
        for(int i=0;i<count;++i) xfer->Snapshot(m_buildPlots[i]);
        int buildingID=(m_plotIndex && m_plotIndex->m_building) ? m_plotIndex->m_building->id : 0;
        Rva004E075FGet(reinterpret_cast<Rva004E075FObj *>(xfer),reinterpret_cast<int>(&buildingID));
    }
    xfer->Bool(&m_plotFlag);
    int spots=m_heroSlots.size();
    xfer->Int(&spots);
    if(xfer->IsLoading()) {
        reinterpret_cast<Rva003F3F27 *>(this)->rva003F3B4F();
        reinterpret_cast<Rva003F3B28View *>(&m_heroSlots)->rva003F3B28(spots);
    }
    if(TheLivingWorldLogic) {
        for(int i=0;i<spots;++i) reinterpret_cast<Rva002BA8F1Logic *>(TheLivingWorldLogic)->rva002B8D06(xfer,&m_heroSlots[i]);
    }
    if(version.fields.current>=3) { xfer->Int(&value134); xfer->Int(&value138); }
}

// WB10413F0 and native3F083A..3F088C RET4: return the plot whose building
// has the requested +18 ID. Keep the existing neutral pointer ABI; the
// historical return type is not asserted as the application object identity.
CreateAHeroData *Rva003F1093::rva003F083A(void *key)
{
    for (unsigned i=0;i<plots.size();++i) {
        LivingWorldBuilding *building=plots[i]->m_building;
        if(building && building->id == reinterpret_cast<int>(key))
            return reinterpret_cast<CreateAHeroData *>(plots[i]);
    }
    return 0;
}

void Rva003F3F27::rva003F3B4F()
{
    reinterpret_cast<Rva003F3B28View *>(&heroes)->rva003F3B28(positions.size());
    unsigned i;
    for(i=0;i<heroes.size();++i) heroes[i].erase(heroes[i].begin(),heroes[i].end());
    reinterpret_cast<Rva003F3B28View *>(&enemyHeroes)->rva003F3B28(enemyPositions.size());
    for(i=0;i<enemyHeroes.size();++i) enemyHeroes[i].erase(enemyHeroes[i].begin(),enemyHeroes[i].end());
}
