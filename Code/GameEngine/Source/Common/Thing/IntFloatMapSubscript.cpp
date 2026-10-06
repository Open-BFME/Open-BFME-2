// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// Integer-to-float map element access (shared subscript helper). The insert
// folds to the rowed integer-pair spelling (twin pin).
// ?insert_unique@?$_Rb_tree@HU?$pair@$$CBHM@_STL@@U?$_Select1st@U?$pair@$$CBHM@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHM@_STL@@@2@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBHM@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHM@_STL@@@2@@2@U32@ABU?$pair@$$CBHM@2@@Z @ 0x003590C9 (294B): _Rb_tree insert_unique with hint; same 294B shape as int_int 0x00422EC0; callees _M_insert 0x005C6A75 and insert_unique 0x005DFD8D plus _M_increment/_M_decrement.

#include <map>

template float &_STL::map<int, float, _STL::less<int>, _STL::allocator<_STL::pair<const int, float> > >::operator[](const int &);

typedef _STL::pair<const int, float> IntFloatValue;
typedef _STL::_Rb_tree<int, IntFloatValue, _STL::_Select1st<IntFloatValue>, _STL::less<int>, _STL::allocator<IntFloatValue> > IntFloatTree;
template IntFloatTree::iterator IntFloatTree::insert_unique(IntFloatTree::iterator, const IntFloatValue &);
