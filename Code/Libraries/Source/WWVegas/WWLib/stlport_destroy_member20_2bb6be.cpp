// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??$_Destroy@PAURva002BB6BE20Rec@@@_STL@@YAXPAURva002BB6BE20Rec@@0@Z @0x002BB6BE 25B:
// STLport range destroy stepping 0x14 over a 20-byte record with a vector at +8.
// Calls the declared-only dtor pinned to rowed Member44 0x002B6B4C (same vector-destroy body).
// Unlocks 0x002BBB57 and 0x002BBBC9. Precedent stlport_vector_rva0007bb16_destroy.cpp.
#include <vector>
struct BfmeE16 { float x, y, z, w; };
struct Rva002BB6BE20Rec {
  int m_00;
  int m_04;
  _STL::vector<BfmeE16> m_08;
  ~Rva002BB6BE20Rec();
};
namespace _STL {
template <>
__declspec(noinline) void _Destroy<Rva002BB6BE20Rec *>(Rva002BB6BE20Rec *__first, Rva002BB6BE20Rec *__last)
{
  for (; __first != __last; ++__first)
    _Destroy(&*__first);
}
template <>
__declspec(noinline) void _Destroy<vector<Rva002BB6BE20Rec> *>(vector<Rva002BB6BE20Rec> *__first, vector<Rva002BB6BE20Rec> *__last)
{
  for (; __first != __last; ++__first)
    _Destroy(&*__first);
}
}
template void _STL::vector<Rva002BB6BE20Rec>::_M_clear();
template _STL::vector<Rva002BB6BE20Rec>::~vector();
template _STL::vector<_STL::vector<Rva002BB6BE20Rec> >::~vector();
