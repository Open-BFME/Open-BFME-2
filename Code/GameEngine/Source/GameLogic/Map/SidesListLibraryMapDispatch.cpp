// cl: /O1 /G7 /arch:SSE /EHsc /MD
// stlport
// Native32FEF5..32FF48 and32FF48..32FF91 are SidesList library-map
// dispatch wrappers, not STL vector resize. WB A864F0/A86590 corroborates the
// LibraryMapCache lifetime and SidesList receiver. Method names unknown.
#include <vector>
struct BfmeE16 { float x,y,z,w; };
class LibraryMapCache : public _STL::_Vector_base<BfmeE16,_STL::allocator<BfmeE16> > {
public:
    LibraryMapCache() : _STL::_Vector_base<BfmeE16,_STL::allocator<BfmeE16> >(_STL::allocator<BfmeE16>()) {}
    ~LibraryMapCache();
};
class SidesList {
public:
    void rva0032FC70(int sideIndex, LibraryMapCache *cache);
    void rva0032FEF5();
    void rva0032FF48(int sideIndex);
private:
    char m_prefix[0x3C];
    int m_count;
};
void SidesList::rva0032FEF5()
{
    LibraryMapCache cache;
    for(int i=0;i<m_count;++i) rva0032FC70(i,&cache);
}
void SidesList::rva0032FF48(int sideIndex)
{
    LibraryMapCache cache;
    rva0032FC70(sideIndex,&cache);
}
