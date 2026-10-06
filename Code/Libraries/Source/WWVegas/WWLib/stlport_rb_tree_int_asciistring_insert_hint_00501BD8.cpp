// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?insert_unique_00501587@?$_Rb_tree@HU?$pair@$$CBHVAsciiString@@@_STL@@U?$_Select1st@U?$pair@$$CBHVAsciiString@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHVAsciiString@@@_STL@@@2@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBHVAsciiString@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHVAsciiString@@@_STL@@@2@@2@U32@ABU?$pair@$$CBHVAsciiString@@@2@@Z @0x00501BD8 294B
// _Rb_tree<int pair<const int AsciiString>>::insert_unique hint overload 294B worker calling rowed _M_insert_005014FF 0x005014FF and rowed non-hint insert_unique_00501587 0x00501587 plus rowed _M_increment 0x00024250 and _M_decrement 0x000242C0
// Evidence: chain from just-landed 0x00501587; single shared 4-arg _M_insert call site and single insert_unique fallback site in retail; shape matches sibling hint 0x002567FA 294B; callers 0x00501E33 and 0x0050223F
// The hint overload shares the renamed base insert_unique_00501587 (its full mangling is overload-distinct from the 134B non-hint row); the base names the family callee the body falls back to
#define _M_insert _M_insert_005014FF
#define insert_unique insert_unique_00501587
#include <map>
#include "ascii_string.h"

typedef _STL::pair<const int, AsciiString> IntAsciiValue;
typedef _STL::_Rb_tree_node<IntAsciiValue> IntAsciiNode;
typedef _STL::_Rb_tree<int, IntAsciiValue, _STL::_Select1st<IntAsciiValue>, _STL::less<int>, _STL::allocator<IntAsciiValue> > MapIntAsciiTree;

template MapIntAsciiTree::iterator MapIntAsciiTree::insert_unique(MapIntAsciiTree::iterator, const MapIntAsciiTree::value_type &);
#undef insert_unique
#undef _M_insert
