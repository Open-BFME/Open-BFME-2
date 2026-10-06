// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
//
// ?rva00463E4D@Rva00463782@@QAE?AURva00463782Iter@@U2@ABVRva0046267A@@@Z
// Target 0x00463E4D, 294 bytes. Target calls the matched tree worker
// 0x004637B7 at +0x6A and duplicate-search helper 0x0046383F at +0x113;
// both helpers use this tree view and the same 0x10 node-base/value offset.
// Its increment/decrement calls land on rowed 0x24250 and 0x242C0. The body
// follows the matched 294-byte hint-insert shape at 0x00407C7F and 0x00136642.
// Target construction evidence at 0x004634BA allocates 0x60 bytes for a
// 0x10-byte node base plus this 0x50-byte value. The internal payload remains
// opaque here; the owner of this set and the record's real field names are
// not established by byte shape alone.
#include <map>

class Rva0046267A
{
public:
	unsigned int m_key;
	char _opaque[0x4C];
};

struct Rva004634BANode;

struct Rva00463782Iter
{
	_STL::_Rb_tree_node_base *_M_node;
	Rva00463782Iter(_STL::_Rb_tree_node_base *node) : _M_node(node) {}
};

struct Rva0046383FOut
{
	_STL::_Rb_tree_node_base *node;
	bool inserted;
};

class Rva00463782
{
	_STL::_Rb_tree_node_base *m_header;
	unsigned int m_count;
public:
	Rva004634BANode *rva004634BA(const Rva0046267A &x);
	Rva00463782Iter rva004637B7(_STL::_Rb_tree_node_base *x,
		_STL::_Rb_tree_node_base *pos, const Rva0046267A *val, int flag);
	_STL::_Rb_tree_node_base *rva0046383F(Rva0046383FOut *out,
		const Rva0046267A *val);
	Rva00463782Iter rva00463E4D(Rva00463782Iter position,
		const Rva0046267A &value);
};

typedef Rva0046383FOut (Rva00463782::*Rva0046383FFindFn)(const Rva0046267A *);

Rva00463782Iter Rva00463782::rva00463E4D(Rva00463782Iter position,
	const Rva0046267A &value)
{
	_STL::_Rb_tree_node_base *pos = position._M_node;
	if (pos == m_header->_M_left) {
		if (m_count <= 0) {
			Rva0046383FFindFn find = (Rva0046383FFindFn)&Rva00463782::rva0046383F;
			return Rva00463782Iter(((this->*find)(&value)).node);
		}
		if (value.m_key < *(const unsigned int *)((const char *)pos + 0x10))
			return rva004637B7(pos, pos, &value, 0);
		else {
			bool comp_pos_v = *(const unsigned int *)((const char *)pos + 0x10) < value.m_key;
			if (comp_pos_v == false)
				return position;
			Rva00463782Iter after = position;
			after._M_node = _STL::_Rb_global<bool>::_M_increment(after._M_node);
			if (after._M_node == m_header)
				return rva004637B7(0, pos, &value, (int)pos);
			if (value.m_key < *(const unsigned int *)((const char *)after._M_node + 0x10)) {
				if (pos->_M_right == 0)
					return rva004637B7(0, pos, &value, (int)pos);
				else
					return rva004637B7(after._M_node, after._M_node, &value, 0);
			} else {
				Rva0046383FFindFn find = (Rva0046383FFindFn)&Rva00463782::rva0046383F;
				return Rva00463782Iter(((this->*find)(&value)).node);
			}
		}
	} else if (pos == m_header) {
		if (*(const unsigned int *)((const char *)m_header->_M_right + 0x10) < value.m_key)
			return rva004637B7(0, m_header->_M_right, &value, (int)pos);
		else {
			Rva0046383FFindFn find = (Rva0046383FFindFn)&Rva00463782::rva0046383F;
			return Rva00463782Iter(((this->*find)(&value)).node);
		}
	} else {
		Rva00463782Iter before = position;
		before._M_node = _STL::_Rb_global<bool>::_M_decrement(before._M_node);
		bool comp_v_pos = value.m_key < *(const unsigned int *)((const char *)pos + 0x10);
		if (comp_v_pos && *(const unsigned int *)((const char *)before._M_node + 0x10) < value.m_key) {
			if (before._M_node->_M_right == 0)
				return rva004637B7(0, before._M_node, &value, (int)before._M_node);
			else
				return rva004637B7(pos, pos, &value, 0);
		} else {
			Rva00463782Iter after = position;
			after._M_node = _STL::_Rb_global<bool>::_M_increment(after._M_node);
			bool comp_pos_v = !comp_v_pos;
			if (!comp_v_pos)
				comp_pos_v = *(const unsigned int *)((const char *)pos + 0x10) < value.m_key;
			if (!comp_v_pos && comp_pos_v && (after._M_node == m_header || value.m_key < *(const unsigned int *)((const char *)after._M_node + 0x10))) {
				if (pos->_M_right == 0)
					return rva004637B7(0, pos, &value, (int)pos);
				else
					return rva004637B7(after._M_node, after._M_node, &value, 0);
			} else {
				if (comp_v_pos == comp_pos_v)
					return position;
				else {
					Rva0046383FFindFn find = (Rva0046383FFindFn)&Rva00463782::rva0046383F;
					return Rva00463782Iter(((this->*find)(&value)).node);
				}
			}
		}
	}
}
