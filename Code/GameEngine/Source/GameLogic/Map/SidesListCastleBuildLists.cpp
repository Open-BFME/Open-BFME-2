// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// stlport
//
// SidesList's castle-template build-list maps (BFME2 SidesList.cpp).
//
// ?rva0032E6F4@SidesList@@QAEXHABUBfmePod128@@@Z, retail 0x0032E6F4, 175 bytes.
// Its only caller is parseCastleTemplateDataChunk 0x0032F664 (REL32 at
// 0x0032F742), which reads a faction name key once, then hands each castle
// build entry it parses to this body with that key. WorldBuilder keeps it out
// of line unnamed (wb 0xa8b7e0) with the same call sequence: find, push_back
// on a hit, otherwise a local vector, push_back, make_pair, the pair
// conversion and insert. The name keeps the address.
//
// Layout (target): the map at this+0x24 is the int-keyed
// map<int, vector<BfmePod128> > whose insert path stlport_map_int_vector_pod128.cpp
// lands (insert_unique 0x0032DCE0, push_back 0x0032CA14); a second map follows
// at +0x30 and the side count at +0x3C.
//
// Element (structural inference): the 0x80-byte entry is really BuildListInfo.
// push_back's _Construct is the BuildListInfo copy (0x0032A2AF) and the vector
// destructor 0x0032BE80 runs the 0x80-stride virtual destroy loop 0x0032B580.
// The ledger already spells the element BfmePod128 across this map's rows, so
// this TU keeps that name. Its declared destructor makes STLport's _Destroy
// non-trivial, which keeps ~vector out of line (three calls to 0x0032BE80) as
// in retail; a trivial element inlines the free instead.
//
// Folded callees, each byte-verified from this TU against its own address:
// _M_find 0x00388F63 (every int-keyed map), make_pair 0x0032C58A, the
// pair<int, V> constructor 0x0032BFCB it calls, and the pair<const int, V>
// conversion constructor 0x0032BF4E (same bytes as the pair copy).
//
// ?rva0032ED75@SidesList@@QAEXHABV?$vector@UBfmeE8@@...@Z, retail 0x0032ED75,
// 175 bytes, is the same add for the second map at this+0x30. Its only caller
// is parseCastleTemplateDataChunk too (REL32 at 0x0032F80C), passing the key
// and a path it built from a count and that many two-real points through
// vector<BfmeE8>::push_back 0x00539A2E. The mapped value is a vector of those
// paths; BfmeE8 is the ledger's spelling of the 8-byte point (the element of
// _Construct<vector<BfmeE8> > 0x0032B598 and of the pair rows at 0x0032E800).
//
// Its three vector destructors carry unwind states in retail (1, 0, -1)
// because the game's free is a C++-linkage function that may throw: the
// destructor chain 0x0032E7A3 -> _Destroy 0x003F29F8 -> 0x0007FAB3 -> free
// 0x00030830 keeps an EH frame of its own. Reaching free through the
// _STL::free spelling (the Rva000C2980Finish.cpp idiom) reproduces that; the
// extern "C" import is nothrow under /EHsc and drops the states.
//
// Its callees fold onto rows other units own, each byte-verified from this TU
// against its own address: _M_find 0x00388F63; push_back 0x0032EA3F with its
// _M_insert_overflow 0x0032E842, __uninitialized_fill_n 0x0032B5EB, _M_clear
// 0x0032E7E2 and allocate 0x00395928; insert_unique 0x0032EB87 with _M_insert
// 0x0032EAD6, _M_create_node 0x0032EA7F and the pair _Construct 0x0032E94B;
// the pair<int, V> constructor 0x0032E81D; the pair<const int, V> copy and
// conversion constructors 0x0032E800; the destructor chain above. make_pair
// 0x0032E914 had no row and is this unit's own.

#include <stdlib.h>
namespace _STL { void __cdecl free(void *block) throw(...); }
#define free _STL::free
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <vector>
#undef free

struct BfmePod128 { ~BfmePod128(); int a[32]; };
struct BfmeE8 { int a[2]; };

typedef _STL::map<int, _STL::vector<BfmePod128> > IntPod128VectorMap;
typedef _STL::vector<BfmeE8> E8Vector;
typedef _STL::map<int, _STL::vector<E8Vector> > IntE8VectorListMap;

class SidesList
{
public:
	virtual ~SidesList();
	void rva0032E6F4(int key, const BfmePod128 &entry);
	void rva0032ED75(int key, const E8Vector &path);

private:
	char m_bases[0x24 - 4];
	IntPod128VectorMap m_castleBuildLists;	// +0x24
	IntE8VectorListMap m_castlePaths;	// +0x30
};

// The entry joins the key's list, creating the list on first use.
void SidesList::rva0032E6F4(int key, const BfmePod128 &entry)
{
	IntPod128VectorMap::iterator it = m_castleBuildLists.find(key);
	if (it != m_castleBuildLists.end()) {
		(*it).second.push_back(entry);
	} else {
		_STL::vector<BfmePod128> list;
		list.push_back(entry);
		m_castleBuildLists.insert(_STL::make_pair(key, list));
	}
}

void SidesList::rva0032ED75(int key, const E8Vector &path)
{
	IntE8VectorListMap::iterator it = m_castlePaths.find(key);
	if (it != m_castlePaths.end()) {
		(*it).second.push_back(path);
	} else {
		_STL::vector<E8Vector> list;
		list.push_back(path);
		m_castlePaths.insert(_STL::make_pair(key, list));
	}
}
