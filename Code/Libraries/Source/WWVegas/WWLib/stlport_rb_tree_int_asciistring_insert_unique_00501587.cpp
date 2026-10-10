// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?insert_unique_00501587@?$_Rb_tree@HU?$pair@$$CBHVAsciiString@@@_STL@@U?$_Select1st@U?$pair@$$CBHVAsciiString@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHVAsciiString@@@_STL@@@2@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@U?$pair@$$CBHVAsciiString@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHVAsciiString@@@_STL@@@2@@_STL@@_N@2@ABU?$pair@$$CBHVAsciiString@@@2@@Z @0x00501587 134B
// _Rb_tree<int pair<const int AsciiString>>::insert_unique 134B worker calling rowed _M_insert_005014FF 0x005014FF and rowed _M_decrement 0x000242C0
// Evidence: chain from just-landed 0x005014FF; int key compare at node+0x10; shape matches sibling 134B insert_unique 0x00501FEA; unblocks 0x00501BD8 hint worker
// Honest-address suffix because plain insert_unique for this tree is already rowed at 0x00383CA7 with a different _M_insert callee
#define _M_insert _M_insert_005014FF
#define insert_unique insert_unique_00501587
#include <map>
#include "ascii_string.h"

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

typedef _STL::pair<const int, AsciiString> IntAsciiValue;
typedef _STL::_Rb_tree_node<IntAsciiValue> IntAsciiNode;
typedef _STL::_Rb_tree<int, IntAsciiValue, _STL::_Select1st<IntAsciiValue>, _STL::less<int>, _STL::allocator<IntAsciiValue> > MapIntAsciiTree;

template _STL::pair<MapIntAsciiTree::iterator, bool> MapIntAsciiTree::insert_unique(const MapIntAsciiTree::value_type &);
#undef insert_unique
#undef _M_insert
