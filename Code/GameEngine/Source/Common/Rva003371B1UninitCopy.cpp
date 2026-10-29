// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport46
//
// ??$__uninitialized_copy@PAVRva003371B1@@PAV1@@_STL@@YAPAVRva003371B1@@PAV1@00ABU__false_type@0@@Z @0x00337340 (38B).
// _STL::__uninitialized_copy<Rva003371B1>, retail 38 bytes. Dedicated TU so
// Rva003371B1Copy.cpp cannot inline _Construct into this loop. Element
// stride is 0x14 via the dummy body below; _Construct is declared only and
// resolves through the rowed 0x00337313.
class Rva003371B1
{
	char _m[0x14];

public:
	Rva003371B1(const Rva003371B1 &that);
};

#include <memory>

// _Construct stays declared only, so the element copy remains an out-of-line call.
namespace _STL { template <> void _Construct<Rva003371B1, Rva003371B1>(Rva003371B1 *, const Rva003371B1 &); }

template Rva003371B1 *_STL::__uninitialized_copy(Rva003371B1 *, Rva003371B1 *, Rva003371B1 *, const _STL::__false_type &);
