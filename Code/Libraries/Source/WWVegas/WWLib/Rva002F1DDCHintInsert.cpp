// cl: /O1 /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
//
// ?rva002F1DDC@Rva002F1DDCTree@@QAE?AURva002F1DDCIter@@U2@ABVRva002F1DDCValue@@@Z
// Candidate 0x002F1DDC, 294B. family_scan's inventory extent is a boundary
// lead; byte verification decides the row. Its body is in the same
// operand-normalized family as the exact hinted insert at 0x00170EFE. Target
// calls 0x002F0DD6 as the insertion worker and 0x002F0E5E for fallback search,
// with _Rb_global increment/decrement at 0x24250/0x242C0. The tree header and
// unsigned key at node +0x10 are visible in the target bytes; trailing value
// layout and owning container remain unknown.
#include <map>

class Rva002F1DDCValue;

struct Rva002F1DDCNode
{
	unsigned int _color;
	Rva002F1DDCNode *_parent;
	Rva002F1DDCNode *_left;
	Rva002F1DDCNode *_right;
	unsigned int _key;
};

struct Rva002F1DDCIter
{
	Rva002F1DDCNode *node;
	Rva002F1DDCIter(Rva002F1DDCNode *p) : node(p) {}
};

struct Rva002F1DDCOut
{
	Rva002F1DDCNode *node;
	bool inserted;
};

class Rva002F1DDCTree
{
	Rva002F1DDCNode *m_header;
	unsigned int m_count;
public:
	Rva002F1DDCIter rva002F0DD6(Rva002F1DDCNode *x,
		Rva002F1DDCNode *y, const Rva002F1DDCValue &value,
		Rva002F1DDCNode *w);
	Rva002F1DDCOut rva002F0E5E(const Rva002F1DDCValue &value);
	Rva002F1DDCIter rva002F1DDC(Rva002F1DDCIter position,
		const Rva002F1DDCValue &value);
};

typedef Rva002F1DDCOut (Rva002F1DDCTree::*Rva002F1DDCFindFn)(
	const Rva002F1DDCValue &);

Rva002F1DDCIter Rva002F1DDCTree::rva002F1DDC(Rva002F1DDCIter position,
	const Rva002F1DDCValue &value)
{
	Rva002F1DDCNode *pos = position.node;
	if (pos == m_header->_left) {
		if (m_count <= 0) {
			Rva002F1DDCFindFn find = (Rva002F1DDCFindFn)&Rva002F1DDCTree::rva002F0E5E;
			return Rva002F1DDCIter(((this->*find)(value)).node);
		}
		if (*(const unsigned int *)&value < *(const unsigned int *)&pos->_key) {
			return rva002F0DD6(pos, pos, value, 0);
		} else {
			bool comp_pos_v = pos->_key < *(const unsigned int *)&value;
			if (comp_pos_v == false)
				return position;
			Rva002F1DDCIter after = position;
			after.node = (Rva002F1DDCNode *)_STL::_Rb_global<bool>::_M_increment(
				(_STL::_Rb_tree_node_base *)after.node);
			if (after.node == m_header) {
				return rva002F0DD6(0, pos, value, pos);
			}
			if (*(const unsigned int *)&value < *(const unsigned int *)&after.node->_key) {
				if (pos->_right == 0)
					return rva002F0DD6(0, pos, value, pos);
				else
					return rva002F0DD6(after.node, after.node, value, 0);
			} else {
				Rva002F1DDCFindFn find = (Rva002F1DDCFindFn)&Rva002F1DDCTree::rva002F0E5E;
				return Rva002F1DDCIter(((this->*find)(value)).node);
			}
		}
	} else if (pos == m_header) {
		if (m_header->_right->_key < *(const unsigned int *)&value) {
			return rva002F0DD6(0, m_header->_right, value, pos);
		} else {
			Rva002F1DDCFindFn find = (Rva002F1DDCFindFn)&Rva002F1DDCTree::rva002F0E5E;
			return Rva002F1DDCIter(((this->*find)(value)).node);
		}
	} else {
		Rva002F1DDCIter before = position;
		before.node = (Rva002F1DDCNode *)_STL::_Rb_global<bool>::_M_decrement(
			(_STL::_Rb_tree_node_base *)before.node);
		bool comp_v_pos = *(const unsigned int *)&value < *(const unsigned int *)&pos->_key;
		if (comp_v_pos && before.node->_key < *(const unsigned int *)&value) {
			if (before.node->_right == 0)
				return rva002F0DD6(0, before.node, value, before.node);
			else
				return rva002F0DD6(pos, pos, value, 0);
		} else {
			Rva002F1DDCIter after = position;
			after.node = (Rva002F1DDCNode *)_STL::_Rb_global<bool>::_M_increment(
				(_STL::_Rb_tree_node_base *)after.node);
			bool comp_pos_v = !comp_v_pos;
			if (!comp_v_pos)
				comp_pos_v = pos->_key < *(const unsigned int *)&value;
			if (!comp_v_pos && comp_pos_v &&
				(after.node == m_header ||
				 *(const unsigned int *)&value < *(const unsigned int *)&after.node->_key)) {
				if (pos->_right == 0)
					return rva002F0DD6(0, pos, value, pos);
				else
					return rva002F0DD6(after.node, after.node, value, 0);
			} else {
				if (comp_v_pos == comp_pos_v)
					return position;
				else {
					Rva002F1DDCFindFn find = (Rva002F1DDCFindFn)&Rva002F1DDCTree::rva002F0E5E;
					return Rva002F1DDCIter(((this->*find)(value)).node);
				}
			}
		}
	}
}
