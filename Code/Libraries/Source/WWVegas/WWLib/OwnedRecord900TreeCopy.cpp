// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 tree copy and cleanup for the target record at 0x2CF550.
#define _STLP_BFME_TREE_NODE_BASE_O2  // emit retail's _Rb_tree_node_base::_S_minimum/_S_maximum (vendor/stlport/stl/_tree.h)
#include "OwnedRecord900.h"
template BfmeStringRecordTree900::_Link_type
BfmeStringRecordTree900::_M_clone_node(BfmeStringRecordTree900::_Link_type);
template BfmeStringRecordTree900::_Link_type
BfmeStringRecordTree900::_M_copy(BfmeStringRecordTree900::_Link_type, BfmeStringRecordTree900::_Link_type);
template BfmeStringRecordTree900::_Rb_tree(const BfmeStringRecordTree900 &);
// P29 test-branch diagnostic: the set's operator= (retail 0x002D07F4), called by ThingTemplate::operator=.
template BfmeStringRecordTree900 &BfmeStringRecordTree900::operator=(const BfmeStringRecordTree900 &);
#include <set>
template _STL::set<BfmeStringRecord002CF550> &_STL::set<BfmeStringRecord002CF550>::operator=(const _STL::set<BfmeStringRecord002CF550> &);
