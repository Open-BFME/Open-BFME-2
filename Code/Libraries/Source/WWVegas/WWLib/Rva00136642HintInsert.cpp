// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?rva00136642@Rva001364F7@@QAE?AURva001364F7Iter@@U2@ABUTreeKey00242F5E@@@Z
// Target 0x00136642, 294 bytes. Target evidence: its REL32 calls at +0x6B
// and +0x114 land on the matched TreeKey tree helpers 0x001364F7 and
// 0x0013657F; the same target uses _Rb_global increment/decrement at
// 0x00024250 and 0x000242C0. Those helpers establish the 8-byte value with
// an unsigned id at +0 and an opaque dword at +4, plus the hinted-insert and
// duplicate-search relationship. The owning set/map name is not established.
//
// Code-shape guide: matched 294-byte Rva004075E0::rva00407C7F at 0x00407C7F.
// Its source provides the same hint/edge/neighbor algorithm and iterator ABI;
// the target's node and helper layouts below come from the target call chain.
struct TreeKey00242F5E { unsigned int m_id; char _pad[4]; };
struct RvaNode1364F7 {
	int _c0;
	RvaNode1364F7 *_parent;
	RvaNode1364F7 *_left;
	RvaNode1364F7 *_right;
	TreeKey00242F5E _key;
};
struct Rva001364F7Iter {
	RvaNode1364F7 *m_node;
	Rva001364F7Iter(RvaNode1364F7 *node);
};
// ??0Rva001364F7Iter@@QAE@PAURvaNode1364F7@@@Z present-unmatched
inline Rva001364F7Iter::Rva001364F7Iter(RvaNode1364F7 *node) : m_node(node) {}
struct RvaOut13657F {
	RvaNode1364F7 *node;
	bool inserted;
};
namespace _STL {
struct _Rb_tree_node_base {};
template <class D> class _Rb_global {
public:
	static _Rb_tree_node_base *_M_decrement(_Rb_tree_node_base *x);
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *x);
};
}
struct Rva001364F7 {
	RvaNode1364F7 *m_root;
	unsigned m_count;
	Rva001364F7Iter rva001364F7(RvaNode1364F7 *a, RvaNode1364F7 *b,
		const TreeKey00242F5E *value, RvaNode1364F7 *c);
	RvaOut13657F *rva0013657F(RvaOut13657F *out, const TreeKey00242F5E *value);
	Rva001364F7Iter rva00136642(Rva001364F7Iter position, const TreeKey00242F5E &value);
};
typedef RvaOut13657F (Rva001364F7::*Rva0013657FOutFn)(const TreeKey00242F5E *);

Rva001364F7Iter Rva001364F7::rva00136642(Rva001364F7Iter position, const TreeKey00242F5E &value)
{
	RvaNode1364F7 *pos = position.m_node;
	if (pos == m_root->_left) {
		if (m_count <= 0) {
			Rva0013657FOutFn find = (Rva0013657FOutFn)&Rva001364F7::rva0013657F;
			return Rva001364F7Iter(((this->*find)(&value)).node);
		}
		if (value.m_id < pos->_key.m_id) {
			return rva001364F7(pos, pos, &value, 0);
		} else {
			bool comp_pos_v = pos->_key.m_id < value.m_id;
			if (comp_pos_v == false)
				return position;
			Rva001364F7Iter after = position;
			after.m_node = (RvaNode1364F7 *)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base *)after.m_node);
			if (after.m_node == m_root) {
				return rva001364F7(0, pos, &value, pos);
			}
			if (value.m_id < after.m_node->_key.m_id) {
				if (pos->_right == 0)
					return rva001364F7(0, pos, &value, pos);
				else
					return rva001364F7(after.m_node, after.m_node, &value, 0);
			} else {
				Rva0013657FOutFn find = (Rva0013657FOutFn)&Rva001364F7::rva0013657F;
				return Rva001364F7Iter(((this->*find)(&value)).node);
			}
		}
	} else if (pos == m_root) {
		if (m_root->_right->_key.m_id < value.m_id) {
			return rva001364F7(0, m_root->_right, &value, pos);
		} else {
			Rva0013657FOutFn find = (Rva0013657FOutFn)&Rva001364F7::rva0013657F;
			return Rva001364F7Iter(((this->*find)(&value)).node);
		}
	} else {
		Rva001364F7Iter before = position;
		before.m_node = (RvaNode1364F7 *)_STL::_Rb_global<bool>::_M_decrement((_STL::_Rb_tree_node_base *)before.m_node);
		bool comp_v_pos = value.m_id < pos->_key.m_id;
		if (comp_v_pos && before.m_node->_key.m_id < value.m_id) {
			if (before.m_node->_right == 0)
				return rva001364F7(0, before.m_node, &value, before.m_node);
			else
				return rva001364F7(pos, pos, &value, 0);
		} else {
			Rva001364F7Iter after = position;
			after.m_node = (RvaNode1364F7 *)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base *)after.m_node);
			bool comp_pos_v = !comp_v_pos;
			if (!comp_v_pos)
				comp_pos_v = pos->_key.m_id < value.m_id;
			if (!comp_v_pos && comp_pos_v && (after.m_node == m_root || value.m_id < after.m_node->_key.m_id)) {
				if (pos->_right == 0)
					return rva001364F7(0, pos, &value, pos);
				else
					return rva001364F7(after.m_node, after.m_node, &value, 0);
			} else {
				if (comp_v_pos == comp_pos_v)
					return position;
				else {
					Rva0013657FOutFn find = (Rva0013657FOutFn)&Rva001364F7::rva0013657F;
					return Rva001364F7Iter(((this->*find)(&value)).node);
				}
			}
		}
	}
}

class Rva001363CC
{
public:
	~Rva001363CC();
};

class Rva00136768Dtor
{
public:
	~Rva00136768Dtor();
};

Rva00136768Dtor::~Rva00136768Dtor()
{
	((Rva001363CC *)this)->~Rva001363CC();
}

