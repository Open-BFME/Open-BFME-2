// cl: /DNDEBUG /MD /EHsc
// ?rva001364F7@Rva001364F7@@QAE?AURva001364F7Iter@@PAURvaNode1364F7@@0PBUTreeKey00242F5E@@0@Z @0x001364F7 136B.
// Tree insert worker over set<TreeKey00242F5E> nodes (base 0x10 plus 8-byte
// key at +0x10): picks the right-child path unless y is the root, the
// sibling is empty with no hint, or the unsigned key id compares below;
// creates the node through rowed 0x001364AC, links it, rebalances through
// rowed _Rebalance 0x00025490, bumps the count at +4 and returns the node
// through the out reference. Evidence: caller 0x0013657F (hinted insert,
// unsigned id compare with setb plus _M_decrement) passes out/A/B/value/0;
// this then unblocks 0x0013657F and 0x00136642. Pattern follows manual worker
// Rva00418C33Insert.cpp (create call through the rowed factory name,
// _Rb_global<bool>::_Rebalance with the parent-slot cast).
struct TreeKey00242F5E { unsigned m_id; char _pad[4]; };
struct RvaNode1364F7 {
	int _c0;
	RvaNode1364F7 *_parent;
	RvaNode1364F7 *_left;
	RvaNode1364F7 *_right;
	TreeKey00242F5E _key;
};
struct RvaOut13657F {
	RvaNode1364F7 *node;
	bool inserted;
};
struct Rva001364F7Iter {
	RvaNode1364F7 *m_node;
	Rva001364F7Iter(RvaNode1364F7 *node) : m_node(node) {}
};
class Rva001364AC { public: void *rva001364AC(const TreeKey00242F5E *src); };
namespace _STL {
struct _Rb_tree_node_base {};
template <typename D> class _Rb_global {
public:
	static void _Rebalance(_Rb_tree_node_base *x, _Rb_tree_node_base *&root);
};
}
struct Rva001364F7 {
	RvaNode1364F7 *m_root;
	unsigned m_count;
	Rva001364F7Iter rva001364F7(RvaNode1364F7 *a, RvaNode1364F7 *b, const TreeKey00242F5E *v, RvaNode1364F7 *c);
	RvaOut13657F *rva0013657F(RvaOut13657F *out, const TreeKey00242F5E *v);
	Rva001364F7Iter rva00136642(Rva001364F7Iter position, const TreeKey00242F5E &value);
};

Rva001364F7Iter Rva001364F7::rva001364F7(RvaNode1364F7 *a, RvaNode1364F7 *b, const TreeKey00242F5E *v, RvaNode1364F7 *c)
{
	RvaNode1364F7 *node;
	if (b != m_root && (c != 0 || (a == 0 && v->m_id >= b->_key.m_id))) {
		node = (RvaNode1364F7 *)((Rva001364AC *)this)->rva001364AC(v);
		b->_right = node;
		RvaNode1364F7 *root = m_root;
		if (b == root->_right)
			root->_right = node;
	} else {
		node = (RvaNode1364F7 *)((Rva001364AC *)this)->rva001364AC(v);
		b->_left = node;
		RvaNode1364F7 *root = m_root;
		if (b == root) {
			root->_parent = node;
			m_root->_right = node;
		} else if (b == root->_left) {
			root->_left = node;
		}
	}
	node->_left = 0;
	node->_right = 0;
	node->_parent = b;
	_STL::_Rb_global<bool>::_Rebalance((_STL::_Rb_tree_node_base *)node, (_STL::_Rb_tree_node_base *&)m_root->_parent);
	++m_count;
	return Rva001364F7Iter(node);
}
