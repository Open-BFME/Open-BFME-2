// cl: -DNDEBUG -MD -EHsc -D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport46
//
// ?_M_bkt_num_key@?$hashtable@U?$pair@PBDURva009D7350Mapped@@@_STL@@PBDU?$hash@PBD@2@U?$_Select1st@U?$pair@PBDURva009D7350Mapped@@@_STL@@@2@U?$equal_to@PBD@2@V?$allocator@U?$pair@PBDURva009D7350Mapped@@@_STL@@@2@@_STL@@ABEIABQBDI@Z
// retail 0x0060C9A7, 23 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/Libraries/Source/WWVegas/WWLib/Rva009D7350BktNumKey.cpp
// (reference/open-bfme-1 @ 6d943426). Compiled /Os the donor emits this body
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is instantiated here; the donor's
// other instantiation is omitted.
// The 53-byte body at 0x009D7350 is the same STLport hashtable member for the
// same shape; identity here is address-derived from the mangled name.

#include <hash_map>

// The bucket lookup naturally emits STLport's complete retail string-hash
// inline (0x0002BA61). Its row lives here with this real caller.

// The rowed /Od size provider owns the standalone body. Keep this
// consumer's pointer-span calculation inline without a competing copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
size_t vector<void*>::size() const
{ return size_t(this->_M_finish - this->_M_start); }
}

struct Rva009D7350Mapped
{
	char m_data[4];
};

typedef _STL::pair<const char *, Rva009D7350Mapped> Rva009D7350Pair;

typedef _STL::hashtable<Rva009D7350Pair, const char *, _STL::hash<const char *>,
	_STL::_Select1st<Rva009D7350Pair>, _STL::equal_to<const char *>,
	_STL::allocator<Rva009D7350Pair> > Rva009D7350Hashtable;

template unsigned int Rva009D7350Hashtable::_M_bkt_num_key(const char * const &) const;
// _M_bkt_num(obj, n) forwards to _M_bkt_num_key(_M_get_key(obj), n); the key
// is the pair's first member, so it is retail's tail jump 0x0060C9BE.
template unsigned int Rva009D7350Hashtable::_M_bkt_num(const Rva009D7350Pair &, unsigned int) const;
