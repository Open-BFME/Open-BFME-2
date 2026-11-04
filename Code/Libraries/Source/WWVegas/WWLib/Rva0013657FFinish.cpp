// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ?rva0013657F@Rva001364F7@@QAEPAURvaOut13657F@@PAU2@PBUTreeKey00242F5E@@@Z @0x0013657F 134B
//
// Finish draft for the banked near miss reverse/attempts/0x0013657f.cpp.
// Same hidden-return wall as the sibling landed at 0x003992B0 (see
// Code/GameEngine/Source/Common/System/Rva003992B0Finish.cpp): the rowed
// tree worker 0x001364F7 spells the iterator return slot as an explicit
// `RvaNode1364F7 *&out` and returns void, so a plain call reloads the value
// parameter instead of reading the inserted node straight back out of the
// hidden slot. Calling the same rowed symbol through a member-function pointer
// recast to the iterator-returning ABI restores the hidden-return call at the
// call site while still naming the rowed void symbol for the REL32 relocation;
// the compiler folds the constant pointer to a direct call.
#include <map>
#include "TreeKey00242F5E.h"
struct RvaNode1364F7 {
	int _c0;
	RvaNode1364F7 *_parent;
	RvaNode1364F7 *_left;
	RvaNode1364F7 *_right;
	TreeKey00242F5E _key;
};
struct RvaOut13657F {
	RvaNode1364F7 *node;
	bool inserted;
};
// Non-trivial class returned by value: MSVC hands it back through a hidden
// pointer, which is the ABI the worker's explicit out reference already
// matches.
struct Rva001364F7Iter {
	RvaNode1364F7 *m_node;
	Rva001364F7Iter(RvaNode1364F7 *node) : m_node(node) {}
};
struct Rva001364F7
{
public:
	Rva001364F7Iter rva001364F7(RvaNode1364F7 *left, RvaNode1364F7 *parent, const TreeKey00242F5E *key, RvaNode1364F7 *right);
	RvaOut13657F *rva0013657F(RvaOut13657F *out, const TreeKey00242F5E *v);
	Rva001364F7Iter rva00136642(Rva001364F7Iter position, const TreeKey00242F5E &value);
	RvaNode1364F7 *m_root; // +0x00
	unsigned m_count; // +0x04
};
typedef Rva001364F7Iter (Rva001364F7::*Rva001364F7IterFn)(RvaNode1364F7 *, RvaNode1364F7 *, const TreeKey00242F5E *, RvaNode1364F7 *);

RvaOut13657F *Rva001364F7::rva0013657F(RvaOut13657F *out, const TreeKey00242F5E *v)
{
	RvaNode1364F7 *header = m_root;
	RvaNode1364F7 *x = header->_parent;
	RvaNode1364F7 *y = header;
	bool comp = true;
	while (x != 0) {
		y = x;
		comp = v->field00 < x->_key.field00;
		x = comp ? x->_left : x->_right;
	}
	RvaNode1364F7 *j = y;
	Rva001364F7IterFn insert = (Rva001364F7IterFn)&Rva001364F7::rva001364F7;
	if (comp) {
		if (y == header->_left) {
			out->node = (((Rva001364F7 *)this)->*insert)(y, y, v, 0).m_node;
			out->inserted = true;
			return out;
		}
		j = (RvaNode1364F7 *)_STL::_Rb_global<bool>::_M_decrement((_STL::_Rb_tree_node_base *)j);
	}
	if (j->_key.field00 < v->field00) {
		out->node = (((Rva001364F7 *)this)->*insert)(x, y, v, 0).m_node;
		out->inserted = true;
		return out;
	}
	out->node = j;
	out->inserted = false;
	return out;
}
