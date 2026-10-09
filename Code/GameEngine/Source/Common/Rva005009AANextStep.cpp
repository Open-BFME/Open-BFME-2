// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva005009AA@@YAHHH@Z, retail 0x005009AA (223 bytes). Cdecl, two int keys.
// Reads the int-key map at 0x00E04544 whose 24-byte values (copy
// constructor 0x0050055D, destructor 0x002B82D5) hold an int multimap at +0
// and an int-to-int map at +0x0C, as the rowed rva0050059A/rva00500606 in
// Rva00500606EqualRange.cpp do. Copies the first key's value, reads its
// +0x0C entry for the second key, then walks its +0 entries under key 1
// (rowed equal_range 0x002F1C89): for each listed key present in the
// global map it copies that key's value and returns the listed key when
// its +0x0C entry for the second key is exactly one less. Returns the
// first key when none is. Callers 0x0059C102 and 0x0059C90F. Map ownership
// and key meaning are not established so the name stays address-derived.

#include <map>

extern unsigned int g_Va00E04544;

typedef _STL::map<int, int> Rva005009AAIntMap;
typedef _STL::pair<const int, int> Rva005009AAIntValue;
typedef _STL::_Rb_tree<int, Rva005009AAIntValue, _STL::_Select1st<Rva005009AAIntValue>,
	_STL::less<int>, _STL::allocator<Rva005009AAIntValue> > Rva005009AAIntTree;
typedef _STL::pair<Rva005009AAIntTree::iterator, Rva005009AAIntTree::iterator> Rva005009AARange;

// The value's copy constructor and destructor carry different ledger names:
// the copy runs as the base of the destroyed type, so both the scope exits
// and the unwind funclets call the destructor directly.
class Rva0050055D
{
public:
	Rva0050055D(const Rva0050055D &other);
	char m_data[24];
};

class Rva002B82D5 : public Rva0050055D
{
public:
	Rva002B82D5(const Rva0050055D &other) : Rva0050055D(other) {}
	~Rva002B82D5();
};

int __cdecl rva005009AA(int from, int to)
{
	Rva005009AAIntMap *map = (Rva005009AAIntMap *)&g_Va00E04544;
	Rva002B82D5 fromValue(*(const Rva0050055D *)&map->find(from)->second);
	int fromDistance = ((Rva005009AAIntMap *)((char *)&fromValue + 0x0C))->find(to)->second;
	Rva005009AARange range = ((Rva005009AAIntTree *)&fromValue)->equal_range(1);
	for (Rva005009AAIntTree::iterator it = range.first; it != range.second; ++it)
	{
		if (map->find((*it).second) != map->end())
		{
			Rva002B82D5 stepValue(*(const Rva0050055D *)&map->find((*it).second)->second);
			if (fromDistance - ((Rva005009AAIntMap *)((char *)&stepValue + 0x0C))->find(to)->second == 1)
				return (*it).second;
		}
	}
	return from;
}
