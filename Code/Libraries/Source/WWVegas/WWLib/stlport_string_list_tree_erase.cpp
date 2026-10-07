// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// List-pair tree single-node erase (retail 0x005CA221 59B): rebalance via
// rowed 0x00025620, destroy the pair at +0x10 via rowed 0x005C9ED3, release
// via _free 0x00030830, decrement count. Same models as
// stlport_string_list_pair_cleanup.cpp; caller 0x005CA7A9.
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <list>

#include "ascii_string.h"


bool operator<(const AsciiString &left, const AsciiString &right);

typedef _STL::list<AsciiString> AsciiStringList;
typedef _STL::pair<const AsciiString, AsciiStringList> ListPair;
typedef _STL::_Rb_tree<AsciiString, ListPair, _STL::_Select1st<ListPair>, _STL::less<AsciiString>, _STL::allocator<ListPair> > ListPairTree;

template void ListPairTree::erase(ListPairTree::iterator);
template void ListPairTree::erase(ListPairTree::iterator, ListPairTree::iterator);
