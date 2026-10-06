// cl: /MD
// ?rva001FD7C4@Rva001FD7C4@@QAEPAURva001FD7C4Node@@PAU2@0@Z @0x001FD7C4 115B.
// Tree copy for map<int,int> nodes: clones the top through the twin of the
// rowed _M_clone_node 0x0053444F, links the parent, recurses right, then
// walks the left spine cloning. Same 115B shape as Rva001FD751Copy precedent.
// Node layout (color +0 parent +4 left +8 right +12 value +10) proven by the
// retail offsets. Landing this unblocks 0x001FDAB0 and 0x001FD952; callers at
// 0x001FD7ED 0x001FD81A (self) and 0x001FD989 0x001FDB0B.
struct Rva001FD7C4Node
{
	unsigned char m_color;
	unsigned char m_pad01[3];
	Rva001FD7C4Node *m_parent;
	Rva001FD7C4Node *m_left;
	Rva001FD7C4Node *m_right;
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

typedef _STL::pair<const int, int> Rva001FD7C4Value;
typedef _STL::_Rb_tree<int, Rva001FD7C4Value,
	_STL::_Select1st<Rva001FD7C4Value>, _STL::less<int>,
	_STL::allocator<Rva001FD7C4Value> > Rva001FD7C4Tree;

struct Rva001FD7C4 : Rva001FD7C4Tree
{
	Rva001FD7C4Node *rva001FD7C4(Rva001FD7C4Node *x, Rva001FD7C4Node *p);
};

Rva001FD7C4Node *Rva001FD7C4::rva001FD7C4(Rva001FD7C4Node *x, Rva001FD7C4Node *p)
{
	Rva001FD7C4Node *top = (Rva001FD7C4Node *)_M_clone_node(
		(_STL::_Rb_tree_node<Rva001FD7C4Value> *)x);
	top->m_parent = p;
	if (x->m_right != 0)
		top->m_right = rva001FD7C4(x->m_right, top);
	p = top;
	x = x->m_left;
	while (x != 0) {
		Rva001FD7C4Node *y = (Rva001FD7C4Node *)_M_clone_node(
			(_STL::_Rb_tree_node<Rva001FD7C4Value> *)x);
		p->m_left = y;
		y->m_parent = p;
		if (x->m_right != 0)
			y->m_right = rva001FD7C4(x->m_right, y);
		p = y;
		x = x->m_left;
	}
	return top;
}
