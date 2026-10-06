// cl: /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?insert_unique@?$_Rb_tree@IU?$pair@$$CBIPAX@_STL@@U?$_Select1st@U?$pair@$$CBIPAX@_STL@@@2@U?$less@I@2@V?$allocator@U?$pair@$$CBIPAX@_STL@@@2@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@U?$pair@$$CBIPAX@_STL@@U?$_Nonconst_traits@U?$pair@$$CBIPAX@_STL@@@2@@_STL@@_N@2@ABU?$pair@$$CBIPAX@2@@Z
// retail 0x00534827 134B: _Rb_tree<unsigned pair<const unsigned void*> >::insert_unique(const value_type&)
// without hint. Pinned name. Calls rowed _M_decrement 0x000242C0 and pinned PAX _M_insert 0x0053479F
// (ICF twin of the rowed State spelling). Donor vendor/stlport/stl/_tree.c
// with _BFME_RETAIL_TREE_INSERT_LAYOUT for the leftmost fast path _M_insert(__y __y __v).
// Flags copy the sibling map<unsigned void*> TU stlport_map_int_ptr_lower.cpp plus the retail layout macro.
#include <map>

typedef _STL::_Rb_tree<unsigned, _STL::pair<const unsigned, void *>, _STL::_Select1st<_STL::pair<const unsigned, void *> >, _STL::less<unsigned>, _STL::allocator<_STL::pair<const unsigned, void *> > > MapIntPtrTree;

template _STL::pair<MapIntPtrTree::iterator, bool> MapIntPtrTree::insert_unique(const MapIntPtrTree::value_type &);
