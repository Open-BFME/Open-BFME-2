// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source /Ireference/shims/moduledata /Ireference/shims/bfmealloc
// stlport
// ??$__uninitialized_copy@PAVRva002E0A0A@@PAV1@@_STL@@YAPAVRva002E0A0A@@PAV1@00ABU__false_type@0@@Z 0x0052C203 38B evidence: copy stride 0x28 via rowed _Construct 0x0052C1D6; callers 0x0052D157 0x0052D1A2; siblings Rva003A6F70UninitCopy Rva004E18A2UninitCopy
// ??$__uninitialized_copy@PAVRva002E0A0A@@PAV1@@_STL@@YAPAVRva002E0A0A@@PAV1@00ABU__false_type@0@@Z 0x0052C203 38B evidence: copy stride 0x28 via rowed _Construct 0x0052C1D6; callers 0x0052D157 0x0052D1A2; siblings Rva003A6F70UninitCopy Rva004E18A2UninitCopy same flags
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
template Rva002E0A0A *_STL::__uninitialized_copy(Rva002E0A0A *, Rva002E0A0A *, Rva002E0A0A *, const _STL::__false_type &);
