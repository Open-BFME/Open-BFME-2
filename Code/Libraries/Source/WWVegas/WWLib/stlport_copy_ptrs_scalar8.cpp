// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$__copy_ptrs@PBUBfmeAsciiScalarValue8@@PAU1@@_STL@@YAPAUBfmeAsciiScalarValue8@@PBU1@0PAU1@ABU__false_type@0@@Z @0x0031BDA4 29B
// __copy_ptrs for BfmeAsciiScalarValue8 via rowed __copy 0x0031BA18
// (Rva0031BA18Copy, 5-push forwarding with tag+0 ignored). Callers in
// stlport_vector_scalar8_assign.cpp. Evidence: chain from 0x0031BA18.
#include "ascii_string.h"

struct BfmeAsciiScalarValue8
{
public:
	BfmeAsciiScalarValue8();
	BfmeAsciiScalarValue8(const BfmeAsciiScalarValue8 &);
	BfmeAsciiScalarValue8 &operator=(const BfmeAsciiScalarValue8 &);
	AsciiString text; // +0x00
	unsigned int value; // +0x04
};

struct OpaqueRefElement4
{
    OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
};

struct Rva002C99FB
{
    int m_first;
    OpaqueRefElement4 m_second;
    Rva002C99FB &operator=(const Rva002C99FB &other);
};

Rva002C99FB *Rva0031BA18Copy(Rva002C99FB *first, Rva002C99FB *last, Rva002C99FB *dest);

namespace _STL {
struct __false_type
{
};
template <class InputIter, class OutputIter>
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result, const __false_type &tag);
}

typedef Rva002C99FB *(__cdecl *FiveCopyFn)(Rva002C99FB *, Rva002C99FB *, Rva002C99FB *, const void *, const void *);

template <>
inline BfmeAsciiScalarValue8 *_STL::__copy_ptrs<const BfmeAsciiScalarValue8 *, BfmeAsciiScalarValue8 *>(const BfmeAsciiScalarValue8 *first, const BfmeAsciiScalarValue8 *last, BfmeAsciiScalarValue8 *result, const __false_type &tag)
{
    __false_type local;
    return (BfmeAsciiScalarValue8 *)((FiveCopyFn)&Rva0031BA18Copy)(
        (Rva002C99FB *)first, (Rva002C99FB *)last, (Rva002C99FB *)result, (const void *)&local, (const void *)0);
}

// This specialization is a header inline in the copier unit; the anchor is not retail code.
#pragma inline_depth(0)
// ?_bfmeBfmeAsciiScalarValue8CopyPtrsInlineAnchor@@YAXXZ absent-from-retail
void _bfmeBfmeAsciiScalarValue8CopyPtrsInlineAnchor()
{
    _STL::__false_type tag;
    _STL::__copy_ptrs<const BfmeAsciiScalarValue8 *, BfmeAsciiScalarValue8 *>(
        static_cast<const BfmeAsciiScalarValue8 *>(0),
        static_cast<const BfmeAsciiScalarValue8 *>(0),
        static_cast<BfmeAsciiScalarValue8 *>(0), tag);
}
#pragma inline_depth()
