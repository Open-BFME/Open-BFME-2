// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0?$map@HUBfmePod24@@U?$less@H@_STL@@V?$allocator@U?$pair@$$CBHUBfmePod24@@@_STL@@@3@@_STL@@QAE@XZ @0x005011C1 25B
// STLport map<int, T>::map(): build the comparator and allocator temporaries
// and call the _Rb_tree constructor, here the one rowed at 0x004FF681 under
// the map<int, BfmePod24> spelling (stlport_rb_tree_create_nodes.cpp), which
// names this map. The body is shared: the constructors of Rva003C2F40Owner,
// BfmeRectVNI, Rva00417F7C, Rva004E32F2 and Rva004E3CD0 all call it, so the
// other int-keyed maps whose tree constructor folded into 0x004FF681 share this
// address too. Masked twin of the rowed set<AsciiString> default constructor
// (stlport_asciistring_set_base.cpp, whose flags these are).
#include <map>

struct BfmePod24 { int a[6]; };

template _STL::map<int, BfmePod24, _STL::less<int>, _STL::allocator<_STL::pair<const int, BfmePod24> > >::map();
