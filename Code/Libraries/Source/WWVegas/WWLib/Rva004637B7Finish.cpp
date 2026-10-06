// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
// ?rva004637B7@Rva00463782@@QAE?AURva00463782Iter@@PAU_Rb_tree_node_base@_STL@@0PBVRva0046267A@@H@Z 0x004637B7 136B
// _Rb_tree::_M_insert for the Rva0046267A (0x50B) red-black tree: create the
// node through the member create_node 0x4634BA, link it left/right of pos,
// fix up the header root/leftmost/rightmost, then rebalance with rowed 0x25490
// and bump the node count at this+4. Key is the unsigned int at value +0
// (node +0x10); retail branches with jb, so the comparator is less<unsigned>.
// Evidence: 136B shape identical to the landed map<int,int> _M_insert 0x38341E
// except the 0x4637DA jl->jb; callees 0x4634BA and 0x25490 both rowed; caller
// 0x4638A1. The 0x4634BA body is byte-identical to a thiscall member with an
// unused receiver, so this source calls it as a member. 0x4634BA is currently
// rowed only under the free __stdcall spelling, so this member spelling must
// be added to reverse/symbols.csv at 0x004634BA for the call to resolve.
#include <map>

class Rva0046267A;

struct Rva004634BANode;
struct Rva0046383FOut;
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

Rva00463782Iter Rva00463782::rva004637B7(_STL::_Rb_tree_node_base *x, _STL::_Rb_tree_node_base *pos, const class Rva0046267A *val, int flag)
{
	_STL::_Rb_tree_node_base *node;
	if (pos == m_header || (flag == 0 && (x != 0 || *(const unsigned *)val < *(const unsigned *)((const char *)pos + 0x10))))
	{
		node = (_STL::_Rb_tree_node_base *)rva004634BA(*val);
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
		node = (_STL::_Rb_tree_node_base *)rva004634BA(*val);
		pos->_M_right = node;
		if (pos == m_header->_M_right)
			m_header->_M_right = node;
	}
	node->_M_left = 0;
	node->_M_right = 0;
	node->_M_parent = pos;
	_STL::_Rb_global<bool>::_Rebalance(node, m_header->_M_parent);
	++m_count;
	return Rva00463782Iter(node);
}
