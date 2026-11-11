// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// The key is retail's 32-bit unsigned int (tools/retail_identity.py MAP_UINT_INT_COPY).
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#define _STLP_BFME_TREE_NODE_BASE_O2  // emit retail's _Rb_tree_node_base::_S_minimum/_S_maximum (vendor/stlport/stl/_tree.h)
#include <algorithm>
#include <map>

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

// map<unsigned int,int>: subscript 0x00534A2A compares the key unsigned (cmp eax,[esi+0x10]; jae) and
// _Construct 0x0060C9D9 copies it as a dword. Only the map copy constructor (0x0053462F) is instantiated; it
// brings the tree copy (0x00534581). The whole class would emit an insert_unique that differs from
// PathDoXfer.cpp's matched row 0x004D795B.
typedef _STL::map<unsigned int, int> Map00534581;
template Map00534581::map(const Map00534581 &);
