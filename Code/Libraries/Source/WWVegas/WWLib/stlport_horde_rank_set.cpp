// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// STLport 4.5.3 integer-set helpers, independently identified from PC Horde
// rank callbacks at 46AD18: set insert BC15D -> tree unique73053 -> insert2EBACB
// -> create-node4ABCC9. Signed int comparison at value+10, 20-byte nodes and
// the single dword copy establish this instantiation; no Xbox layout assumed.
// Allocation adaptation follows the already verified BFME byte-allocator
// pattern in stlport_rb_tree_hint_00242f5e.cpp. No new allocator pin is needed.
#include <set>

// These operations are native inline in all four matched rank-set bodies.
// Keep their unused out-of-line copies from competing with existing providers.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &left, const int &right) const
{ return left < right; }
template <> __declspec(dllimport) __forceinline
const int &_Identity<int>::operator()(const int &value) const
{ return value; }
template <> __declspec(dllimport) __forceinline
void _Construct<int, int>(int *place, const int &value)
{ new (static_cast<void *>(place)) int(value); }
}

typedef _STL::_Rb_tree<int, int, _STL::_Identity<int>, _STL::less<int>, _STL::allocator<int> > RankTree;
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}

// The tree accessors, iterator and pair constructors are native inline too;
// their unreferenced out-of-line copies lose to or override other providers.
namespace _STL {
typedef _Rb_tree_node<int> *RankLink;
template <> __declspec(dllimport) __forceinline
_Rb_tree_iterator<int, _Nonconst_traits<int> >::_Rb_tree_iterator(RankLink node) { _M_node = node; }
template <> __declspec(dllimport) __forceinline
_Rb_tree_iterator<int, _Nonconst_traits<int> >::_Rb_tree_iterator(
    const _Rb_tree_iterator<int, _Nonconst_traits<int> > &it) { _M_node = it._M_node; }
template <> __declspec(dllimport) __forceinline RankLink &_STLP_CALL
_Rb_tree<int, int, _Identity<int>, less<int>, allocator<int> >::_S_left(RankLink node)
{ return (RankLink &)(node->_M_left); }
template <> __declspec(dllimport) __forceinline RankLink &_STLP_CALL
_Rb_tree<int, int, _Identity<int>, less<int>, allocator<int> >::_S_right(RankLink node)
{ return (RankLink &)(node->_M_right); }
template <> __declspec(dllimport) __forceinline RankLink &_STLP_CALL
_Rb_tree<int, int, _Identity<int>, less<int>, allocator<int> >::_S_parent(RankLink node)
{ return (RankLink &)(node->_M_parent); }
template <> __declspec(dllimport) __forceinline int &_STLP_CALL
_Rb_tree<int, int, _Identity<int>, less<int>, allocator<int> >::_S_value(RankLink node)
{ return node->_M_value_field; }
template <> __declspec(dllimport) __forceinline const int &_STLP_CALL
_Rb_tree<int, int, _Identity<int>, less<int>, allocator<int> >::_S_key(RankLink node)
{ return _Identity<int>()(_S_value(node)); }
template <> __declspec(dllimport) __forceinline const int &_STLP_CALL
_Rb_tree<int, int, _Identity<int>, less<int>, allocator<int> >::_S_key(_Rb_tree_node_base *node)
{ return _Identity<int>()(_S_value(RankLink(node))); }
template <> __declspec(dllimport) __forceinline _Rb_tree_iterator<int, _Nonconst_traits<int> >
_Rb_tree<int, int, _Identity<int>, less<int>, allocator<int> >::begin() { return iterator(_M_leftmost()); }
template <> __declspec(dllimport) __forceinline
pair<_Rb_tree_iterator<int, _Nonconst_traits<int> >, bool>::pair(
    const _Rb_tree_iterator<int, _Nonconst_traits<int> > &a, const bool &b) : first(a), second(b) {}
template <> __declspec(dllimport) __forceinline
pair<_Rb_tree_iterator<int, _Const_traits<int> >, bool>::pair(
    const _Rb_tree_iterator<int, _Const_traits<int> > &a, const bool &b) : first(a), second(b) {}
}

template <> RankTree::_Link_type RankTree::_M_create_node(const int &value)
{
    _Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<int>), 0);
    _STL::_Construct(&node->_M_value_field, value);
    return node;
}

// The integer-set copy shares these node operations with rank insertion.
// ?RankTree::_M_clone_node present-unmatched
template <> __declspec(noinline) inline
RankTree::_Link_type RankTree::_M_clone_node(_Link_type x)
{
    _Link_type node = _M_create_node(x->_M_value_field);
    node->_M_color = x->_M_color;
    node->_M_left = 0;
    node->_M_right = 0;
    return node;
}

template _STL::pair<RankTree::iterator, bool> RankTree::insert_unique(const int &);
typedef _STL::set<int> RankSet;
template _STL::pair<RankSet::iterator, bool> RankSet::insert(const int &);

template RankTree::_Link_type RankTree::_M_copy(_Link_type, _Link_type);
