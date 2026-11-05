// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ??0Rva004121B2@@QAE@XZ @0x004121B2 31B: hash_map-shape default ctor, one more
// twin of 0x00360B99 (and of 0x003A393A): the same 31B pushing 0x64 with three
// empty functor temporaries, calling the hashtable ctor fold at 0x00411AC7.
// Its only callers are the four file-scope initializers below, whose cleanups
// (rowed 0x007B8247/821F/8229/8233) tear the maps down through three different
// hashtable destructors, so the value types differ and fold here; the owner is
// unknown and the ctor keeps an honest address name. The layout is a
// hashtable's: 0x14 bytes per map, the stride between the four globals.
// The fold keeps its own EH handler operand; the call binds the fold's owner
// row (StlSweepW5Rva00411AC7.cpp) by its name, so no pin is needed.
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
#include <stdlib.h>
// Keep the inlined STLport __malloc_alloc<0>::deallocate without emitting an
// optimised out-of-line copy that would shadow retail's /Od body at 0x23A70
// (STLMallocAlloc0Deallocate.cpp).
namespace _STL { template <> __declspec(dllimport) __forceinline void _STLP_CALL __malloc_alloc<0>::deallocate(void *__p, size_t) { free((char *)__p); } }
namespace _STL { template <> inline allocator<void *>::~allocator() _STLP_NOTHROW {} }
// bfme link decl-only begin
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_set(void **, void **, void **); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail vector<void*> operator[] copy (family2-LK3 row 25):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void *&_STL::vector<void*>::operator[](size_t);
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> size_t vector<void*>::size() const;
}
// Suppress this TU's non-retail vector<void*> begin/end copies (family2-LK3 rows 6/9):
// the retail copies serve the link. Plain declaration-only form (no __imp_).
namespace _STL {
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

// Retail calls 0x00411AC7, the rowed int-keyed hashtable ctor
// (StlSweepW5Rva00411AC7.cpp's hash_map<int,Rva00411AC7Element>, element declared
// as there): the member is that table. A declaration-only specialization of its
// ctor would zero the hasher temporary (xor/stosb), so the template stays visible,
// as in ArmorHashMapCtor003A393A.cpp.
struct Rva00411AC7Element {Rva00411AC7Element();Rva00411AC7Element(const Rva00411AC7Element&);Rva00411AC7Element&operator=(const Rva00411AC7Element&);~Rva00411AC7Element(){}char bytes[8]; bool operator==(const Rva00411AC7Element&)const;};
typedef _STL::hash_map<int, Rva00411AC7Element> Rva00411AC7Map;
typedef Rva00411AC7Map::value_type Rva00411AC7Pair;
typedef _STL::hashtable<Rva00411AC7Pair, int, Rva00411AC7Map::hasher,
	_STL::_Select1st<Rva00411AC7Pair>, Rva00411AC7Map::key_equal,
	Rva00411AC7Map::allocator_type> Rva00411AC7Hashtable;

class Rva004121B2
{
public:
	Rva004121B2();
private:
	Rva00411AC7Hashtable m_table;
};

Rva004121B2::Rva004121B2() : m_table(100, Rva00411AC7Map::hasher(), Rva00411AC7Map::key_equal(), Rva00411AC7Map::allocator_type()) {}

void __cdecl rva007B8247();
void __cdecl rva007B821F();
void __cdecl rva007B8229();
void __cdecl rva007B8233();

struct BfmeAptScreenRefStorage;
extern BfmeAptScreenRefStorage g_aptScreenReferences;
// RVA 0x00A02FE4 is AptComponentWindowLookup.cpp's owned component-window table.
extern unsigned int AptComponentWindowDataTableStorage[5];
unsigned g_Va00E02FF8;	// retail RVA 0x00A02FF8 (.bss), defined here
struct Rva00411112GlobalTable;
extern Rva00411112GlobalTable g_Va00E0300C;

struct Rva004121B2HashMapInits
{
	static void rva007AFF1A();
	static void rva007AFF30();
	static void rva007AFF46();
	static void rva007AFF5C();
};

// 0x007AFF1A (22B): Rva004121B2() on VA 0x00E02FD0, atexit(0x007B8247 -> hashtable dtor 0x004111CC)
void Rva004121B2HashMapInits::rva007AFF1A()
{
	( (Rva004121B2 *)&g_aptScreenReferences )->Rva004121B2::Rva004121B2();
	atexit( rva007B8247 );
}

// 0x007AFF30 (22B): Rva004121B2() on VA 0x00E02FE4, atexit(0x007B821F -> hashtable dtor 0x00410C42)
void Rva004121B2HashMapInits::rva007AFF30()
{
	( (Rva004121B2 *)AptComponentWindowDataTableStorage )->Rva004121B2::Rva004121B2();
	atexit( rva007B821F );
}

// 0x007AFF46 (22B): Rva004121B2() on VA 0x00E02FF8, atexit(0x007B8229 -> hashtable dtor 0x00410C7B)
void Rva004121B2HashMapInits::rva007AFF46()
{
	( (Rva004121B2 *)&g_Va00E02FF8 )->Rva004121B2::Rva004121B2();
	atexit( rva007B8229 );
}

// 0x007AFF5C (22B): Rva004121B2() on VA 0x00E0300C, atexit(0x007B8233 -> hashtable dtor 0x00410C7B)
void Rva004121B2HashMapInits::rva007AFF5C()
{
	( (Rva004121B2 *)&g_Va00E0300C )->Rva004121B2::Rva004121B2();
	atexit( rva007B8233 );
}
