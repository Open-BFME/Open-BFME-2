// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
// ?rva00463F73@Rva004638C5@@QAEPAPAU_Rb_tree_node_base@_STL@@PAPAU23@PAU23@1PBUTreeKey00242F5E@@H@Z 0x00463F73 136B
// TreeKey tree insert core: create via rowed member 0x4638C5 in both the
// right and left branches then link rebalance via rowed 0x25490 count out.
// Evidence: callees 0x4638C5 just landed plus 0x25490 rowed; callers at
// 0x46405D plus 0x4644B8; signed key compare (jl) of the TreeKey int at
// +0x10 same as the 0x463F9B walker; same shape as stashed 0x4637B7.
#include <map>

struct TreeKey00242F5E
{
	char _d[8];
};

struct Rva004638C5Node
{
	char _head[0x10];
	char _val[8];
};

class Rva004638C5
{
	_STL::_Rb_tree_node_base *m_header;
	unsigned int m_count;
public:
	struct Rva004638C5Node *rva004638C5(const struct TreeKey00242F5E &x);
	_STL::_Rb_tree_node_base **rva00463F73(_STL::_Rb_tree_node_base **out, _STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *pos, const struct TreeKey00242F5E *val, int flag);
};

_STL::_Rb_tree_node_base **Rva004638C5::rva00463F73(_STL::_Rb_tree_node_base **out, _STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *pos, const struct TreeKey00242F5E *val, int flag)
{
	_STL::_Rb_tree_node_base *node;
	if (pos == m_header || (flag == 0 && (x != 0 || *(const int *)val < *(const int *)((const char *)pos + 0x10))))
	{
		node = (_STL::_Rb_tree_node_base *)rva004638C5(*val);
		pos->_M_left = node;
		if (pos == m_header)
		{
			m_header->_M_parent = node;
			m_header->_M_right = node;
		}
		else if (pos == m_header->_M_left)
			m_header->_M_left = node;
	}
	else
	{
		node = (_STL::_Rb_tree_node_base *)rva004638C5(*val);
		pos->_M_right = node;
		if (pos == m_header->_M_right)
			m_header->_M_right = node;
	}
	node->_M_left = 0;
	node->_M_right = 0;
	node->_M_parent = pos;
	_STL::_Rb_global<bool>::_Rebalance(node, m_header->_M_parent);
	++m_count;
	*out = node;
	return out;
}
