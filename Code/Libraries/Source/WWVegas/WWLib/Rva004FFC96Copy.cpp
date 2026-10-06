// cl: /MD
// ?rva004FFC96@Rva004FFC96@@QAEPAURva004FFC96Node@@PAU2@0@Z @0x004FFC96 115B.
// Tree copy for map<int void*> nodes: clones the top through the twin of the
// rowed _M_clone_node 0x0053444F, links the parent, recurses right, then
// walks the left spine cloning. Same 115B shape as the rowed 0x002CF6CF
// copy and Rva004FFC23Copy precedent. Node layout (color +0 parent +4
// left +8 right +12) proven by the retail offsets. Callers at 0x004FFCBF
// 0x004FFCEC (self) and 0x004FFFAF in 0x004FFF54; landing this unblocks
// 0x004FFF54.
struct Rva004FFC96Node
{
	unsigned char m_color;
	unsigned char m_pad01[3];
	Rva004FFC96Node *m_parent;
	Rva004FFC96Node *m_left;
	Rva004FFC96Node *m_right;
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

typedef _STL::pair<const int, int> Rva004FFC96Value;
typedef _STL::_Rb_tree<int, Rva004FFC96Value,
	_STL::_Select1st<Rva004FFC96Value>, _STL::less<int>,
	_STL::allocator<Rva004FFC96Value> > Rva004FFC96Tree;

struct Rva004FFC96 : Rva004FFC96Tree
{
	Rva004FFC96Node *rva004FFC96(Rva004FFC96Node *x, Rva004FFC96Node *p);
};

Rva004FFC96Node *Rva004FFC96::rva004FFC96(Rva004FFC96Node *x, Rva004FFC96Node *p)
{
	Rva004FFC96Node *top = (Rva004FFC96Node *)_M_clone_node(
		(_STL::_Rb_tree_node<Rva004FFC96Value> *)x);
	top->m_parent = p;
	if (x->m_right != 0)
		top->m_right = rva004FFC96(x->m_right, top);
	p = top;
	x = x->m_left;
	while (x != 0) {
		Rva004FFC96Node *y = (Rva004FFC96Node *)_M_clone_node(
			(_STL::_Rb_tree_node<Rva004FFC96Value> *)x);
		p->m_left = y;
		y->m_parent = p;
		if (x->m_right != 0)
			y->m_right = rva004FFC96(x->m_right, y);
		p = y;
		x = x->m_left;
	}
	return top;
}
