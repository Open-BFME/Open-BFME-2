// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport46
//
// ??$__uninitialized_fill_n@PAVRva0052BE33@@IV1@@_STL@@YAPAVRva0052BE33@@PAV1@IABV1@ABU__false_type@0@@Z @0x00565685 (37B).
// _STL::__uninitialized_fill_n<Rva0052BE33> retail 37 bytes. Dedicated TU
// so Rva0052BE33 _Construct stays out-of-line. Evidence: loop calls rowed
// _Construct 0x0052C392 stride 0x14 caller 0x00565D59 same shape as rowed
// 0x0056561E and FXList fill 0x005655DC.
class Rva0052BE33
{
	char _m[20];

public:
	Rva0052BE33(const Rva0052BE33 &that);
};

#include <memory>

// _Construct stays declared only, so the element copy remains an out-of-line call.
namespace _STL { template <> void _Construct<Rva0052BE33, Rva0052BE33>(Rva0052BE33 *, const Rva0052BE33 &); }

template Rva0052BE33 *_STL::__uninitialized_fill_n(Rva0052BE33 *, unsigned int, const Rva0052BE33 &, const _STL::__false_type &);
