// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
//
// ?rva00079D14@Rva00079D14Tree@@QAE?AURva00079D14Iter@@U2@ABVRva00079D14Value@@@Z
// Candidate 0x00079D14, 294B. family_scan's inventory extent is a boundary
// lead; byte verification decides the row. Its body is in the same
// operand-normalized family as the exact hinted insert at 0x00170EFE. Target
// calls 0x00079AB9 as the insertion worker and 0x00079B41 for fallback search,
// with _Rb_global increment/decrement at 0x24250/0x242C0. The tree header and
// unsigned key at node +0x10 are visible in the target bytes; trailing value
// layout and owning container remain unknown.
#include <map>

class Rva00079D14Value;

struct Rva00079D14Node
{
	unsigned int _color;
	Rva00079D14Node *_parent;
	Rva00079D14Node *_left;
	Rva00079D14Node *_right;
	unsigned int _key;
};

struct Rva00079D14Iter
{
    ::_STL::_Rb_tree_node_base *_M_node;
    Rva00079D14Iter() {}
    Rva00079D14Iter(Rva00079D14Node *p)
        : _M_node((::_STL::_Rb_tree_node_base *)p) {}
    Rva00079D14Iter &operator--()
    {
        _M_node = _STL::_Rb_global<bool>::_M_decrement(_M_node);
        return *this;
    }
};

struct Rva00079D14Out
{
	Rva00079D14Node *node;
	bool inserted;
	Rva00079D14Out(const Rva00079D14Iter &iter, bool flag)
		: node((Rva00079D14Node *)iter._M_node), inserted(flag) {}
};

class Rva00079D14Tree
{
public:
	Rva00079D14Iter rva00079AB9(Rva00079D14Node *x, Rva00079D14Node *y, const Rva00079D14Value &value, Rva00079D14Node *w);
	Rva00079D14Out rva00079B41(const Rva00079D14Value &value);
	Rva00079D14Iter rva00079D14(Rva00079D14Iter position, const Rva00079D14Value &value);
private:
	Rva00079D14Node *m_header; // +0x00
	unsigned int m_count; // +0x04
};

typedef Rva00079D14Out (Rva00079D14Tree::*Rva00079D14FindFn)(
	const Rva00079D14Value &);

Rva00079D14Iter Rva00079D14Tree::rva00079D14(Rva00079D14Iter position,
	const Rva00079D14Value &value)
{
	Rva00079D14Node *pos = ((Rva00079D14Node *)position._M_node);
	if (pos == m_header->_left) {
		if (m_count <= 0) {
			Rva00079D14FindFn find = (Rva00079D14FindFn)&Rva00079D14Tree::rva00079B41;
			return Rva00079D14Iter(((this->*find)(value)).node);
		}
		if (*(const unsigned int *)&value < *(const unsigned int *)&pos->_key) {
			return rva00079AB9(pos, pos, value, 0);
		} else {
			bool comp_pos_v = pos->_key < *(const unsigned int *)&value;
			if (comp_pos_v == false)
				return position;
			Rva00079D14Iter after = position;
			after._M_node = _STL::_Rb_global<bool>::_M_increment(
				(_STL::_Rb_tree_node_base *)((Rva00079D14Node *)after._M_node));
			if (((Rva00079D14Node *)after._M_node) == m_header) {
				return rva00079AB9(0, pos, value, pos);
			}
			if (*(const unsigned int *)&value < *(const unsigned int *)&((Rva00079D14Node *)after._M_node)->_key) {
				if (pos->_right == 0)
					return rva00079AB9(0, pos, value, pos);
				else
					return rva00079AB9(((Rva00079D14Node *)after._M_node), ((Rva00079D14Node *)after._M_node), value, 0);
			} else {
				Rva00079D14FindFn find = (Rva00079D14FindFn)&Rva00079D14Tree::rva00079B41;
				return Rva00079D14Iter(((this->*find)(value)).node);
			}
		}
	} else if (pos == m_header) {
		if (m_header->_right->_key < *(const unsigned int *)&value) {
			return rva00079AB9(0, m_header->_right, value, pos);
		} else {
			Rva00079D14FindFn find = (Rva00079D14FindFn)&Rva00079D14Tree::rva00079B41;
			return Rva00079D14Iter(((this->*find)(value)).node);
		}
	} else {
		Rva00079D14Iter before = position;
		before._M_node = _STL::_Rb_global<bool>::_M_decrement(
			(_STL::_Rb_tree_node_base *)((Rva00079D14Node *)before._M_node));
		bool comp_v_pos = *(const unsigned int *)&value < *(const unsigned int *)&pos->_key;
		if (comp_v_pos && ((Rva00079D14Node *)before._M_node)->_key < *(const unsigned int *)&value) {
			if (((Rva00079D14Node *)before._M_node)->_right == 0)
				return rva00079AB9(0, ((Rva00079D14Node *)before._M_node), value, ((Rva00079D14Node *)before._M_node));
			else
				return rva00079AB9(pos, pos, value, 0);
		} else {
			Rva00079D14Iter after = position;
			after._M_node = _STL::_Rb_global<bool>::_M_increment(
				(_STL::_Rb_tree_node_base *)((Rva00079D14Node *)after._M_node));
			bool comp_pos_v = !comp_v_pos;
			if (!comp_v_pos)
				comp_pos_v = pos->_key < *(const unsigned int *)&value;
			if (!comp_v_pos && comp_pos_v &&
				(((Rva00079D14Node *)after._M_node) == m_header ||
				 *(const unsigned int *)&value < *(const unsigned int *)&((Rva00079D14Node *)after._M_node)->_key)) {
				if (pos->_right == 0)
					return rva00079AB9(0, pos, value, pos);
				else
					return rva00079AB9(((Rva00079D14Node *)after._M_node), ((Rva00079D14Node *)after._M_node), value, 0);
			} else {
				if (comp_v_pos == comp_pos_v)
					return position;
				else {
					Rva00079D14FindFn find = (Rva00079D14FindFn)&Rva00079D14Tree::rva00079B41;
					return Rva00079D14Iter(((this->*find)(value)).node);
				}
			}
		}
	}
}
