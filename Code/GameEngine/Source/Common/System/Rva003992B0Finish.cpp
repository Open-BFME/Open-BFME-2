// cl: /DNDEBUG /MD /EHsc
// ?rva003992B0@Rva0039834C@@QAEPAURvaInsertOut@@PAU2@PBURva0039627D@@@Z @0x003992B0 134B
//
// Finish draft for the banked near miss reverse/attempts/0x003992b0.cpp.
//
// The out-of-line worker Rva0039834C::rva0039834C (0x0039834C, 136B, the
// sibling of Code/GameEngine/Source/Common/System/Rva0039834CInsert.cpp) is
// STLport's _M_insert: it returns an `iterator` (a non-trivial class) by
// value, so retail passes the hidden return slot as its first argument and the
// caller reads the inserted node straight back out of that slot with
// `mov ecx,[eax]; mov eax,[ebp+0x8]; mov [eax],ecx`.
//
// The rowed reconstruction of the worker spells that hidden slot as an
// explicit `RvaNode0039834C *&out` and returns void, which reproduces the
// worker's 136 bytes but makes a plain call reload the value-parameter slot
// (`mov ecx,[ebp+0xc]`) instead. Calling the same rowed symbol through a
// member-function pointer recast to the iterator-returning ABI restores the
// hidden-return call at the call site while still naming the rowed void symbol
// for the REL32 relocation; the compiler folds the constant pointer to a direct
// call. This is the same hidden-pointer ABI, only spelled so the optimizer
// keeps it.
struct Rva0039627D {
	int m_key;
	unsigned char m_body[12];
};
struct RvaNode0039834C {
	int _c0;
	RvaNode0039834C *_parent;
	RvaNode0039834C *_left;
	RvaNode0039834C *_right;
	int _key10;
	unsigned char _pad14[12];
};
namespace _STL {
struct _Rb_tree_node_base {};
template <typename D> class _Rb_global {
public:
	static void _Rebalance(_Rb_tree_node_base *x, _Rb_tree_node_base *&root);
	static _Rb_tree_node_base *_M_decrement(_Rb_tree_node_base *x);
};
}
struct RvaInsertOut {
	RvaNode0039834C *node;
	bool inserted;
};
// Non-trivial class returned by value: MSVC hands it back through a hidden
// pointer, which is the ABI the worker's explicit out reference already
// matches.
struct Rva0039834CIter {
	RvaNode0039834C *m_node;
	Rva0039834CIter(RvaNode0039834C *node) : m_node(node) {}
};
struct Rva0039834C {
	RvaNode0039834C *m_root;
	unsigned m_count;
	void rva0039834C(RvaNode0039834C *&out, RvaNode0039834C *a, RvaNode0039834C *b, const Rva0039627D *v, RvaNode0039834C *c);
	RvaInsertOut *rva003992B0(RvaInsertOut *out, const Rva0039627D *v);
};
typedef Rva0039834CIter (Rva0039834C::*Rva0039834CIterFn)(RvaNode0039834C *, RvaNode0039834C *, const Rva0039627D *, RvaNode0039834C *);

RvaInsertOut *Rva0039834C::rva003992B0(RvaInsertOut *out, const Rva0039627D *v)
{
	RvaNode0039834C *header = m_root;
	RvaNode0039834C *x = header->_parent;
	RvaNode0039834C *y = header;
	bool comp = true;
	if (x != 0) {
		do {
			y = x;
			comp = v->m_key < x->_key10;
			x = comp ? x->_left : x->_right;
		} while (x != 0);
	}
	RvaNode0039834C *j = y;
	Rva0039834CIterFn insert = (Rva0039834CIterFn)&Rva0039834C::rva0039834C;
	if (comp) {
		if (y == header->_left) {
			out->node = (this->*insert)(y, y, v, 0).m_node;
			out->inserted = true;
			return out;
		}
		j = (RvaNode0039834C *)_STL::_Rb_global<bool>::_M_decrement((_STL::_Rb_tree_node_base *)j);
	}
	if (j->_key10 < v->m_key) {
		out->node = (this->*insert)(x, y, v, 0).m_node;
		out->inserted = true;
		return out;
	}
	out->node = j;
	out->inserted = false;
	return out;
}
