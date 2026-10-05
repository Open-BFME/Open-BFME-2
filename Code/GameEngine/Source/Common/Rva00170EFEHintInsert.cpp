// cl: /O1 /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
//
// ?rva00170EFE@Rva00170BFF@@QAE?AURva00170EFEIter@@U2@ABVRva00170999@@@Z
// Candidate 0x00170EFE, 294B. The inventory extent and family_scan's
// instruction-normalized family are boundary leads; byte verification decides
// this row. Target calls the rowed tree worker 0x00170BFF and the direct
// value-search helper at 0x00170DB7, plus rowed _Rb_global increment/decrement
// at 0x24250/0x242C0. The worker's 0x24-byte node establishes the 0x14-byte
// value at +0x10; the body compares its first dword unsigned. Owner and full
// value identity remain address-derived from the target call chain.
#include <map>

class Rva00170999;

struct Rva00170EFENode
{
	unsigned int _color;
	Rva00170EFENode *_parent;
	Rva00170EFENode *_left;
	Rva00170EFENode *_right;
	char _val10[0x14];
};

struct Rva00170EFEIter
{
	Rva00170EFENode *node;
	Rva00170EFEIter(Rva00170EFENode *p) : node(p) {}
};

struct Rva00170DB7Out
{
	Rva00170EFENode *node;
	bool inserted;
};

class Rva00170BFF
{
	Rva00170EFENode *m_00Head;
	unsigned int m_04Flag;
public:
	Rva00170EFEIter rva00170BFF(Rva00170EFENode *x,
		Rva00170EFENode *y, const Rva00170999 &value,
		Rva00170EFENode *w);
	Rva00170DB7Out rva00170DB7(const Rva00170999 &value);
	Rva00170EFEIter rva00170EFE(Rva00170EFEIter position,
		const Rva00170999 &value);
};

typedef Rva00170DB7Out (Rva00170BFF::*Rva00170EFEFindFn)(
	const Rva00170999 &);

Rva00170EFEIter Rva00170BFF::rva00170EFE(Rva00170EFEIter position,
	const Rva00170999 &value)
{
	Rva00170EFENode *pos = position.node;
	if (pos == m_00Head->_left) {
		if (m_04Flag <= 0) {
			Rva00170EFEFindFn find = (Rva00170EFEFindFn)&Rva00170BFF::rva00170DB7;
			return Rva00170EFEIter(((this->*find)(value)).node);
		}
		if (*(const unsigned int *)&value < *(const unsigned int *)pos->_val10) {
			return rva00170BFF(pos, pos, value, 0);
		} else {
			bool comp_pos_v = *(const unsigned int *)pos->_val10 < *(const unsigned int *)&value;
			if (comp_pos_v == false)
				return position;
			Rva00170EFEIter after = position;
			after.node = (Rva00170EFENode *)_STL::_Rb_global<bool>::_M_increment(
				(_STL::_Rb_tree_node_base *)after.node);
			if (after.node == m_00Head) {
				return rva00170BFF(0, pos, value, pos);
			}
			if (*(const unsigned int *)&value < *(const unsigned int *)after.node->_val10) {
				if (pos->_right == 0)
					return rva00170BFF(0, pos, value, pos);
				else
					return rva00170BFF(after.node, after.node, value, 0);
			} else {
				Rva00170EFEFindFn find = (Rva00170EFEFindFn)&Rva00170BFF::rva00170DB7;
				return Rva00170EFEIter(((this->*find)(value)).node);
			}
		}
	} else if (pos == m_00Head) {
		if (*(const unsigned int *)m_00Head->_right->_val10 < *(const unsigned int *)&value) {
			return rva00170BFF(0, m_00Head->_right, value, pos);
		} else {
			Rva00170EFEFindFn find = (Rva00170EFEFindFn)&Rva00170BFF::rva00170DB7;
			return Rva00170EFEIter(((this->*find)(value)).node);
		}
	} else {
		Rva00170EFEIter before = position;
		before.node = (Rva00170EFENode *)_STL::_Rb_global<bool>::_M_decrement(
			(_STL::_Rb_tree_node_base *)before.node);
		bool comp_v_pos = *(const unsigned int *)&value < *(const unsigned int *)pos->_val10;
		if (comp_v_pos && *(const unsigned int *)before.node->_val10 < *(const unsigned int *)&value) {
			if (before.node->_right == 0)
				return rva00170BFF(0, before.node, value, before.node);
			else
				return rva00170BFF(pos, pos, value, 0);
		} else {
			Rva00170EFEIter after = position;
			after.node = (Rva00170EFENode *)_STL::_Rb_global<bool>::_M_increment(
				(_STL::_Rb_tree_node_base *)after.node);
			bool comp_pos_v = !comp_v_pos;
			if (!comp_v_pos)
				comp_pos_v = *(const unsigned int *)pos->_val10 < *(const unsigned int *)&value;
			if (!comp_v_pos && comp_pos_v &&
				(after.node == m_00Head ||
				 *(const unsigned int *)&value < *(const unsigned int *)after.node->_val10)) {
				if (pos->_right == 0)
					return rva00170BFF(0, pos, value, pos);
				else
					return rva00170BFF(after.node, after.node, value, 0);
			} else {
				if (comp_v_pos == comp_pos_v)
					return position;
				else {
					Rva00170EFEFindFn find = (Rva00170EFEFindFn)&Rva00170BFF::rva00170DB7;
					return Rva00170EFEIter(((this->*find)(value)).node);
				}
			}
		}
	}
}
