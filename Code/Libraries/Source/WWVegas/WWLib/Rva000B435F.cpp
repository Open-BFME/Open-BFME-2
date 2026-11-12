// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva000B435F@Rva000B435F@@QAEAAU0@ABU0@@Z @0x000B435F 37B.
// Copy-assignment for 12-byte struct {int +0, AsciiString +4, int +8}.
// Evidence: copies [edi] to [esi], calls ?set@?$StringBase@D@@QAEXABV1@@Z
// for +4, copies [edi+8] to [esi+8], returns this; caller at 0x000B684C
// strides 0xC over the same 12-byte elements.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
#include "ascii_string.h"

#include "Rva000B435F.h"

Rva000B435F &Rva000B435F::operator=(const Rva000B435F &o)
{
	m_a = o.m_a;
	m_s.setCopyInline(o.m_s);
	m_b = o.m_b;
	return *this;
}

// Only the rowed members. A whole-class instantiation also emitted this TU's
// range erase, which differs from retail (stlport_vector_rva000b435f_erase.cpp,
// 0x000C059B) and, first in link order, was kept; clear() calls that one.
typedef _STL::vector<Rva000B435F, _STL::allocator<Rva000B435F> > Rva000B435FVector;
template <> Rva000B435F *Rva000B435FVector::erase(Rva000B435F *, Rva000B435F *);
template void Rva000B435FVector::clear();
template Rva000B435F *_STL::__copy<Rva000B435F *, Rva000B435F *, int>(Rva000B435F *, Rva000B435F *, Rva000B435F *, const _STL::random_access_iterator_tag &, int *);
