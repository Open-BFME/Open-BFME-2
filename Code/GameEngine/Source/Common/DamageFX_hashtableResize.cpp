// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport46
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
#include <vector>
// vector<void*> members kept from this unit's link copies, moved beside <vector> so
// they precede every use. Import-inline: these members are inlined at every use here,
// and this unit's out-of-line copies (referenced from .debug$F alone) are not the ones
// the link keeps.
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int vector<void *,allocator<void *> >::size()const  { return (unsigned int)(this->_M_finish - this->_M_start); } }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL {
template <> __declspec(dllimport) __forceinline _Vector_base<void *, allocator<void *> >::~_Vector_base() { if (_M_start != 0) _M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start); }
}
#include <hash_map>
// Import-inline: every __malloc_alloc<0>::deallocate use here is inlined, and this
// unit's out-of-line copy (referenced from .debug$F alone) is not the one the link keeps.
namespace _STL { template <> __declspec(dllimport) __forceinline void _STLP_CALL __malloc_alloc<0>::deallocate(void *__p, size_t) { free((char *)__p); } }
// Bind to the kept retail copy instead of emitting this unit's own.
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * & vector<void *,allocator<void *> >::operator[](unsigned int n) { return *(this->_M_start + n); } }
// bfme link decl-only begin
namespace _STL { template <> allocator<void *> vector<void *, allocator<void *> >::get_allocator() const; }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??$advance@PBIH@_STL@@YAXAAPBIH@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void advance<unsigned int const *,int>(unsigned int const * &,int); }
// Suppress this TU's non-retail copy of ??$__advance@PBIH@_STL@@YAXAAPBIHABUrandom_access_iterator_tag@0@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void __advance<unsigned int const *,int>(unsigned int const * &,int,random_access_iterator_tag const &); }
// Suppress this TU's non-retail copy of ?allocate@?$__malloc_alloc@$0A@@_STL@@SAPAXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void *__malloc_alloc<0>::allocate(size_t); }

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
