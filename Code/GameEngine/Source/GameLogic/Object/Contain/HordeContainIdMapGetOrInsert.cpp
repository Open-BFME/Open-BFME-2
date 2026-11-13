// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// Get-or-insert subscript of HordeContain's id -> {Coord3D, UnsignedInt} map at +0x1A0
// (retail 0x00473F81, called by HordeContain::xfer 0x00474EA8 and 0x004756C9). Names by address.

#include <map>
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

// Mapped record of the id map: ctor 0x00469155, operator= 0x0046916D.
// Its destructor is empty; the WorldBuilder twin still tracks both temporaries for unwinding.
class Rva00469155
{
public:
	Rva00469155();
	Rva00469155 &operator=(const Rva00469155 &o);
	~Rva00469155() {}
	Coord3D m_pos;
	unsigned int m_value;
};

// The map's key/record pair, constructed out of line at 0x00469BEA.
class Rva00469BEA
{
public:
	Rva00469BEA(const int &a, const Rva00469155 &b);
	int m_00;
	Rva00469155 m_04;
};

// The map is viewed through the rowed int-key instantiations: the record map whose insert is
// 0x00470205 and the int/int tree whose _M_lower_bound 0x00382A92 every int-key tree shares.
// The mapped value is retail's 16-byte Rva00469155: node 0x0046AC30 allocates 0x24 bytes and 0x00469D33 copies 16 after the key.
#include "../../../../Include/GameLogic/Module/Rva00470205Record.h"
typedef _STL::map<int, Rva00470205Record, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00470205Record> > > Rva00470205Map;
typedef _STL::map<int, int> HordeIntMap;
typedef _STL::_Rb_tree<int, _STL::pair<const int, int>, _STL::_Select1st<_STL::pair<const int, int> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > > HordeIntTree;
template<> HordeIntTree::_Link_type HordeIntTree::_M_lower_bound(const int &) const;
namespace _STL {
template <> Rva00470205Map::iterator Rva00470205Map::insert(iterator, const value_type &);
}

class Rva00473F81 : public Rva00470205Map
{
public:
	Rva00469155 &rva00473F81(const int &key);
};

// Get-or-insert by key, building the pair in its own statement before the insert call.
// The pair temporary ends with that statement; its destructors are empty, so insert reads intact storage.
__declspec(noinline) inline Rva00469155 &Rva00473F81::rva00473F81(const int &key)
{
	HordeIntMap::iterator found = ((HordeIntMap *)this)->lower_bound(key);
	iterator i = *(iterator *)&found;
	if (i == end() || key < (*i).first)
	{
		const value_type &entry = *(const value_type *)&Rva00469BEA(key, Rva00469155());
		i = insert(i, entry);
	}
	return *(Rva00469155 *)&(*i).second;
}

// Select-any: HordeContainIface11CSlots.cpp compiles an identical copy; the anchor keeps the rowed body emitted.
// ?bfmeAnchorRva00473F81 absent-from-retail
Rva00469155 &bfmeAnchorRva00473F81(Rva00473F81 *map, const int &key) { return map->rva00473F81(key); }
