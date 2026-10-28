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
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <hash_map>
// Import-inline: every __malloc_alloc<0>::deallocate use here is inlined, and this
// unit's out-of-line copy (referenced from .debug$F alone) is not the one the link keeps.
namespace _STL { template <> __declspec(dllimport) __forceinline void _STLP_CALL __malloc_alloc<0>::deallocate(void *__p, size_t) { free((char *)__p); } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * const * vector<void *,allocator<void *> >::begin()const  { return this->_M_start; } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<unsigned int>::operator()(unsigned int const &x,unsigned int const &y)const  { return x < y; } }
// bfme link decl-only begin
namespace _STL { template <> void swap<_STLP_alloc_proxy<void **, void *, allocator<void *> > >(_STLP_alloc_proxy<void **, void *, allocator<void *> > &, _STLP_alloc_proxy<void **, void *, allocator<void *> > &); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(unsigned int, allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(unsigned int, void *const &, allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void *& vector<void *, allocator<void *> >::operator[](unsigned int); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_set(void **, void **, void **); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::begin(); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::end(); }
namespace _STL { template <> allocator<void *> vector<void *, allocator<void *> >::get_allocator() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::size() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::swap(vector<void *, allocator<void *> > &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?allocate@?$__malloc_alloc@$0A@@_STL@@SAPAXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void *__malloc_alloc<0>::allocate(size_t); }

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

// Nothing here calls the table's destructor; this unit's unreferenced copy of
// it is not retail's (Armor.cpp supplies that one).
namespace _STL {
template <> hashtable<pair<const NameKeyType, ArmorTemplate>, NameKeyType, rts::hash<NameKeyType>,
    _Select1st<pair<const NameKeyType, ArmorTemplate> >, rts::equal_to<NameKeyType>,
    allocator<pair<const NameKeyType, ArmorTemplate> > >::~hashtable();
// The constructor calls _M_initialize_buckets out of line; Armor.cpp's row
// 0x00148DDF is retail's body, this unit's unproven copy is not.
template <> void hashtable<pair<const NameKeyType, ArmorTemplate>, NameKeyType, rts::hash<NameKeyType>,
    _Select1st<pair<const NameKeyType, ArmorTemplate> >, rts::equal_to<NameKeyType>,
    allocator<pair<const NameKeyType, ArmorTemplate> > >::_M_initialize_buckets(size_type);
}

// Instantiate the rowed constructors without the unresolved insertion path.
// See ArmorHashtableRtsInsertDeferred.cpp for the original insertion rows.
template _STL::hash_map<NameKeyType, ArmorTemplate, rts::hash<NameKeyType>, rts::equal_to<NameKeyType> >::hash_map();
