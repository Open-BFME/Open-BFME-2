// ?rva0059DA34@Rva0059DA34@@QAEHHH_NHPAVRva004FF5B7@@PAH@Z
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
#include <map>
#include <vector>
#include "ascii_string.h"

extern unsigned int g_Va00E04544;

struct Rva00501875Count
{
	int value;
};

struct Rva00501E3FElement
{
	Rva00501E3FElement(const Rva00501E3FElement &src);

	int m_00;
	_STL::multimap<int, Rva00501875Count> m_04;
	int m_10;
};

struct Rva004FF5B7Node
{
	char m_pad[0x14];
	char m_value[1];
};

struct Rva004FF5B7Iter
{
	Rva004FF5B7Node *m_ptr;
};

class Rva004FF5B7
{
public:
	Rva004FF5B7Iter rva004FF5B7(int key);
};

struct Rva0059DA34Region
{
	char m_pad00[0x4C];
	_STL::multimap<int, Rva00501E3FElement> m_4c;
};

typedef _STL::map<int, int> Rva004FFA6EIntMap;

class Rva00319CED
{
public:
	int rva004E1755();
	char m_pad00[0x2C];
	AsciiString m_name; // +0x2C
};

struct BfmeE8
{
	int id;
	Rva00319CED *unit;
};

class Rva004FF8DA
{
public:
	bool rva0050010D(int type, int key);
	void *rva0050024C(int type, int key);
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
	int m_00;
	char m_pad04[0x30];
	_STL::vector<int> m_ids34; // +0x34
	_STL::vector<int> m_ids40; // +0x40
};

class Rva003B8E89 { public: void *rva003B8E89(void *); };
class Rva00E02D6C;
extern Rva00E02D6C *TheCampaignManager;
class Rva0040CB2CIndexedField { public: int get(int) const; };
struct Rva005E7322MidRet { char pad[4]; AsciiString text; };
class ThingTemplate { public: char pad00[0x5C4]; int kind; };
class ThingFactory { public: const ThingTemplate *findTemplate(const AsciiString &name); };
extern ThingFactory *TheThingFactory;

class Rva0059DA34
{
public:
	int rva0059DA34(int key, int limit, bool matchEqual, int maxLevel, Rva004FF5B7 *info, int *out);
	bool rva0059DB48(_STL::vector<BfmeE8> *out, const Rva0059D90CSource *source, Rva004FF8DA *types, Rva004FF5B7 *info, int limit, int budget, int *spent);
private:
	char m_pad00[0x20];
	int m_counts[8]; // +0x20
	int m_weights[8]; // +0x40
};

int Rva0059DA34::rva0059DA34(int key, int limit, bool matchEqual, int maxLevel, Rva004FF5B7 *info, int *out)
{
	for (int i = 0; i < 8; ++i)
		out[i] = 0;
	int total = 0;
	Rva004FFA6EIntMap::iterator from = ((Rva004FFA6EIntMap *)&g_Va00E04544)->find(key);
	const _STL::multimap<int, int> *levels = (const _STL::multimap<int, int> *)&from->second;
	for (key = 1; key <= maxLevel; ++key)
	{
		_STL::pair<_STL::multimap<int, int>::const_iterator, _STL::multimap<int, int>::const_iterator> range = levels->equal_range(key);
		for (_STL::multimap<int, int>::const_iterator it = range.first; it != range.second; ++it)
		{
			Rva0059DA34Region *region = (Rva0059DA34Region *)info->rva004FF5B7(it->second).m_ptr->m_value;
			for (_STL::multimap<int, Rva00501E3FElement>::iterator r = region->m_4c.begin(); r != region->m_4c.end(); ++r)
			{
				if ((matchEqual && r->first == limit) || (!matchEqual && r->first != limit))
				{
					Rva00501E3FElement army(r->second);
					for (_STL::multimap<int, Rva00501875Count>::iterator m = army.m_04.begin(); m != army.m_04.end(); ++m)
					{
						out[m->first] += m->second.value;
						total += m->second.value;
					}
				}
			}
		}
	}
	return total;
}

// ?rva0059DB48@Rva0059DA34@@QAE_NPAV?$vector@UBfmeE8@@V?$allocator@UBfmeE8@@@_STL@@@_STL@@PBURva0059D90CSource@@PAVRva004FF8DA@@PAVRva004FF5B7@@HHPAH@Z
// Retail 0x0059DB48 (503 bytes): sibling of 0x0059D90C. Tallies the source army with 0x0059DA34, ranks the
// eight unit types by this+0x40 weights (selection sort), then per id of the two source vectors picks the first
// ranked type the building table (rowed callers 0x0050010D / 0x0050024C, pinned) can field for the id's region
// key whose unit-template kind tally does not exceed the type weight; appends {id unit} while the unit cost
// stays under budget - *spent and decrements this+0x20[kind]. Returns whether anything was considered.
// Evidence: retail bytes; WB 0x014FF6A0 loops and calls; the args are evaluated key-first then type, so key and
// type are separate locals (that is what moves order[k] into EBX and unit into its stack slot).
bool Rva0059DA34::rva0059DB48(_STL::vector<BfmeE8> *out, const Rva0059D90CSource *source, Rva004FF8DA *types, Rva004FF5B7 *info, int limit, int budget, int *spent)
{
	int tally[8];
	rva0059DA34(source->m_00, limit, true, 3, info, tally);
	int order[8];
	int j;
	int i;
	for (i = 0; i < 8; ++i)
		order[i] = i;
	for (i = 0; i < 8; ++i)
	{
		for (j = i + 1; j < 8; ++j)
		{
			if (m_weights[order[j]] > m_weights[order[i]])
			{
				int t = order[i];
				order[i] = order[j];
				order[j] = t;
			}
		}
	}
	bool placed = false;
	const _STL::vector<int> *ids = &source->m_ids34;
	for (int pass = 0; pass < 2; ++pass)
	{
		if (pass == 1)
			ids = &source->m_ids40;
		for (unsigned int ii = 0; ii < ids->size(); ++ii)
		{
			for (int k = 0; k < 8; ++k)
			{
				int key1 = ((Rva0059D90CRegion *)TheLivingWorldLogic->getRegionManager()->rva0020EEF4((*ids)[ii]))->m_type->m_key;
				int type = order[k];
				if (!types->rva0050010D(type, key1))
					continue;
				int key2 = ((Rva0059D90CRegion *)TheLivingWorldLogic->getRegionManager()->rva0020EEF4((*ids)[ii]))->m_type->m_key;
				Rva00319CED *unit = (Rva00319CED *)types->rva0050024C(type, key2);
				void *summary = ((Rva003B8E89 *)TheCampaignManager)->rva003B8E89(&unit->m_name);
				AsciiString name(((Rva005E7322MidRet *)((Rva0040CB2CIndexedField *)summary)->get(0))->text);
				int kind = TheThingFactory->findTemplate(name)->kind;
				if (tally[kind] > m_weights[type])
					continue;
				BfmeE8 entry;
				entry.id = (*ids)[ii];
				entry.unit = unit;
				if (unit->rva004E1755() < budget - *spent)
				{
					out->push_back(entry);
					*spent += unit->rva004E1755();
					--m_counts[kind];
				}
				placed = true;
				break;
			}
		}
	}
	return placed;
}
