// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
// ??4?$_Rb_tree@UBfmeStringRecord0021A940@@U1@U?$_Identity@UBfmeStringRecord0021A940@@@_STL@@U?$less@UBfmeStringRecord0021A940@@@3@V?$allocator@UBfmeStringRecord0021A940@@@3@@_STL@@QAEAAV01@ABV01@@Z @0x0021D842 115B operator= via rowed clear 0x0021CFD1 and copy 0x0021D7CF.
// Evidence: chain lane every callee rowed; same 115B shape as 0x001DDC52.
#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#include <map>
#include "../../../../GameEngine/Include/Common/BfmeStringRecord0021A940.h"
bool operator<(const BfmeStringRecord0021A940 &a, const BfmeStringRecord0021A940 &b);
typedef _STL::_Rb_tree<BfmeStringRecord0021A940, BfmeStringRecord0021A940, _STL::_Identity<BfmeStringRecord0021A940>, _STL::less<BfmeStringRecord0021A940>, _STL::allocator<BfmeStringRecord0021A940> > BfmeStringRecord0021A940SetTree;
namespace _STL {
template <> void _Destroy<BfmeStringRecord0021A940>(BfmeStringRecord0021A940 *);
template <> void _Construct<BfmeStringRecord0021A940, BfmeStringRecord0021A940>(BfmeStringRecord0021A940 *, const BfmeStringRecord0021A940 &);
template <> void BfmeStringRecord0021A940SetTree::_M_erase(_Rb_tree_node<BfmeStringRecord0021A940> *);
}
template BfmeStringRecord0021A940SetTree &BfmeStringRecord0021A940SetTree::operator=(const BfmeStringRecord0021A940SetTree &);

// The outer set operator= at retail 0x0021DA96 (18 bytes): forwards to the tree
// member instantiated above and returns this.
#include <set>
template _STL::set<BfmeStringRecord0021A940, _STL::less<BfmeStringRecord0021A940 >, _STL::allocator<BfmeStringRecord0021A940 > > &_STL::set<BfmeStringRecord0021A940, _STL::less<BfmeStringRecord0021A940 >, _STL::allocator<BfmeStringRecord0021A940 > >::operator=(const _STL::set<BfmeStringRecord0021A940, _STL::less<BfmeStringRecord0021A940 >, _STL::allocator<BfmeStringRecord0021A940 > > &);
