// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?_M_clone_node clone for BfmeRecord001DD3BC set tree @0x001DD998 30B via rowed create_node 0x001DD976.
// Evidence: unlock lane same 30B shape as 0x002CFE27; value at source+0x10 color copy null links.
#include <map>
struct BfmeRecord001DD3BC {
	unsigned char m_data[8];
};
bool operator<(const BfmeRecord001DD3BC &a, const BfmeRecord001DD3BC &b);
typedef _STL::_Rb_tree<BfmeRecord001DD3BC, BfmeRecord001DD3BC, _STL::_Identity<BfmeRecord001DD3BC>, _STL::less<BfmeRecord001DD3BC>, _STL::allocator<BfmeRecord001DD3BC> > BfmeRecord001DD3BCSetTree;
namespace _STL {
template <> void _Construct<BfmeRecord001DD3BC>(BfmeRecord001DD3BC *, const BfmeRecord001DD3BC &);
}
template BfmeRecord001DD3BCSetTree::_Link_type BfmeRecord001DD3BCSetTree::_M_clone_node(BfmeRecord001DD3BCSetTree::_Link_type);
template BfmeRecord001DD3BCSetTree::_Link_type BfmeRecord001DD3BCSetTree::_M_copy(BfmeRecord001DD3BCSetTree::_Link_type, BfmeRecord001DD3BCSetTree::_Link_type);
