// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2's 64-byte BfmeVectorRecord000BDF17 vector allocation/copy helper at RVA 0xC24A0.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include <vector>
// The record dtor calls the kept vector<AsciiString> dtor (0x2CC70); a
// declaration-only specialization stops this TU emitting its own copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
}
#include "../../../../GameEngine/Include/Common/BfmeVectorRecord000BDF17.h"
BfmeVectorRecord000BDF17::~BfmeVectorRecord000BDF17() {}
namespace _STL {
template <> void _Construct<BfmeVectorRecord000BDF17, BfmeVectorRecord000BDF17>(BfmeVectorRecord000BDF17 *, const BfmeVectorRecord000BDF17 &);
}
// No row here needs the four members that build a T() (the element's
// default ctor is unrowed): declare them specialized so the class-wide
// instantiation does not emit them.
namespace _STL {
template <> vector<BfmeVectorRecord000BDF17, allocator<BfmeVectorRecord000BDF17> >::vector(size_t);
template <> void vector<BfmeVectorRecord000BDF17, allocator<BfmeVectorRecord000BDF17> >::push_back();
template <> BfmeVectorRecord000BDF17 *vector<BfmeVectorRecord000BDF17, allocator<BfmeVectorRecord000BDF17> >::insert(BfmeVectorRecord000BDF17 *);
template <> void vector<BfmeVectorRecord000BDF17, allocator<BfmeVectorRecord000BDF17> >::resize(size_t);
// The assignment is rowed in BfmeVectorRecord000BDF17Ctor.cpp (retail 0x000C697B,
// which calls __copy_ptrs out of line); this unit's shim would inline it.
template <> vector<BfmeVectorRecord000BDF17, allocator<BfmeVectorRecord000BDF17> > &vector<BfmeVectorRecord000BDF17, allocator<BfmeVectorRecord000BDF17> >::operator=(const vector<BfmeVectorRecord000BDF17, allocator<BfmeVectorRecord000BDF17> > &);
}
template class _STL::vector<BfmeVectorRecord000BDF17, _STL::allocator<BfmeVectorRecord000BDF17> >;
// The rowed allocate/copy helper 0x000C24A0 has no other user here once the
// assignment is declaration-only.
template BfmeVectorRecord000BDF17 *_STL::vector<BfmeVectorRecord000BDF17, _STL::allocator<BfmeVectorRecord000BDF17> >::_M_allocate_and_copy<const BfmeVectorRecord000BDF17 *>(size_t, const BfmeVectorRecord000BDF17 *, const BfmeVectorRecord000BDF17 *);
