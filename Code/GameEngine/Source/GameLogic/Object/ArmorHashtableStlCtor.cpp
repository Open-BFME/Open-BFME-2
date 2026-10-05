// cl: /Ireference/shims/bfme2_ascii /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ??0?$hash_map@W4NameKeyType@@VArmorTemplate@@U?$hash@W4NameKeyType@@@rts@@U?$equal_to@W4NameKeyType@@@_STL@@V?$allocator@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@6@@_STL@@QAE@XZ
// @ 0x0014918D (31B). hash_map<NameKeyType ArmorTemplate rts::hash _STL::equal_to>
// default ctor: builds the single hashtable member with 100 buckets plus three
// empty params. Evidence: 31B body pushes 0x64 with three slavings of [ebp-1]
// then calls the rowed Armor hashtable ctor 0x00148F7E (dup of 0x00360B59);
// caller 0x001491AC constructs the member at +0x2bf4c just before the lock at
// +0x2bf60 (0x14 gap = hashtable size). Same pattern as the rowed rts
// twin ??0hash_map rts 0x002898E3/31 in ArmorHashtableRtsCtor.cpp.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <hash_map>
#include <cstddef>

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

namespace rts
{

template <typename T> struct hash
{
	size_t operator()(const T &value) const;
};

}

class ArmorTemplate
{
public:
	float m_damageCoefficient[38]; // DAMAGE_NUM_TYPES, ZH count
};

typedef std::hash_map<
	NameKeyType,
	ArmorTemplate,
	rts::hash<NameKeyType>,
	std::equal_to<NameKeyType> > ArmorStlMap;

template _STL::hash_map<NameKeyType, ArmorTemplate, rts::hash<NameKeyType>, std::equal_to<NameKeyType> >::hash_map();
