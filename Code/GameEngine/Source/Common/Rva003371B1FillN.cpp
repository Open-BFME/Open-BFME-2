// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport46
//
// ??$__uninitialized_fill_n@PAVRva003371B1@@IV1@@_STL@@YAPAVRva003371B1@@PAV1@IABV1@ABU__false_type@0@@Z @0x00337366 (37B).
// _STL::__uninitialized_fill_n<Rva003371B1>, retail 37 bytes. Dedicated TU
// so Rva003371B1Copy.cpp cannot inline _Construct into this loop.
// Element stride is 0x14 via the dummy body below; _Construct is declared
// only and resolves through the rowed 0x00337313.
class Rva003371B1
{
	char _m[0x14];

public:
	Rva003371B1(const Rva003371B1 &that);
};

#include <memory>

// _Construct stays declared only, so the element copy remains an out-of-line call.
namespace _STL { template <> void _Construct<Rva003371B1, Rva003371B1>(Rva003371B1 *, const Rva003371B1 &); }

template Rva003371B1 *_STL::__uninitialized_fill_n(Rva003371B1 *, unsigned int, const Rva003371B1 &, const _STL::__false_type &);
