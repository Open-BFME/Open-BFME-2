// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ??0Rva003A393A@@QAE@XZ @0x003A393A 31B: Armor hash_map-shape default ctor twin of 0x00360B99.
// Identical 31B pushing 0x64 with three empty params calling the Armor hashtable ctor
// (rowed 0x00360B59, dup 0x003A37FA). Evidence: same bytes except call target; caller
// 0x003A3959 constructs member at +4 through this body; landing unblocks 0x003A3959/50
// and 0x003A39A7/471. Honest ctor name for an unknown owner; hashtable layout matches
// ArmorStoreCtor's ArmorTemplateMap.
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
	float m_damageCoefficient[38];
};

typedef std::hash_map<
	NameKeyType,
	ArmorTemplate,
	rts::hash<NameKeyType>,
	std::equal_to<NameKeyType> > ArmorTemplateMap;

typedef ArmorTemplateMap::value_type ArmorPair003A393A;
typedef ArmorTemplateMap::hasher ArmorHasher003A393A;
typedef ArmorTemplateMap::key_equal ArmorEqual003A393A;
typedef ArmorTemplateMap::allocator_type ArmorAlloc003A393A;

typedef _STL::hashtable<
	ArmorPair003A393A,
	NameKeyType,
	ArmorHasher003A393A,
	_STL::_Select1st<ArmorPair003A393A>,
	ArmorEqual003A393A,
	ArmorAlloc003A393A> ArmorHashtable003A393A;

class Rva003A393A
{
public:
	Rva003A393A();
private:
	ArmorHashtable003A393A m_table;
};

Rva003A393A::Rva003A393A() : m_table(100, ArmorHasher003A393A(), ArmorEqual003A393A(), ArmorAlloc003A393A()) {}
