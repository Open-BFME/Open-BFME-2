// cl: /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??$__uninitialized_copy@PAVRva001ED03C@@PAV1@@_STL@@YAPAVRva001ED03C@@PAV1@00ABU__false_type@0@@Z @0x001ED21E 38B.
// _STL::__uninitialized_copy<Rva001ED03C> retail 38 bytes. Dedicated TU
// so Rva001ED03C _Construct stays out-of-line. Evidence: chain via rowed
// _Construct 0x001ED1F1 stride 0x24 callers 0x001ED4B7 0x001ED502 same shape
// as Rva002E0A0A copy 0x0052C203 and Rva003F1EA8 copy 0x003F1EA8.
// The real STLport template supplies the loop; the declaration-only
// _Construct specialization keeps each element copy a call to the row.
#include <vector>
class Rva001ED03C { public: unsigned char data[0x24]; };
namespace _STL { template <> void _Construct<Rva001ED03C, Rva001ED03C>(Rva001ED03C *, const Rva001ED03C &); }

template Rva001ED03C *_STL::__uninitialized_copy(Rva001ED03C *, Rva001ED03C *, Rva001ED03C *, const _STL::__false_type &);
