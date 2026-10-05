// cl: /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// vector<PrereqUnitRec> copy ctor, retail 0x002CFE45.
//
// This is the +0x00 member copy of ProductionPrerequisite (retail copy ctor
// at 0x002D08DA): the 12-byte PrereqUnitRec element forces the idiv-by-0x0C
// count shape. Unlike the push_back TU, this unit compiles WITHOUT
// _STLP_NO_EXCEPTIONS: retail carries the __EH_prolog frame here, and the
// non-trivial element (user-declared dtor, like the Zero Hour header in
// reference/open-bfme-1) selects the exception-guarded copy path with the
// out-of-line _Vector_base and uninitialized_copy callees.

// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

struct PrereqUnitRec
{
	unsigned int m_data[3];
	~PrereqUnitRec() {}
};

template class _STL::vector<PrereqUnitRec>;
