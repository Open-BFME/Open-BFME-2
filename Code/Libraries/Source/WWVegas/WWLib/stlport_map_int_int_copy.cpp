// cl: /GX- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// ?_M_copy@?$_Rb_tree@HU?$pair@$$CBHH@_STL@@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHH@_STL@@@2@@_STL@@AAEPAU?$_Rb_tree_node@U?$pair@$$CBHH@_STL@@@2@PAU32@0@Z,
// retail 0x002CF6CF, 115 bytes. Dedicated TU.
//
// map<int,int> red-black tree copy (STLport _M_copy shape: clone the top,
// link the parent, recurse right, then walk down the left spine cloning).
// The clone helper is the tree's own 0x002CF6B1 (opaque pin: the true
// _M_clone_node spelling is row-owned at 0x0053444F by a different body,
// so this TU declares it under an address-scoped name). No EH in retail
// (all callees nothrow under the malloc allocator), hence /GX- where the
// sibling map<int,int> TUs use /EHsc.

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
	Node *_M_create_node(const Value &x);
	Node *_M_copy(Node *x, Node *p);
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename _Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::Node *
_Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::_M_clone_node_for_copy(Node *x)
{
	Node *top = _M_create_node(x->m_value);
	top->m_color = x->m_color;
	top->m_left = 0;
	top->m_right = 0;
	return top;
}

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

typedef pair<const int, int> MapIntIntValue;
typedef _Select1st<MapIntIntValue> MapIntIntKeyOf;
typedef less<int> MapIntIntCompare;
typedef allocator<MapIntIntValue> MapIntIntAlloc;
typedef _Rb_tree<int, MapIntIntValue, MapIntIntKeyOf, MapIntIntCompare, MapIntIntAlloc> MapIntIntTree;

template MapIntIntTree::Node *MapIntIntTree::_M_copy(Node *x, Node *p);
template MapIntIntTree::Node *MapIntIntTree::_M_clone_node_for_copy(Node *x);

}
