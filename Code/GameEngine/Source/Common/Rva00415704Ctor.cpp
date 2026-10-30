// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2
// stlport
// Constructor isolated with its original compiler and STL environment.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include <map>

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}
// Isolated from Rva0041573FCopy.cpp so the independent record-copy rows
// can link while this subsystem's class and table providers are reconciled.
// ??0Rva0022A809Subsystem@@QAE@XZ, retail 0x00415704, 59 bytes.
// Gap between ??1Rva0041579E 0x004156FC and ??0Rva0041573F 0x0041573F; called by matched GameEngine::init 0x0022ED66;
// calls rowed BFME2NativeNetwork::baseConstruct 0x001B4E63 and rowed hash_map ctor 0x00415643; vtable 0x0083A288; byte at +0x20.
#include <hash_map>
#include <cstddef>
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
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail vector<void*> operator[] copy (family2-LK3 row 25):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void *&_STL::vector<void*>::operator[](size_t);
}
// Suppress this TU's non-retail vector<void*> begin/end copies (family2-LK3 rows 6/9):
// the retail copies serve the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void **vector<void*>::begin();
// end() and the fill insert(pos, n, x) are taken inline, as retail's
// hashtable::_M_initialize_buckets does (59 bytes: it reads _M_finish and
// calls the rowed _M_fill_insert); dllimport + forceinline emits no copy.
template <> __declspec(dllimport) __forceinline void **vector<void*>::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline void vector<void*>::insert(void **pos, size_t n, void *const &x)
{ _M_fill_insert(pos, n, x); }
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> size_t vector<void*>::size() const;
}
struct Rva00415643Element { char bytes[1]; };
class BFME2NativeNetwork
{
public:
};
// 0x001B4E63 is the rowed SubsystemInterface ctor. The fourteen-slot base view
// is the one the destructor's unit (Rva00415CABDtor.cpp) and the deleting
// destructor's (OpaqueScalarDeletingDtorsB10.cpp) compile, so the three units
// emit one ??_7Rva0022A809Subsystem@@6B@.
typedef bool Bool;
#include "subsystem_interface.h"

class Rva0022A809Subsystem : public SubsystemInterface
{
public:
	Rva0022A809Subsystem();
	virtual ~Rva0022A809Subsystem();
private:
	_STL::hash_map<int, Rva00415643Element> m_map0C; // +0x0C
	unsigned char m_20; // +0x20
};
Rva0022A809Subsystem::Rva0022A809Subsystem()
	: m_20(0)
{
}
