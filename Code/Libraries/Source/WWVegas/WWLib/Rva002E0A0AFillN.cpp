// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source /Ireference/shims/moduledata /Ireference/shims/bfmealloc
// stlport
//
// ??$__uninitialized_fill_n@PAVRva002E0A0A@@IV1@@_STL@@YAPAVRva002E0A0A@@PAV1@IABV1@ABU__false_type@0@@Z @0x0052C229 (37B).
// _STL::__uninitialized_fill_n<Rva002E0A0A>, retail 37 bytes. Element
// stride is 0x28; the loop calls _Construct out of line, the rowed
// 0x0052C1D6. Caller 0x0052D184. Sibling Rva00564C58FillN same recipe.
// _STL::__uninitialized_fill_n<Rva002E0A0A>, retail 37 bytes. Dedicated TU
// so no local _Construct definition can inline into this loop. Element
// stride is 0x28 via the dummy body below; _Construct is declared only
// and resolves through the rowed 0x0052C1D6. Caller 0x0052D184.
// Sibling Rva00564C58FillN same recipe same flags.
#include <vector>
class Rva002E0A0A {
    char opaque[36];
public:
    Rva002E0A0A(const Rva002E0A0A &);
    Rva002E0A0A &operator=(const Rva002E0A0A &);
    virtual ~Rva002E0A0A();
};
namespace _STL {
template <> void _Construct<Rva002E0A0A, Rva002E0A0A>(
    Rva002E0A0A *, const Rva002E0A0A &);
}
template Rva002E0A0A *_STL::__uninitialized_fill_n(Rva002E0A0A *, unsigned int, const Rva002E0A0A &, const _STL::__false_type &);
