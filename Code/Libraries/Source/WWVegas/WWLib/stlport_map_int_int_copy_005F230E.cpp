// cl: /GX- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// ?_M_copy_005F230E@?$_Rb_tree@HU?$pair@$$CBHH@_STL@@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHH@_STL@@@2@@_STL@@AAEPAU?$_Rb_tree_node@U?$pair@$$CBHH@_STL@@@2@PAU32@0@Z,
// retail 0x005F230E, 115 bytes. Dedicated TU.
//
// map<int,int> red-black tree copy duplicate (STLport _M_copy shape: clone
// the top, link the parent, recurse right, then walk down the left spine
// cloning). Retail calls the rowed clone 0x002CF6B1 and itself, identical
// to the rowed copies 0x002CF6CF 0x004E1D95 0x006008E6 modulo relocations;
// address-scoped spelling follows the fleet _M_copy_004E1D95 precedent since
// the unsuffixed name is claimed by 0x002CF6CF. No EH in retail hence /GX-.
#define _M_copy _M_copy_005F230E

namespace _STL
{

template <class T>
struct less
{
};

template <class T>
class allocator
{
};

template <class K, class V>
struct pair
{
	K first;
	V second;
};

template <class P>
struct _Select1st
{
};

struct _Rb_tree_node_base
{
	char m_color;
	char m_pad[3];
	_Rb_tree_node_base *m_parent;
	_Rb_tree_node_base *m_left;
	_Rb_tree_node_base *m_right;
};

template <class V>
struct _Rb_tree_node : public _Rb_tree_node_base
{
	V m_value;
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
public:
	typedef _Rb_tree_node<Value> Node;

private:
	Node *_M_clone_node_for_copy(Node *x);
	Node *_M_copy(Node *x, Node *p);
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename _Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::Node *
_Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::_M_copy(Node *x, Node *p)
{
	Node *top = _M_clone_node_for_copy(x);
	top->m_parent = (_Rb_tree_node_base *)p;
	if (x->m_right != 0)
		top->m_right = (_Rb_tree_node_base *)_M_copy((Node *)x->m_right, top);
	p = top;
	x = (Node *)x->m_left;
	while (x != 0) {
		Node *y = _M_clone_node_for_copy(x);
		p->m_left = (_Rb_tree_node_base *)y;
		y->m_parent = (_Rb_tree_node_base *)p;
		if (x->m_right != 0)
			y->m_right = (_Rb_tree_node_base *)_M_copy((Node *)x->m_right, y);
		p = y;
		x = (Node *)x->m_left;
	}
	return top;
}

typedef pair<const int, int> MapIntIntValue005F230E;
typedef _Select1st<MapIntIntValue005F230E> MapIntIntKeyOf005F230E;
typedef less<int> MapIntIntCompare005F230E;
typedef allocator<MapIntIntValue005F230E> MapIntIntAlloc005F230E;
typedef _Rb_tree<int, MapIntIntValue005F230E, MapIntIntKeyOf005F230E, MapIntIntCompare005F230E, MapIntIntAlloc005F230E> MapIntIntTree005F230E;

template MapIntIntTree005F230E::Node *MapIntIntTree005F230E::_M_copy(Node *x, Node *p);

}
#undef _M_copy
