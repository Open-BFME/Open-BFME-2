// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1?$_Rb_tree@HU?$pair@$$CBHPAX@_STL@@U?$_Select1st@U?$pair@$$CBHPAX@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHPAX@_STL@@@2@@_STL@@QAE@XZ, retail 0x00286852, 56 bytes.
// _Rb_tree<int pair<const int void*>> dtor for map<int void*> members via rowed ctor 0x0033C432.
// Callers include SiegeContain dtor 0x0047BF43 and HordeSiegeContain dtor 0x0047CFB2 plus Contain dtors.
// Vendored STLport 4.5.3 explicit dtor instantiation per WaypointTreeCleanup precedent.
#include <map>
typedef _STL::pair<const int, void *> IntPtrPair00286852;
typedef _STL::_Rb_tree<int, IntPtrPair00286852, _STL::_Select1st<IntPtrPair00286852>, _STL::less<int>, _STL::allocator<IntPtrPair00286852> > IntPtrTree00286852;
template IntPtrTree00286852::~_Rb_tree();
