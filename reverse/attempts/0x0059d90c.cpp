// ?rva0059D90C@Rva0059D90C@@QAE_NPAV?$vector@UBfmeE8@@V?$allocator@UBfmeE8@@@_STL@@@_STL@@PBURva0059D90CSource@@PAVRva004FF8DA@@HPAH@Z
// partial score=0.95 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0059D90C@Rva0059D90C@@QAE_NPAV?$vector@UBfmeE8@@V?$allocator@UBfmeE8@@@_STL@@@_STL@@PBURva0059D90CSource@@PAVRva004FF8DA@@HPAH@Z
// Retail 0x0059D90C..0x0059DA34 (296 bytes).
// For the two id vectors of the source (+0x34 then +0x40) picks for every id
// the unit type (0..7) with the highest remaining count in the receiver's
// int[8] at +0x20 (starting from -100; 7 means none) among the types the
// building-types table has a unit of for the id's region key; when one is
// found with a count below 8 it decrements that count and looks the unit up
// and appends {id unit} to the output vector and adds the unit's cost to
// *spent while the cost stays below budget - *spent. Always returns true.
// Evidence: WorldBuilder 0x014FF4A0 has the same loops and calls and names
// the callees LivingWorldAIBuildingTypes::HasUnitOfType (rowed 0x004FF8DA)
// and GetUnitOfType (rowed 0x004FF910). Other rowed callees: region lookup
// Rva0020EEF4Outer::rva0020EEF4 0x0020EEF4 on TheLivingWorldLogic +0xB0 (as
// in LivingWorldLogic.cpp) then region +0x28 -> +4 as the type key
// Rva00319CED::rva004E1755 0x004E1755 (unit cost) and
// vector<BfmeE8>::push_back 0x00539A2E (8-byte {id unit} record as in WB's
// adjacent locals). Receiver and source identities are unproven; names are
// address-derived.
#include <vector>

struct BfmeE8;
namespace _STL
{
template <> void vector<BfmeE8, allocator<BfmeE8> >::push_back(const BfmeE8 &value);
}

class Rva00319CED
{
public:
	int rva004E1755();
};

struct BfmeE8
{
	int id;
	Rva00319CED *unit;
};

class Rva004FF8DA
{
public:
	bool rva004FF8DA(int type, int key);
	void *rva004FF910(int type, int key);
};

struct Rva0059D90CTypeKey
{
	int m_00;
	int m_key; // +0x04
};

struct Rva0059D90CRegion
{
	char m_pad00[0x28];
	Rva0059D90CTypeKey *m_type; // +0x28
};

class Rva0020EEF4Outer
{
public:
	int rva0020EEF4(int id);
};

class LivingWorldLogic
{
public:
	Rva0020EEF4Outer *getRegionManager() { return m_regions; }
private:
	char m_pad00[0xB0];
	Rva0020EEF4Outer *m_regions; // +0xB0
};
extern LivingWorldLogic *TheLivingWorldLogic;

struct Rva0059D90CSource
{
	char m_pad00[0x34];
	_STL::vector<int> m_ids34; // +0x34
	_STL::vector<int> m_ids40; // +0x40
};

class Rva0059D90C
{
public:
	bool rva0059D90C(_STL::vector<BfmeE8> *out, const Rva0059D90CSource *source, Rva004FF8DA *types, int budget, int *spent);
private:
	char m_pad00[0x20];
	int m_counts[8]; // +0x20
};

bool Rva0059D90C::rva0059D90C(_STL::vector<BfmeE8> *out, const Rva0059D90CSource *source, Rva004FF8DA *types, int budget, int *spent)
{
	const _STL::vector<int> *ids = &source->m_ids34;
	for (int pass = 0; pass < 2; ++pass)
	{
		if (pass == 1)
			ids = &source->m_ids40;
		for (unsigned int i = 0; i < ids->size(); ++i)
		{
			int best = -100;
			int bestType = 7;
			for (int type = 0; type < 8; ++type)
			{
				if (m_counts[type] > best && types->rva004FF8DA(type, ((Rva0059D90CRegion *)TheLivingWorldLogic->getRegionManager()->rva0020EEF4((*ids)[i]))->m_type->m_key))
				{
					best = m_counts[type];
					bestType = type;
				}
			}
			if (bestType != 7 && best < 8)
			{
				--m_counts[bestType];
				BfmeE8 entry;
				entry.id = (*ids)[i];
				entry.unit = (Rva00319CED *)types->rva004FF910(bestType, ((Rva0059D90CRegion *)TheLivingWorldLogic->getRegionManager()->rva0020EEF4((*ids)[i]))->m_type->m_key);
				if (entry.unit->rva004E1755() < budget - *spent)
				{
					out->push_back(entry);
					*spent += entry.unit->rva004E1755();
				}
			}
		}
	}
	return true;
}
