// cl: /O1 /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
//
// ?erase@?$_Rb_tree@UTreeKey00242F5E@@U1@U?$_Identity@UTreeKey00242F5E@@@_STL@@U?$less@UTreeKey00242F5E@@@3@V?$allocator@UTreeKey00242F5E@@@3@@_STL@@QAEXU?$_Rb_tree_iterator@UTreeKey00242F5E@@U?$_Nonconst_traits@UTreeKey00242F5E@@@_STL@@@2@0@Z, retail 0x000a79f7, 68 bytes. Banked partial (score 0.95) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// stlport
// _Rb_tree erase(first,last) for the TreeKey00242F5E set (unsigned id at +0
// plus AsciiString at +4): if first==begin and last==end clear via 0x000A79CE,
// else loop increment via 0x00024250 and single erase via 0x00383380 (ICF twin
// of the TreeKey erase-one). Evidence: chain lane all callees rowed; 68B exact
// via whole-class shape (0 memory/register diffs); neighbours 0x000A79CE and
// 0x000A7AA7 share the same cl flags; caller at 0x000A7E6D; same 68B shape as
// 0x002E452F 0x004ABC85 0x005CA7A9.
#include <set>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
struct TreeKey00242F5E
{
	~TreeKey00242F5E();
	unsigned int m_id;
	void *m_name;
	bool operator<(const TreeKey00242F5E &o) const { return m_id < o.m_id; }
};
typedef _STL::_Rb_tree<TreeKey00242F5E, TreeKey00242F5E, _STL::_Identity<TreeKey00242F5E>, _STL::less<TreeKey00242F5E>, _STL::allocator<TreeKey00242F5E> > TreeKey00242F5ESetTree;
template void TreeKey00242F5ESetTree::clear();
template void TreeKey00242F5ESetTree::erase(TreeKey00242F5ESetTree::iterator);
template void TreeKey00242F5ESetTree::erase(TreeKey00242F5ESetTree::iterator, TreeKey00242F5ESetTree::iterator);
