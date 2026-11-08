// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Retail's 0x002D07F4 is set<BfmeStringRecord002CF550>'s tree operator=: it calls that tree's clear (0x002572AE) and _M_copy (0x002D0326).
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#define _STLP_BFME_TREE_NODE_BASE_O2  // emit retail's _Rb_tree_node_base::_S_minimum/_S_maximum (vendor/stlport/stl/_tree.h)
#include <algorithm>
#include <set>
#include "OwnedRecord900.h"

// clear and _M_copy are retail's rows; declaring them binds the calls there instead of emitting this unit's copies.
namespace _STL {
template <> void BfmeStringRecordTree900::clear();
template <> BfmeStringRecordTree900::_Link_type BfmeStringRecordTree900::_M_copy(BfmeStringRecordTree900::_Link_type, BfmeStringRecordTree900::_Link_type);
}

// Instantiate the recovered operation.
template BfmeStringRecordTree900 &BfmeStringRecordTree900::operator=(const BfmeStringRecordTree900 &);

// The outer set operator= at retail 0x002D0B36 (18 bytes): forwards to the tree member instantiated above and returns this.
template _STL::set<BfmeStringRecord002CF550> &_STL::set<BfmeStringRecord002CF550>::operator=(const _STL::set<BfmeStringRecord002CF550> &);
