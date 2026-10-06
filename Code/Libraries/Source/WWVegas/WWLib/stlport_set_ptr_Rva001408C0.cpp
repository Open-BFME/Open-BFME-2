// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?insert@?$set@PAURva001408C0Target@@U?$less@PAURva001408C0Target@@@_STL@@V?$allocator@PAURva001408C0Target@@@3@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@PAURva001408C0Target@@U?$_Const_traits@PAURva001408C0Target@@@_STL@@@_STL@@_N@2@ABQAURva001408C0Target@@@Z, retail 0x00080691, 35 bytes.
// STLport 4.5.3 set<Rva001408C0Target*> insert wrapper: hidden-result copy of
// tree insert_unique at pinned 0x00422047. Called from 12 sites including
// 0x004ABEAE (LargeGroupAudio path). Flags from stlport_vector_s_o1.cpp.
#include <set>
struct Rva001408C0Target { int x; };
typedef _STL::set<Rva001408C0Target*, _STL::less<Rva001408C0Target*>, _STL::allocator<Rva001408C0Target*> > PtrSet001408C0;
#pragma optimize("y", off)
template _STL::pair<PtrSet001408C0::iterator, bool> PtrSet001408C0::insert(Rva001408C0Target* const &);
