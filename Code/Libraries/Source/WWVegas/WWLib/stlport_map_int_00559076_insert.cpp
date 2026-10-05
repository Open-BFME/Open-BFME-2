// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?insert@?$map@HURva00559076Mapped@@U?$less@H@_STL@@V?$allocator@U?$pair@$$CBHURva00559076Mapped@@@_STL@@@3@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBHURva00559076Mapped@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHURva00559076Mapped@@@_STL@@@2@@2@U32@ABU?$pair@$$CBHURva00559076Mapped@@@2@@Z @0x005592FB 29B map hint-insert forwards to tree insert_unique 0x0055913B.
// Evidence: callee rowed in StlportIntMapInsertFamily.cpp; caller 0x00559376 in 150B unclaimed user; prev BFMENetwork queues cl /O1 /DNDEBUG /MD /GX.
#include <map>

struct Rva00559076Mapped { int a; };

typedef _STL::map<int, Rva00559076Mapped, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00559076Mapped> > > Map005592FB;

template Map005592FB::iterator Map005592FB::insert(Map005592FB::iterator, const Map005592FB::value_type &);
