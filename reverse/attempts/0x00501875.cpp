// ?rva00501875@Rva00501875Owner@@QAEHH@Z
// partial score=0.99 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// NEAR (helper draft): every byte matches; only three call targets differ.
//  1. map<int,Rva00501DD4Sub>::_M_find<int> is unresolved: retail calls the
//     ICF body 0x00388F63 (fold-proof pin needed for
//     ??$_M_find@H@?$_Rb_tree@HU?$pair@$$CBHURva00501DD4Sub@@@_STL@@...).
//  2. ??0?$map@HHU?$less@H@_STL@@V?$allocator@U?$pair@$$CBHH@_STL@@@2@@_STL@@QAE@XZ
//     is unresolved: retail calls the ICF map ctor 0x0033C432.
//  3. the local map's tree destructor resolves to the rowed map<int,int> copy
//     0x0021B775 but retail calls 0x004FF5F3 (the copy next to this unit,
//     ledgered as the LocomotorSetType tree dtor; its clear is 0x004FF49F), so
//     the local map's real value type (or that dtor's ledger name) is open.
// The loop counters are long: retail copies them into a temporary before
// every const int& call, which an int counter does not do (an enum also would).
// Rva00501776 derives from the copy-ctor view only to call the rowed dtor
// ??1Rva00501776@@QAE@XZ; both placeholder classes name the same record.
// ?rva00501875@Rva00501875Owner@@QAEHH@Z retail 0x00501875..0x00501A00 (395 bytes).
// No call or vtable reference found; WorldBuilder twin 0x012FF2F0 (unnamed).
// Copies the record found under key in the owner's map at +4 (rowed copy ctor
// 0x005017B4, destroyed by the rowed 0x00501776), tallies the multimap<int,int>
// counts of keys 0..7 over the record's two 0x14-byte element vectors into a
// local map, and returns the key 0..7 with the largest local count().
#include <map>

struct Rva00501875Entry
{
	int m_00;
	_STL::multimap<int, int> m_map; // +0x04
	int m_10;
};

struct Rva00501875EntryVector
{
	Rva00501875Entry *m_start;
	Rva00501875Entry *m_finish;
	Rva00501875Entry *m_end;
};

struct Rva00501DD4Sub
{
	Rva00501DD4Sub(const Rva00501DD4Sub &that);

	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	Rva00501875EntryVector m_14;
	Rva00501875EntryVector m_20;
};

// The rowed destructor 0x00501776 of the same record.
struct Rva00501776 : public Rva00501DD4Sub
{
	Rva00501776(const Rva00501DD4Sub &that) : Rva00501DD4Sub(that) {}
	~Rva00501776();
};

class Rva00501875Owner
{
public:
	int rva00501875(int key);

private:
	int m_00;
	_STL::map<int, Rva00501DD4Sub> m_map; // +0x04
};

int Rva00501875Owner::rva00501875(int key)
{
	Rva00501776 info(m_map.find(key)->second);
	_STL::map<int, int> counts;

	Rva00501875Entry *it;
	long i;
	for (it = info.m_14.m_start; it != info.m_14.m_finish; ++it)
	{
		for (i = 0; i < 8; ++i)
		{
			int count = it->m_map.count(i);
			if (counts.find(i) != counts.end())
				counts.find(i)->second += count;
			else
				counts.insert(counts.end(), _STL::pair<const int, int>(i, count));
		}
	}
	for (it = info.m_20.m_start; it != info.m_20.m_finish; ++it)
	{
		_STL::multimap<int, int>::iterator first = it->m_map.begin();
		for (i = 0; i < 8; ++i)
		{
			int count = it->m_map.count(i);
			if (counts.find(first->first) != counts.end())
				counts.find(first->first)->second += count;
			else
				counts.insert(counts.end(), _STL::pair<const int, int>(i, count));
		}
	}

	int best = 0;
	unsigned int bestCount = 0;
	for (i = 0; i < 8; ++i)
	{
		if (counts.count(i) > bestCount)
		{
			bestCount = counts.count(i);
			best = i;
		}
	}
	return best;
}
