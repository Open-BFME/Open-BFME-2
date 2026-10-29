// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/game/GameEngine/Source/Common
// stlport46
// Open-BFME5: STLport deque<POD>::_M_push_back_aux_v, byte-twin of the
// int specialization at 0x006472C0 (Rva006472C0DequeIntPushBackAux.cpp) --
// same 101 bytes once relocations are masked; only the per-caller ILT reloc
// (the leading branch to the sizing check thunk) differs.

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

#include <deque>

// __node_alloc<1,0>::allocate (STLport node path) otherwise emits a per-TU
// COMDAT that loses to another unit's copy in link order; this explicit
// dllimport+forceinline specialization keeps the body inline and emits none.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__node_alloc<true, 0>::allocate(size_t __n)
{ return (__n > (size_t)_MAX_BYTES) ? __stl_new(__n) : _M_allocate(__n); }
}

// __node_alloc<1,0>::deallocate (STLport node path) otherwise emits a per-TU
// COMDAT that loses to another unit's copy in link order; this explicit
// dllimport+forceinline specialization keeps the body inline and emits none.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

struct Gen_t_00089ce0_p4pod { int a; };

template class _STL::deque<Gen_t_00089ce0_p4pod, _STL::allocator<Gen_t_00089ce0_p4pod> >;
