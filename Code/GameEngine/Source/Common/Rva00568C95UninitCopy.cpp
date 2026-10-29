// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport46
//
// ??$__uninitialized_copy@PBVRva00568A20@@PAV1@@_STL@@YAPAVRva00568A20@@PBV1@0PAV1@ABU__false_type@0@@Z @0x00568C95 (38B).
// _STL::__uninitialized_copy<Rva00568A20>, retail 38 bytes. Dedicated TU so
// Rva00568A20 _Construct stays out-of-line. Element stride is 0xC via the
// dummy body below; _Construct is declared only and resolves through the
// rowed 0x00568C83. Same 38B shape as throw-spec sibling 0x0004CC82 and
// callers at 0x00568D86 0x0056A225 0x0056A270 prove copy role.
class Rva00568A20
{
	char _m[12];

public:
	Rva00568A20(const Rva00568A20 &that);
};

#include <memory>

// _Construct stays declared only, so the element copy remains an out-of-line call.
namespace _STL { template <> void _Construct<Rva00568A20, Rva00568A20>(Rva00568A20 *, const Rva00568A20 &); }

template Rva00568A20 *_STL::__uninitialized_copy(const Rva00568A20 *, const Rva00568A20 *, Rva00568A20 *, const _STL::__false_type &);
