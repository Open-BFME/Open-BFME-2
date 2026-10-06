// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?insert@?$map@HURva00439AAAMapped@@U?$less@H@_STL@@V?$allocator@U?$pair@$$CBHURva00439AAAMapped@@@_STL@@@3@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBHURva00439AAAMapped@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHURva00439AAAMapped@@@_STL@@@2@@2@U32@ABU?$pair@$$CBHURva00439AAAMapped@@@2@@Z @0x00439C56 29B map hint-insert forwards to tree insert_unique 0x00439B30.
// Evidence: rowed insert_unique 0x00439B30 in StlportIntMapInsertFamily.cpp; caller 0x00439C73 passes hidden+pos+pair with this=map; same 29B shape as 0x005592FB and 0x0021DB74.
#include <map>

struct Rva00439AAAMapped { int a; };

typedef _STL::map<int, Rva00439AAAMapped, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00439AAAMapped> > > Map00439C56;

template Map00439C56::iterator Map00439C56::insert(Map00439C56::iterator, const Map00439C56::value_type &);
