// cl: /Od /GX- /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 _Rb_global<bool>::_M_increment - the in-order successor walk
// every red-black tree iterator runs. Retail keeps its frame pointer and
// reloads the node parameter on every step, so this body is unoptimized.

namespace _STL
{

// _M_color is bool, which _M_increment cannot see - it never reads the field,
// and a bool leaves the three pointers at the same offsets a int would. The
// decrement below does read it, and reads it as a byte.
typedef bool _Rb_tree_Color_type;

const _Rb_tree_Color_type _S_rb_tree_red = false;

struct _Rb_tree_node_base
{
	_Rb_tree_Color_type _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};

template <class Dummy>
class _Rb_global
{
public:
	static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *);
	static _Rb_tree_node_base *__cdecl _M_decrement(_Rb_tree_node_base *);
};

template <class Dummy>
_Rb_tree_node_base *__cdecl _Rb_global<Dummy>::_M_increment(
		_Rb_tree_node_base *node)
{
	if (node->_M_right != 0)
	{
		node = node->_M_right;

		while (node->_M_left != 0)
			node = node->_M_left;
	}
	else
	{
		_Rb_tree_node_base *parent = node->_M_parent;

		while (node == parent->_M_right)
		{
			node = parent;
			parent = parent->_M_parent;
		}

		if (node->_M_right != parent)
			node = parent;
	}

	return node;
}

// The predecessor walk, the mirror of the successor above. Named by the full
// gate's reloc sweep from its own call site. The first test is the header
// check every STLport tree iterator carries - a red node that is its own
// grandparent is the header, and its right child is the rightmost element -
// and the colour is compared against red, which is false.
template <class Dummy>
_Rb_tree_node_base *__cdecl _Rb_global<Dummy>::_M_decrement(
		_Rb_tree_node_base *node)
{
	if (node->_M_color == _S_rb_tree_red && node->_M_parent->_M_parent == node)
	{
		node = node->_M_right;
	}
	else if (node->_M_left != 0)
	{
		_Rb_tree_node_base *y = node->_M_left;

		while (y->_M_right != 0)
			y = y->_M_right;

		node = y;
	}
	else
	{
		_Rb_tree_node_base *y = node->_M_parent;

		while (node == y->_M_left)
		{
			node = y;
			y = y->_M_parent;
		}

		node = y;
	}

	return node;
}

template class _Rb_global<bool>;

}
