// cl: /Od /GX- /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 _Rb_global<bool>::_M_increment - the in-order successor walk
// every red-black tree iterator runs. Retail keeps its frame pointer and
// reloads the node parameter on every step, so this body is unoptimized.

namespace _STL
{

struct _Rb_tree_node_base
{
	int _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};

template <class Dummy>
class _Rb_global
{
public:
	static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *);
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

template class _Rb_global<bool>;

}
