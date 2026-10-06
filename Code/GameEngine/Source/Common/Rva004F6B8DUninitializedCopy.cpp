// cl: /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$__uninitialized_copy@PBURva004F6966@@PAU1@@_STL@@YAPAURva004F6966@@PBU1@0PAU1@ABU__false_type@0@@Z
// @0x004F6B8D 38B: STLport __uninitialized_copy over the 12-byte ref-holding
// record whose copy ctor 0x004F6966, placement construct 0x004F6B69 and
// __uninitialized_fill_n 0x004F6BB3 are rowed (Rva004F6966CopyCtor.cpp and
// siblings). The banked attempt wrote the loop by hand and came out with esi
// and edi swapped; the vendored template body (exceptions off, as retail has
// no EH here) gives retail's register roles.
//
// Its per-element call goes to _Construct<Rva004F6966, Rva004F6966>, declared
// here as an explicit specialization: retail's construct at 0x004F6B69 is the
// 18-byte null-tested placement copy of the rowed Rva004F6B69Construct, with
// no EH frame, and a body with that statement compiled as this
// specialization is byte-identical there, so the template name is pinned
// at that address.
#include <memory>

struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};

struct Rva004F6966
{
	TargetRef00217D4C *m_00;
	int m_04;
	int m_08;
	Rva004F6966(const Rva004F6966 &other);
};

namespace _STL
{
template <> void _Construct<Rva004F6966, Rva004F6966>(Rva004F6966 *p, const Rva004F6966 &v);
}

template Rva004F6966 *_STL::__uninitialized_copy<const Rva004F6966 *, Rva004F6966 *>(const Rva004F6966 *, const Rva004F6966 *, Rva004F6966 *, const _STL::__false_type &);
