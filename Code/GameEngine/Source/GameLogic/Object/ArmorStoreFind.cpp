// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva001D901B@Rva001D901B@@QBEPBVArmorTemplate@@ABVAsciiString@@@Z @0x001D901B 47B unlock.
// Evidence: NameKeyGenerator->nameToKey 0x0009FA65 rowed plus hashtable _M_find
// 0x002888D4 rowed; lea ecx [esi+0xc] proves map at +0xc; callers 0x001D908A
// 0x001D910C 0x001D9130 0x00339544 use AsciiString arg and ArmorTemplate result.
#include <hash_map>
#include <cstddef>
// _M_find (retail's 47-byte body at 0x002888D4) inlines the key hash, the bucket
// count and the bucket read; declaration-only forms of those made this TU's copy
// call them. Bind to the kept retail copies instead of emitting them.
namespace _STL { template <> __declspec(dllimport) __forceinline void * const * vector<void *,allocator<void *> >::begin()const  { return this->_M_start; } }
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int vector<void *,allocator<void *> >::size()const  { return (unsigned int)(this->_M_finish - this->_M_start); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void * const & vector<void *,allocator<void *> >::operator[](unsigned int n)const  { return *(this->_M_start + n); } }
// Suppress this TU's non-retail non-const vector<void*> begin/end copies.
namespace _STL {
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}

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
// Identity hash (row 0x00169440); inlined into _M_find as retail does.
namespace rts { template <> __declspec(dllimport) __forceinline size_t hash<NameKeyType>::operator()(const NameKeyType &value) const { return (size_t)value; } }

#include "../../../Include/GameLogic/Armor.h"

#include "ascii_string.h"

#include "../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

typedef std::hash_map<
	NameKeyType,
	ArmorTemplate *,
	rts::hash<NameKeyType>,
	std::equal_to<NameKeyType> > ArmorTemplateMap;

class Rva001D901B
{
public:
	const ArmorTemplate *rva001D901B(const AsciiString &name) const;
private:
	unsigned char m_pad[12];
	ArmorTemplateMap m_map;
};

const ArmorTemplate *Rva001D901B::rva001D901B(const AsciiString &name) const
{
	NameKeyType key = TheNameKeyGenerator->nameToKey(name);
	ArmorTemplateMap::const_iterator it = m_map.find(key);
	if (it == m_map.end())
		return 0;
	return (*it).second;
}
