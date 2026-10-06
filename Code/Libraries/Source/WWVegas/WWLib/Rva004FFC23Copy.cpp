// cl: /MD
// ?rva004FFC23@Rva004FFC23@@QAEPAURva004FFC23Node@@PAU2@0@Z @0x004FFC23 115B.
// Tree copy for map<int void*> nodes: clones the top through the twin of the
// rowed _M_clone_node 0x0053444F, links the parent, recurses right, then
// walks the left spine cloning. Same 115B shape as the rowed 0x002CF6CF
// copy and Rva002CFD96Copy precedent. Node layout (color +0 parent +4
// left +8 right +12) proven by the retail offsets. Callers at 0x004FFC4C
// 0x004FFC79 (self) and 0x004FFF0A in 0x004FFEAF; landing this unblocks
// 0x004FFEAF.
struct Rva004FFC23Node
{
	unsigned char m_color;
	unsigned char m_pad01[3];
	Rva004FFC23Node *m_parent;
	Rva004FFC23Node *m_left;
	Rva004FFC23Node *m_right;
	unsigned char m_value[8];
};

namespace _STL
{
	template <class T1, class T2> struct pair;
	template <class T> struct _Select1st;
	template <class T> struct less;
	template <class T> class allocator;
	template <class T> struct _Rb_tree_node;
	template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	class _Rb_tree
	{
	protected:
		typedef _Rb_tree_node<Value> *_Link_type;
		_Link_type _M_clone_node(_Link_type x);
	};
}

// The opaque map<int,void*> payload is 8 bytes; this matches the helper's
// map<int,int> value layout and reuses Rva004FFC96Copy's verified facade.
typedef _STL::pair<const int, int> Rva004FFC23Value;
typedef _STL::_Rb_tree<int, Rva004FFC23Value,
	_STL::_Select1st<Rva004FFC23Value>, _STL::less<int>,
	_STL::allocator<Rva004FFC23Value> > Rva004FFC23Tree;

struct Rva004FFC23 : Rva004FFC23Tree
{
	Rva004FFC23Node *rva004FFC23(Rva004FFC23Node *x, Rva004FFC23Node *p);
};

Rva004FFC23Node *Rva004FFC23::rva004FFC23(Rva004FFC23Node *x, Rva004FFC23Node *p)
{
	Rva004FFC23Node *top = (Rva004FFC23Node *)_M_clone_node(
		(_STL::_Rb_tree_node<Rva004FFC23Value> *)x);
	top->m_parent = p;
	if (x->m_right != 0)
		top->m_right = rva004FFC23(x->m_right, top);
	p = top;
	x = x->m_left;
	while (x != 0) {
		Rva004FFC23Node *y = (Rva004FFC23Node *)_M_clone_node(
			(_STL::_Rb_tree_node<Rva004FFC23Value> *)x);
		p->m_left = y;
		y->m_parent = p;
		if (x->m_right != 0)
			y->m_right = rva004FFC23(x->m_right, y);
		p = y;
		x = x->m_left;
	}
	return top;
}
