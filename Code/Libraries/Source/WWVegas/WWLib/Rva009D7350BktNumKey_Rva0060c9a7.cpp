// cl: -DNDEBUG -MD -EHsc -D_STLP_USE_STATIC_LIB /Os -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
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

struct Rva009D7350Mapped
{
	char m_data[4];
};

typedef _STL::pair<const char *, Rva009D7350Mapped> Rva009D7350Pair;

typedef _STL::hashtable<Rva009D7350Pair, const char *, _STL::hash<const char *>,
	_STL::_Select1st<Rva009D7350Pair>, _STL::equal_to<const char *>,
	_STL::allocator<Rva009D7350Pair> > Rva009D7350Hashtable;

template unsigned int Rva009D7350Hashtable::_M_bkt_num_key(const char * const &) const;