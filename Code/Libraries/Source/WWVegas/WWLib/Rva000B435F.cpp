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

struct Rva000B435F
{
	int m_a;
	AsciiString m_s;
	int m_b;
	Rva000B435F &operator=(const Rva000B435F &o);
};

Rva000B435F &Rva000B435F::operator=(const Rva000B435F &o)
{
	m_a = o.m_a;
	m_s.setCopyInline(o.m_s);
	m_b = o.m_b;
	return *this;
}

template class _STL::vector<Rva000B435F, _STL::allocator<Rva000B435F> >;
