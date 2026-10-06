// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?insert@?$list@FV?$allocator@F@_STL@@@_STL@@QAE?AU?$_List_iterator@FU?$_Nonconst_traits@F@_STL@@@2@U32@ABF@Z @0x002ABB61 (37B)
// Evidence: identical 37B shape to list<int>::insert at 0x005925E2 calling rowed _M_create_node;
// here calls rowed short _M_create_node at 0x002AAC55 then list hook insertion; caller 0x002AC01D.
#include <list>
template class _STL::list<short, _STL::allocator<short> >;
