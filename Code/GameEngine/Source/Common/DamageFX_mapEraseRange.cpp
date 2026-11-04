// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport46
// Retail 0x00056B0A range erase and its typed STLport table provider.
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

#include "../../Include/Common/DamageFXClass.h"

namespace rts
{

template <class _Key>
struct hash
{
};

template <>
struct hash<NameKeyType>
{
	__declspec(dllimport) __forceinline unsigned int operator()(const NameKeyType &key) const
	{
		return (unsigned int)key;
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

// Instantiate range erase without the unused whole-map operations.
template void DamageFXMap::erase(DamageFXMap::iterator, DamageFXMap::iterator);
