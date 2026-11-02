// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native32FEF5..32FF48 and32FF48..32FF91 are SidesList library-map
// dispatch wrappers, not STL vector resize. WB A864F0/A86590 corroborates the
// LibraryMapCache lifetime and SidesList receiver. Method names unknown.
#include <vector>
#include "../../../../Libraries/Include/Lib/BfmeE16.h"
class LibraryMapCache : public _STL::_Vector_base<BfmeE16,_STL::allocator<BfmeE16> > {
public:
    LibraryMapCache() : _STL::_Vector_base<BfmeE16,_STL::allocator<BfmeE16> >(_STL::allocator<BfmeE16>()) {}
    ~LibraryMapCache();
};
#include "../../../Include/Common/SidesList.h"
void SidesList::rva0032FEF5()
{
    LibraryMapCache cache;
    for(int i=0;i<m_numSides;++i) rva0032FC70(i,&cache);
}
void SidesList::rva0032FF48(int sideIndex)
{
    LibraryMapCache cache;
    rva0032FC70(sideIndex,&cache);
}
