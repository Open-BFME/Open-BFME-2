// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??0Rva002D0C71@@QAE@XZ @0x002D0C71 31B: hashtable wrapper ctor via Armor hashtable 0x002D0B5A slash 0x00360B59 with 100 buckets. Evidence: caller 0x002D0E14 constructs member at +0x14; three empty args share one byte at ebp-1; returns this. ICF twin needs unique equal_to spelling same code.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

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

namespace Rva002D0C71Twin
{
template <typename T> struct equal_to
{
	bool operator()(const T &a, const T &b) const;
};
}

class ArmorTemplate
{
public:
	float m_damageCoefficient[38];
};

typedef _STL::hashtable<_STL::pair<const NameKeyType, ArmorTemplate>, NameKeyType, rts::hash<NameKeyType>, _STL::_Select1st<_STL::pair<const NameKeyType, ArmorTemplate> >, Rva002D0C71Twin::equal_to<NameKeyType>, _STL::allocator<_STL::pair<const NameKeyType, ArmorTemplate> > > ArmorHt002D0C71;

class Rva002D0C71
{
public:
	ArmorHt002D0C71 m_ht;
	Rva002D0C71();
};

Rva002D0C71::Rva002D0C71() : m_ht(100, rts::hash<NameKeyType>(), Rva002D0C71Twin::equal_to<NameKeyType>(), _STL::allocator<_STL::pair<const NameKeyType, ArmorTemplate> >()) {}
