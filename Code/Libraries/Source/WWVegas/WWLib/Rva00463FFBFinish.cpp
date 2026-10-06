// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
// ?rva00463FFB@Rva004638C5@@QAEPAU_Rb_tree_node_base@_STL@@PAURva00463FFBOut@@PBUTreeKey00242F5E@@@Z 0x00463FFB 134B
// TreeKey insert_unique via rowed _M_decrement 0x242C0 plus just-landed _M_insert 0x463F73.
// Evidence: callees 0x242C0 and 0x463F73 both rowed; caller at 0x464561; prev 0x463F73 same flags and node layout; signed key compare (setl/jge) of int at +0x10 same as 0x463F73.
#include <map>

struct TreeKey00242F5E
{
	char _d[8];
};

struct Rva004638C5Node;

struct Rva00463FFBOut
{
	_STL::_Rb_tree_node_base *node;
	bool inserted;
};

class Rva004638C5
{
	_STL::_Rb_tree_node_base *m_header;
	unsigned int m_count;
public:
	struct Rva004638C5Node *rva004638C5(const struct TreeKey00242F5E &x);
	_STL::_Rb_tree_node_base **rva00463F73(_STL::_Rb_tree_node_base **out, _STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *pos, const struct TreeKey00242F5E *val, int flag);
	_STL::_Rb_tree_node_base *rva00463FFB(struct Rva00463FFBOut *out, const struct TreeKey00242F5E *val);
};

_STL::_Rb_tree_node_base *Rva004638C5::rva00463FFB(struct Rva00463FFBOut *out, const struct TreeKey00242F5E *v)
{
	_STL::_Rb_tree_node_base *header = m_header;
	_STL::_Rb_tree_node_base *x = header->_M_parent;
	_STL::_Rb_tree_node_base *y = header;
	bool comp = true;
	while (x != 0) {
		y = x;
		comp = *(const int *)v < *(const int *)((const char *)x + 0x10);
		x = comp ? x->_M_left : x->_M_right;
	}
	_STL::_Rb_tree_node_base *j = y;
	if (comp) {
		if (y == header->_M_left) {
			out->node = *rva00463F73((_STL::_Rb_tree_node_base **)&v, y, y, v, 0);
			out->inserted = true;
			return (_STL::_Rb_tree_node_base *)out;
		}
		j = _STL::_Rb_global<bool>::_M_decrement(j);
	}
	if (*(const int *)((const char *)j + 0x10) < *(const int *)v) {
		out->node = *rva00463F73((_STL::_Rb_tree_node_base **)&v, x, y, v, 0);
		out->inserted = true;
		return (_STL::_Rb_tree_node_base *)out;
	}
	out->node = j;
	out->inserted = false;
	return (_STL::_Rb_tree_node_base *)out;
}
