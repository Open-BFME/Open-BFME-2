// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ??0Rva003A393A@@QAE@XZ @0x003A393A 31B: Armor hash_map-shape default ctor twin of 0x00360B99.
// Identical 31B pushing 0x64 with three empty params calling the Armor hashtable ctor
// (rowed 0x00360B59, dup 0x003A37FA). Evidence: same bytes except call target; caller
// 0x003A3959 constructs member at +4 through this body; landing unblocks 0x003A3959/50
// and 0x003A39A7/471. Honest ctor name for an unknown owner; hashtable layout matches
// ArmorStoreCtor's ArmorTemplateMap.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <hash_map>
// map<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); an explicit specialization declaration
// suppresses this TU's copy so callers bind retail's instead.
namespace _STL {
template <> bool less<unsigned int>::operator()(const unsigned int &a, const unsigned int &b) const;
}
#include <cstddef>
// Import-inline: every __malloc_alloc<0>::deallocate use here is inlined, and this
// unit's out-of-line copy (referenced from .debug$F alone) is not the one the link keeps.
namespace _STL { template <> __declspec(dllimport) __forceinline void _STLP_CALL __malloc_alloc<0>::deallocate(void *__p, size_t) { free((char *)__p); } }
// bfme link decl-only begin
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void *& vector<void *, allocator<void *> >::operator[](unsigned int); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_set(void **, void **, void **); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
namespace _STL { template <> allocator<void *>::~allocator(); }
// bfme link decl-only end
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> size_t vector<void*>::size() const;
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
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

#include "../../../Include/GameLogic/Armor.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> hashtable<pair<NameKeyType const ,ArmorTemplate>,NameKeyType,rts::hash<NameKeyType>,_Select1st<pair<NameKeyType const ,ArmorTemplate> >,equal_to<NameKeyType>,allocator<pair<NameKeyType const ,ArmorTemplate> > >::~hashtable(); }

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

// Retail calls 0x003A37FA, the rowed int-keyed hashtable ctor (StlSweepW5Rva003A37FA.cpp's
// hash_map<int,Rva003A37FAElement>), not the ArmorTemplate one at 0x00360B59: the member is that table.
struct Rva003A37FAElement {Rva003A37FAElement();Rva003A37FAElement(const Rva003A37FAElement&);Rva003A37FAElement&operator=(const Rva003A37FAElement&);~Rva003A37FAElement(){}char bytes[8]; bool operator==(const Rva003A37FAElement&)const;};
typedef _STL::hash_map<int, Rva003A37FAElement> Rva003A37FAMap;
typedef _STL::hashtable<Rva003A37FAMap::value_type, int, Rva003A37FAMap::hasher,
	_STL::_Select1st<Rva003A37FAMap::value_type>, Rva003A37FAMap::key_equal, Rva003A37FAMap::allocator_type> Rva003A37FATable;

class Rva003A393A
{
public:
	Rva003A393A();
private:
	Rva003A37FATable m_table;
};

Rva003A393A::Rva003A393A()
	: m_table(100,
		Rva003A37FAMap::hasher(),
		Rva003A37FAMap::key_equal(),
		Rva003A37FAMap::allocator_type()) {}
