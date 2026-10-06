// cl: /DNDEBUG /MD /EHsc
// ?rva00418D3C@Rva00418BFB@@QAE?AURva00418BFBPair@@ABURva00418BFBKey@@@Z @ 0x00418D3C 166B: tree insert_unique
// calling rowed 0x00418BB7 less plus rowed _M_decrement 0x000242C0 and rowed 0x00418C33 Minsert.
// Unblocks 0x00418DE2. Evidence: chain packet calls 0x00418C33 shape matches STL insert_unique.
struct Rva00418BFB;
namespace _STL {
	struct _Rb_tree_node_base {};
	template <typename D> class _Rb_global {
	public:
		static _Rb_tree_node_base *_M_decrement(_Rb_tree_node_base *x);
	};
}

struct Rva00418BFBKey {
	int lo;
	int hi;
};
struct Rva00418BFBNode {
	int _c0;
	Rva00418BFBNode *_parent;
	Rva00418BFBNode *_left;
	Rva00418BFBNode *_right;
	Rva00418BFBKey _key;
};
struct Rva00418BFBComp {
	bool operator()(const void *a, const void *b) const;
};
struct Rva00418BFBIter {
	Rva00418BFBNode *node;
};
struct Rva00418BFBPair {
	Rva00418BFBNode *first;
	bool second;
	Rva00418BFBPair(Rva00418BFBNode *f, bool s) : first(f), second(s) {}
	Rva00418BFBPair(Rva00418BFBIter it, bool s) : first(it.node), second(s) {}
};
struct Rva00418BFB {
	Rva00418BFBNode *_head;
	int _size;
	Rva00418BFBComp _comp;
	Rva00418BFBIter rva00418C33(Rva00418BFBNode *x, Rva00418BFBNode *y, const Rva00418BFBKey &v, Rva00418BFBNode *w);
	Rva00418BFBPair rva00418D3C(const Rva00418BFBKey &v);
};

Rva00418BFBPair Rva00418BFB::rva00418D3C(const Rva00418BFBKey &v)
{
	Rva00418BFBNode *header = _head;
	Rva00418BFBNode *x = header->_parent;
	Rva00418BFBNode *y = header;
	bool comp = true;
	while (x != 0) {
		y = x;
		comp = _comp((const void *)&v, (const void *)&x->_key);
		x = comp ? x->_left : x->_right;
	}
	Rva00418BFBNode *j = y;
	if (comp) {
		if (j == header->_left)
			return Rva00418BFBPair(rva00418C33(y, y, v, 0), true);
		j = (Rva00418BFBNode *)_STL::_Rb_global<bool>::_M_decrement((_STL::_Rb_tree_node_base *)y);
	}
	if (_comp((const void *)&j->_key, (const void *)&v))
		return Rva00418BFBPair(rva00418C33(x, y, v, 0), true);
	return Rva00418BFBPair(j, false);
}
