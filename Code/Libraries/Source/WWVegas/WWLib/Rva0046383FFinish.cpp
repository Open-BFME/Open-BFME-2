// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
// ?rva0046383F@Rva00463782@@QAEPAU_Rb_tree_node_base@_STL@@PAURva0046383FOut@@PBVRva0046267A@@@Z @0x0046383F 134B: _Rb_tree insert_unique for Rva0046267A tree via rowed _M_insert plus _M_decrement.
// Evidence: callees _M_decrement 0x000242C0 plus rva004637B7 0x004637B7 both rowed; caller 0x00463E4D; prev 0x004637B7 and next 0x004638C5 share flags and node layout.
#include <map>

class Rva0046267A
{
public:
	unsigned int m_key;
	char _opaque[0x4C];
};

struct Rva004634BANode;

struct Rva0046383FOut
{
	_STL::_Rb_tree_node_base *node;
	bool inserted;
};

struct Rva00463782Iter
{
	_STL::_Rb_tree_node_base *_M_node;
	Rva00463782Iter(_STL::_Rb_tree_node_base *node) : _M_node(node) {}
};

class Rva00463782
{
	_STL::_Rb_tree_node_base *m_header;
	unsigned int m_count;
public:
	struct Rva004634BANode *rva004634BA(const class Rva0046267A &x);
	Rva00463782Iter rva004637B7(_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *pos, const class Rva0046267A *val, int flag);
	_STL::_Rb_tree_node_base *rva0046383F(struct Rva0046383FOut *out, const class Rva0046267A *val);
	Rva00463782Iter rva00463E4D(Rva00463782Iter position, const class Rva0046267A &value);
};

typedef _STL::_Rb_tree_node_base **(Rva00463782::*Rva004637B7OutFn)(
	_STL::_Rb_tree_node_base **out, _STL::_Rb_tree_node_base *x,
	_STL::_Rb_tree_node_base *pos, const Rva0046267A *val, int flag);

_STL::_Rb_tree_node_base *Rva00463782::rva0046383F(struct Rva0046383FOut *out, const Rva0046267A *v)
{
	_STL::_Rb_tree_node_base *header = m_header;
	_STL::_Rb_tree_node_base *x = header->_M_parent;
	_STL::_Rb_tree_node_base *y = header;
	bool comp = true;
	while (x != 0) {
		y = x;
		comp = v->m_key < *(const unsigned int *)((const char *)x + 0x10);
		x = comp ? x->_M_left : x->_M_right;
	}
	_STL::_Rb_tree_node_base *j = y;
	Rva004637B7OutFn insert = (Rva004637B7OutFn)&Rva00463782::rva004637B7;
	if (comp) {
		if (y == header->_M_left) {
			out->node = *((this->*insert)((_STL::_Rb_tree_node_base **)&v, y, y, v, 0));
			out->inserted = true;
			return (_STL::_Rb_tree_node_base *)out;
		}
		j = _STL::_Rb_global<bool>::_M_decrement(j);
	}
	if (*(const unsigned int *)((const char *)j + 0x10) < v->m_key) {
		out->node = *((this->*insert)((_STL::_Rb_tree_node_base **)&v, x, y, v, 0));
		out->inserted = true;
		return (_STL::_Rb_tree_node_base *)out;
	}
	out->node = j;
	out->inserted = false;
	return (_STL::_Rb_tree_node_base *)out;
}
