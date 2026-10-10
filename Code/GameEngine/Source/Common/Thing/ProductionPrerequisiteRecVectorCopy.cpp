// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
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

struct PrereqUnitRec
{
	unsigned int m_data[3];
	~PrereqUnitRec() {}
};

template class _STL::vector<PrereqUnitRec>;
