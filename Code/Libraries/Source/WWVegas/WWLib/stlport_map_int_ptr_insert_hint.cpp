// cl: /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
//
// ?insert@?$map@IPAXU?$less@I@_STL@@V?$allocator@U?$pair@$$CBIPAX@_STL@@@2@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBIPAX@_STL@@U?$_Nonconst_traits@U?$pair@$$CBIPAX@_STL@@@2@@2@U32@ABU?$pair@$$CBIPAX@2@@Z
// retail 0x00534A0D 29B: map<unsigned void*>::insert(iterator position const value_type&)
// hint-forwarding wrapper over the rowed _Rb_tree hint insert_unique at 0x005348E7.
// Called once by the unclaimed operator[]-style worker at 0x00534A2A via 0x00534A7B.
// Flags copy the sibling map<unsigned void*> TU stlport_map_int_ptr_lower.cpp.
#include <map>

typedef _STL::map<unsigned, void *, _STL::less<unsigned>, _STL::allocator<_STL::pair<const unsigned, void *> > > MapIntPtr;

template MapIntPtr::iterator MapIntPtr::insert(MapIntPtr::iterator, const MapIntPtr::value_type &);
