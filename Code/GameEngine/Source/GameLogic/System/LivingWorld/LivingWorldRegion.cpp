// cl: /O1 /EHsc /MD /arch:SSE
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

struct LivingWorldBuildPlot
{
	Bool HasBuilding() const { return m_building != 0 && !m_hidden; }

	unsigned char m_pad00[0x20];
	LivingWorldBuilding *m_building;	// +0x20
	unsigned char m_pad24[0x34 - 0x24];
	Bool m_hidden;				// +0x34
};

// STLport vector<LivingWorldBuildPlot *> view.
class BuildPlotVector
{
public:
	UnsignedInt size() const { return m_finish - m_start; }
	LivingWorldBuildPlot *operator[](UnsignedInt i) const { return m_start[i]; }

private:
	LivingWorldBuildPlot **m_start;
	LivingWorldBuildPlot **m_finish;
	LivingWorldBuildPlot **m_endOfStorage;
};

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

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class LivingWorldRegion
{
public:
	Bool IsOwnedByTeam(Int teamID) const;
	Bool CanSpawnUnitWithinCPLimit(Rva00319CED *unit) const;
	LivingWorldBuilding *GetBuildingByIndex(Int index) const;
	Int rva003F0614(CreateAHeroData *key) const;

private:
	Int rva003EFDB3(Rva002E2903Player *owner) const;	// 0x003EFDB3, command points in use
	Int rva003EFD6F(Rva002E2903Player *owner) const;	// 0x003EFD6F, command-point limit
	Int usedCommandPoints(Rva002E2903Player *owner) const { return rva003EFDB3(owner); }

	unsigned char m_pad00[0x13c];
	Int m_ownerPlayerID;			// +0x13C
	unsigned char m_pad140[0x170 - 0x140];
	BuildPlotVector m_buildPlots;		// +0x170
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
