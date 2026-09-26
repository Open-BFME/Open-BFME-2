// cl: /O1 /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
// String->int tree node eraser: retail 0x00389C9, 53 bytes. Same 53B
// Destroy-and-free shape as the landed color-tree erase 0x380EB1 (recurse
// right, destroy the value at node+0x10, release the node via GameMemory
// free 0x30830, walk left). The value is pair<const narrow string, int>;
// retail destroys it with a direct call to the 14B narrow-string teardown
// at 0x7FAB3 (gen-alias of the rowed string dtor 0x142D70), reached from
// the rowed tree clear 0x389A4C in PeerThread.cpp.
#include <map>
#include <string>

typedef _STL::pair<const _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >, int> StringIntValue;
typedef _STL::_Rb_tree<_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >, StringIntValue, _STL::_Select1st<StringIntValue>, _STL::less<_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > >, _STL::allocator<StringIntValue> > StringIntTree;

// ?_M_erase@?$_Rb_tree@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@U?$pair@$$CBV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@H@2@U?$_Select1st@U?$pair@$$CBV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@H@_STL@@@2@U?$less@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@H@_STL@@@2@@_STL@@AAEXPAU?$_Rb_tree_node@U?$pair@$$CBV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@H@_STL@@@2@@Z
template void StringIntTree::_M_erase(StringIntTree::_Link_type);
