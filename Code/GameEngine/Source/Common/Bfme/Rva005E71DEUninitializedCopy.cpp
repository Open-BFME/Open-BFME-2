// cl: /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$__uninitialized_copy@PAURva005E71C6Ref@@PAU1@@_STL@@YAPAURva005E71C6Ref@@PAU1@00ABU__false_type@0@@Z
// @0x005E71DE 38B: STLport __uninitialized_copy over a 4-byte intrusive
// reference (the pointee's count sits at +0x28), the sibling of the rowed
// __uninitialized_fill_n 0x005E7204 (Rva005E7204Fill.cpp) and of the rowed
// placement copy 0x005E71C6 (Rva005E71C6Assign.cpp). The banked attempt wrote
// the loop by hand with its two pointer adds in the opposite order; the
// vendored template body, exceptions off, gives retail's order. Callers
// 0x005E7247, 0x005E81CC, 0x005E8217.
//
// The element copy goes to _Construct<Rva005E71C6Ref, Rva005E71C6Ref>, only
// declared here: the rowed 24-byte placement copy at 0x005E71C6 compiled as
// that specialization (with the row's flags) is byte-identical, so the
// template name is pinned there. The reference type keeps an address-derived
// name; its pointee layout beyond the count is not modelled.
#include <memory>

struct Rva005E71C6Object;

struct Rva005E71C6Ref
{
	Rva005E71C6Object *m_object;
};

namespace _STL
{
template <> void _Construct<Rva005E71C6Ref, Rva005E71C6Ref>(Rva005E71C6Ref *p, const Rva005E71C6Ref &v);
}

template Rva005E71C6Ref *_STL::__uninitialized_copy<Rva005E71C6Ref *, Rva005E71C6Ref *>(Rva005E71C6Ref *, Rva005E71C6Ref *, Rva005E71C6Ref *, const _STL::__false_type &);
