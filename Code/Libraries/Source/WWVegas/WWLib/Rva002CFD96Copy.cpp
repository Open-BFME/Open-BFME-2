// cl: /MD
// ?rva002CFD96@Rva002CFD96@@QAEPAURva002CFD96Node@@PAU2@0@Z @0x002CFD96 115B.
// Tree copy for map<int,int> nodes: clones the top through the twin of the
// rowed _M_clone_node 0x0053444F, links the parent, recurses right, then
// walks the left spine cloning. Same 115B shape as the rowed 0x002CFCEE
// copy. Node layout (color +0 parent +4 left +8 right +12 value +10) proven
// by the retail offsets. Caller at 0x002D0253 unblocks 0x002D021C.
struct Rva002CFD96Node
{
	unsigned char m_color;
	unsigned char m_pad01[3];
	Rva002CFD96Node *m_parent;
	Rva002CFD96Node *m_left;
	Rva002CFD96Node *m_right;
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

typedef _STL::pair<const int, int> Rva002CFD96Value;
typedef _STL::_Rb_tree<int, Rva002CFD96Value,
	_STL::_Select1st<Rva002CFD96Value>, _STL::less<int>,
	_STL::allocator<Rva002CFD96Value> > Rva002CFD96Tree;

struct Rva002CFD96 : Rva002CFD96Tree
{
	Rva002CFD96Node *rva002CFD96(Rva002CFD96Node *x, Rva002CFD96Node *p);
};

Rva002CFD96Node *Rva002CFD96::rva002CFD96(Rva002CFD96Node *x, Rva002CFD96Node *p)
{
	Rva002CFD96Node *top = (Rva002CFD96Node *)_M_clone_node(
		(_STL::_Rb_tree_node<Rva002CFD96Value> *)x);
	top->m_parent = p;
	if (x->m_right != 0)
		top->m_right = rva002CFD96(x->m_right, top);
	p = top;
	x = x->m_left;
	while (x != 0) {
		Rva002CFD96Node *y = (Rva002CFD96Node *)_M_clone_node(
			(_STL::_Rb_tree_node<Rva002CFD96Value> *)x);
		p->m_left = y;
		y->m_parent = p;
		if (x->m_right != 0)
			y->m_right = rva002CFD96(x->m_right, y);
		p = y;
		x = x->m_left;
	}
	return top;
}
