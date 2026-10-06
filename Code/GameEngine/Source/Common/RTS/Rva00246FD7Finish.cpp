// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??0Rva00246FD7@@QAE@XZ @0x00246FD7 31B: hashtable wrapper ctor via the Armor hashtable
// twin 0x0024619A with 100 buckets. Evidence: the 31B body pushes 0x64 with three copies of
// [ebp-1]; retail's call target is the dup 0x0024619A of rowed 0x00360B59, not the copy
// the default spelling resolves to. ICF twin needs a unique equal_to spelling in its own
// namespace so the call binds to this TU's own copy, the same recipe as Rva002D0C71.
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

namespace Rva00246FD7Twin
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

typedef _STL::hashtable<_STL::pair<const NameKeyType, ArmorTemplate>, NameKeyType, rts::hash<NameKeyType>, _STL::_Select1st<_STL::pair<const NameKeyType, ArmorTemplate> >, Rva00246FD7Twin::equal_to<NameKeyType>, _STL::allocator<_STL::pair<const NameKeyType, ArmorTemplate> > > ArmorHt00246FD7;

class Rva00246FD7
{
public:
	ArmorHt00246FD7 m_ht;
	Rva00246FD7();
};

Rva00246FD7::Rva00246FD7() : m_ht(100, rts::hash<NameKeyType>(), Rva00246FD7Twin::equal_to<NameKeyType>(), _STL::allocator<_STL::pair<const NameKeyType, ArmorTemplate> >()) {}