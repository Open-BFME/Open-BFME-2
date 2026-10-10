// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /EHc- /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// Native501875..501A00 RET4; WB12FF2F0 corroborates the complete record/key
// tally algorithm. Existing copy95 at5017B4 and destructor54 at501776 prove
// the44-byte record with two20-byte-element vectors at14/20. Use their real
// established provider spelling instead of the older second record name.
// Native local-map insertion copies8 bytes: signed key plus scalar count.
// Its erase4FF3DB only frees nodes, proving no mapped-value destructor work.
// Rva00501875Count is an explicit4-byte structural view of these count bits;
// no original mapped C++ type or application class name is asserted.
// STLport4.5.3 provides the algorithm. EHs/EHc- and the existing retail-tree
// layout setting reproduce the full helper bodies and their relocations.
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

struct Rva00501776
{
	Rva00501776(const Rva00501776 &that);
 ~Rva00501776();

	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	Rva00501875EntryVector m_14;
	Rva00501875EntryVector m_20;
};

class Rva00501875Owner
{
public:
	int rva00501875(int key);

private:
	int m_00;
	_STL::map<int, Rva00501776> m_map; // +0x04
};

struct Rva00501875Count {
 int value;
 Rva00501875Count(int n=0):value(n){}
 Rva00501875Count &operator+=(int n){value+=n;return *this;}
};

int Rva00501875Owner::rva00501875(int key)
{
	Rva00501776 info(m_map.find(key)->second);
	_STL::map<int, Rva00501875Count> counts;

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
				counts.insert(counts.end(), _STL::pair<const int, Rva00501875Count>(i, count));
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
				counts.insert(counts.end(), _STL::pair<const int, Rva00501875Count>(i, count));
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
