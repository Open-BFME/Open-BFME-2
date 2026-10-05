// ?_M_fill_insert@?$vector@V?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@V?$allocator@V?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@@2@@_STL@@QAEXPAV?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@2@IABV32@@Z
// partial score=0.94 date=2026-10-05
// cl: /O1 /G7 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?_M_fill_insert@?$vector@V?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@V?$allocator@V?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@@2@@_STL@@QAEXPAV?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@2@IABV32@@Z @0x0033A05E 265B vector<vector<ScienceType>>::_M_fill_insert(pos,n,x) via stock STLport 4.5.3; stride 12 with ScienceType copy ctor 0x54878E; evidence leaf packet with sciencevec helpers
#include <vector>
enum ScienceType { SCIENCE_NONE = 0 };
typedef _STL::vector<ScienceType, _STL::allocator<ScienceType> > SciVec;
typedef _STL::vector<SciVec, _STL::allocator<SciVec> > SciVecVec;
template void SciVecVec::insert(SciVecVec::iterator, SciVecVec::size_type, const SciVecVec::value_type &);
