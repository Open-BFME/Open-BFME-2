// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?resize@?$hashtable@U?$pair@$$CBW4NameKeyType@@VDamageFX@@@_STL@@W4NameKeyType@@U?$hash@W4NameKeyType@@@rts@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@VDamageFX@@@_STL@@@2@U?$equal_to@W4NameKeyType@@@5@V?$allocator@U?$pair@$$CBW4NameKeyType@@VDamageFX@@@_STL@@@2@@_STL@@QAEXI@Z,
// retail 0x0016DD70, 252 bytes. Dedicated TU.
//
// STLport body out of the real <hash_map> header for the DamageFX name-key
// map. The retail rehash loop hashes each node as (node[8] << 16) + node[4]
// — the key word plus the first DamageFX word — so the TU-local rts hash
// below reads exactly those two dwords through the key reference (the only
// construct that reproduces the retail loads). Flags mirror DamageFX.cpp.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class DamageFX
{
	int m_first;
};

namespace rts
{

template<class _Key>
struct hash
{
};

template<>
struct hash<NameKeyType>
{
	unsigned int operator()(const NameKeyType &key) const
	{
		const unsigned int *words = (const unsigned int *)&key;
		return (words[1] << 16) + words[0];
	}
};

template<class _Key>
struct equal_to
{
	bool operator()(const _Key &left, const _Key &right) const
	{
		return left == right;
	}
};

}

typedef _STL::hash_map<NameKeyType, DamageFX, rts::hash<NameKeyType>, rts::equal_to<NameKeyType> > DamageFXMap;

// Anchor: emits the hashtable resize COMDAT this TU exists to place.
void damageFXMapResizeAnchor(DamageFXMap &map, unsigned int hint)
{
	map.resize(hint);
}
