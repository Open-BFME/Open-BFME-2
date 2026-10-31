// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??$__uninitialized_fill_n@PAVRva001ED03C@@IV1@@_STL@@YAPAVRva001ED03C@@PAV1@IABV1@ABU__false_type@0@@Z @0x001ED244 (37B).
// _STL::__uninitialized_fill_n<Rva001ED03C> retail 37 bytes. Dedicated TU
// so Rva001ED03C _Construct stays out-of-line. Evidence: chain via rowed
// _Construct 0x001ED1F1 stride 0x24 caller 0x001ED4E4 same shape as rowed
// Coord3D fill 0x002CA849 and Rva0052BEF0 fill 0x00565770.
// The real STLport template supplies the loop; the declaration-only
// _Construct specialization keeps each element copy a call to the row.
#include <vector>
class Rva001ED03C { public: unsigned char data[0x24]; };
namespace _STL { template <> void _Construct<Rva001ED03C, Rva001ED03C>(Rva001ED03C *, const Rva001ED03C &); }

template Rva001ED03C *_STL::__uninitialized_fill_n(Rva001ED03C *, unsigned int, const Rva001ED03C &, const _STL::__false_type &);
