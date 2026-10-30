// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport46
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
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int vector<void *,allocator<void *> >::size()const  { return (unsigned int)(this->_M_finish - this->_M_start); } }
// Preserve the inline const begin operation without a DLL-import declaration.
namespace _STL { template <> __forceinline void * const * vector<void *,allocator<void *> >::begin()const  { return this->_M_start; } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<unsigned int>::operator()(unsigned int const &x,unsigned int const &y)const  { return x < y; } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * & vector<void *,allocator<void *> >::operator[](unsigned int n) { return *(this->_M_start + n); } }
// bfme link decl-only begin
namespace _STL { template <> void swap<_STLP_alloc_proxy<void **, void *, allocator<void *> > >(_STLP_alloc_proxy<void **, void *, allocator<void *> > &, _STLP_alloc_proxy<void **, void *, allocator<void *> > &); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(unsigned int, allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(unsigned int, void *const &, allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_set(void **, void **, void **); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL {
// end() and the fill insert(pos, n, x) are taken inline, as retail's
// hashtable::_M_initialize_buckets does (59 bytes: it reads _M_finish and
// calls the rowed _M_fill_insert); dllimport + forceinline emits no copy.
template <> __declspec(dllimport) __forceinline void **vector<void*>::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline void vector<void*>::insert(void **pos, size_t n, void *const &x)
{ _M_fill_insert(pos, n, x); }
}
namespace _STL { template <> allocator<void *> vector<void *, allocator<void *> >::get_allocator() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
namespace _STL { template <> void vector<void *, allocator<void *> >::swap(vector<void *, allocator<void *> > &); }
// bfme link decl-only end

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

// Instantiate the owned operations, avoiding unused whole-map definitions.
typedef _STL::pair<const NameKeyType, DamageFX> DamageFXPair;
typedef _STL::hashtable<DamageFXPair, NameKeyType, rts::hash<NameKeyType>,
    _STL::_Select1st<DamageFXPair>, rts::equal_to<NameKeyType>,
    _STL::allocator<DamageFXPair> > DamageFXTable;
typedef _STL::_Hashtable_node<DamageFXPair> DamageFXNode;
typedef _STL::pair<DamageFXMap::iterator, bool> DamageFXInsertResult;
namespace _STL {
template <> DamageFXTable::~hashtable();
template <> void DamageFXTable::erase(DamageFXTable::const_iterator, DamageFXTable::const_iterator);
template <> void DamageFXTable::clear();
}
template DamageFXNode *DamageFXTable::_M_new_node(const DamageFXPair &);
template unsigned int DamageFXTable::_M_bkt_num_key(const NameKeyType &) const;
template void DamageFXTable::_M_erase_bucket(unsigned int, DamageFXNode *, DamageFXNode *);
template DamageFXPair::pair(const NameKeyType &, const DamageFX &);
template DamageFXInsertResult::pair(const DamageFXMap::iterator &, const bool &);
template DamageFXTable::hashtable(unsigned int, const rts::hash<NameKeyType> &,
    const rts::equal_to<NameKeyType> &, const _STL::allocator<DamageFXPair> &);
template DamageFXMap::hash_map();
