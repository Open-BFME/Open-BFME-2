// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport46
//
// ??$__uninitialized_fill_n@PAVRva00568A20@@IV1@@_STL@@YAPAVRva00568A20@@PAV1@IABV1@ABU__false_type@0@@Z @0x00568CBB (37B).
// _STL::__uninitialized_fill_n<Rva00568A20> retail 37 bytes. Dedicated TU
// so Rva00568A20 _Construct stays out-of-line. Evidence: loop calls rowed
// _Construct 0x00568C83 stride 0xC caller 0x0056A252 same 37B shape as rowed
// fill_n 0x00565685 and siblings at 0x000BBB83.
class Rva00568A20
{
	char _m[12];

public:
	Rva00568A20(const Rva00568A20 &that);
};

#include <memory>

// _Construct stays declared only, so the element copy remains an out-of-line call.
namespace _STL { template <> void _Construct<Rva00568A20, Rva00568A20>(Rva00568A20 *, const Rva00568A20 &); }

template Rva00568A20 *_STL::__uninitialized_fill_n(Rva00568A20 *, unsigned int, const Rva00568A20 &, const _STL::__false_type &);
