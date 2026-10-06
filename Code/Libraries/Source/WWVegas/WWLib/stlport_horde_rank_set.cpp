// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// STLport 4.5.3 integer-set helpers, independently identified from PC Horde
// rank callbacks at 46AD18: set insert BC15D -> tree unique73053 -> insert2EBACB
// -> create-node4ABCC9. Signed int comparison at value+10, 20-byte nodes and
// the single dword copy establish this instantiation; no Xbox layout assumed.
// Allocation adaptation follows the already verified BFME byte-allocator
// pattern in stlport_rb_tree_hint_00242f5e.cpp. No new allocator pin is needed.
#include <set>

typedef _STL::_Rb_tree<int, int, _STL::_Identity<int>, _STL::less<int>, _STL::allocator<int> > RankTree;
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}

template <> RankTree::_Link_type RankTree::_M_create_node(const int &value)
{
    _Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<int>), 0);
    _STL::_Construct(&node->_M_value_field, value);
    return node;
}

#pragma optimize("y", off)
template _STL::pair<RankTree::iterator, bool> RankTree::insert_unique(const int &);
typedef _STL::set<int> RankSet;
template _STL::pair<RankSet::iterator, bool> RankSet::insert(const int &);
