// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// Retail RVA 0x002896AA, 64 bytes.
// ??0?$hashtable@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@W4NameKeyType@@U?$hash@W4NameKeyType@@@rts@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@2@U?$equal_to@W4NameKeyType@@@5@V?$allocator@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@2@@_STL@@QAE@IABU?$hash@W4NameKeyType@@@rts@@ABU?$equal_to@W4NameKeyType@@@3@ABV?$allocator@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@1@@Z
// STLport hashtable ctor (n, hash, equal, alloc) for hash_map<NameKeyType ArmorTemplate rts::hash rts::equal_to>.
// Evidence: callee vector<uint> ctor 0x00025100 and rowed Armor _M_initialize_buckets 0x00148DDF (rts::equal_to spelling, same as Armor.cpp rows);
// caller 0x002898E3 is the 31B hash_map default ctor pushing 0x64 with three empty params; its callers at 0x00289B84/0x00289BA9 sit in ctor 0x00289ABD
// (vtable 0x007FB8F4, base BFME2NativeNetwork 0x001B4E63, two 0x14B heap hash_maps at +0x0C/+0x10). ZH Armor.h defines this map with rts::equal_to
// (vs ArmorStoreCtor rts-free _STL::equal_to twin at 0x00360B59); rts::equal_to pattern follows DamageFX_hashtableNewNode.cpp.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <hash_map>

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class ArmorTemplate
{
public:
	float m_damageCoefficient[38];
};

inline bool operator==(const ArmorTemplate &x, const ArmorTemplate &y)
{
	return x.m_damageCoefficient[0] == y.m_damageCoefficient[0];
}

namespace rts
{

template <class _Key>
struct hash
{
};

template <>
struct hash<NameKeyType>
{
	unsigned int operator()(const NameKeyType &key) const
	{
		const unsigned int *words = (const unsigned int *)&key;
		return (words[1] << 16) + words[0];
	}
};

template <class _Key>
struct equal_to
{
	bool operator()(const _Key &left, const _Key &right) const
	{
		return left == right;
	}
};

}

typedef _STL::hash_map<NameKeyType, ArmorTemplate, rts::hash<NameKeyType>, rts::equal_to<NameKeyType> > ArmorRtsMap;

template class _STL::hash_map<NameKeyType, ArmorTemplate, rts::hash<NameKeyType>, rts::equal_to<NameKeyType> >;
