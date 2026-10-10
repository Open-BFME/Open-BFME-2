// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?_M_new_node@?$hashtable@U?$pair@$$CBW4NameKeyType@@VDamageFX@@@_STL@@W4NameKeyType@@U?$hash@W4NameKeyType@@@rts@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@VDamageFX@@@_STL@@@2@U?$equal_to@W4NameKeyType@@@5@V?$allocator@U?$pair@$$CBW4NameKeyType@@VDamageFX@@@_STL@@@2@@_STL@@AAEPAU?$_Hashtable_node@U?$pair@$$CBW4NameKeyType@@VDamageFX@@@_STL@@@2@ABU?$pair@$$CBW4NameKeyType@@VDamageFX@@@2@@Z,
// retail 0x00360939, 40 bytes. Dedicated TU.
//
// STLport 4.5.3 hashtable::_M_new_node for hash_map<NameKeyType DamageFX> out
// of the real <hash_map> header. Allocate size 0x788 is 4 (next) + 4 (key) +
// 0x780 (value) so DamageFX is 0x780 bytes which matches the rep-movsd 0x1E0
// in the rowed _Construct at 0x00360917. Calls the rowed 2-arg byte allocator
// at 0x000307F0 via the bfmealloc shim and the rowed _Construct at 0x00360917.
// Caller at 0x00360A27 in 0x003609F7. Shape is identical to the /O1 sibling
// _M_new_node at 0x0041930C in stlport_pod_hash_bodies.cpp.

#define _STLP_NO_EXCEPTIONS 1
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
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
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class DamageFX
{
public:
	int m_valueWords[0x1E0];
};

inline bool operator==(const DamageFX &x, const DamageFX &y)
{
	return x.m_valueWords[0] == y.m_valueWords[0];
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

typedef _STL::hash_map<NameKeyType, DamageFX, rts::hash<NameKeyType>, rts::equal_to<NameKeyType> > DamageFXMap;

template class _STL::hash_map<NameKeyType, DamageFX, rts::hash<NameKeyType>, rts::equal_to<NameKeyType> >;
