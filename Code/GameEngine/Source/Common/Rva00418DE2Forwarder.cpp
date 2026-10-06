// cl: /DNDEBUG /MD /EHsc
// ?rva00418DE2@Rva00418DE2@@QAE?AURva00418BFBPair@@ABURva00418BFBKey@@@Z @ 0x00418DE2 35B: map insert forwarder
// calling rowed 0x00418D3C insert_unique. Unblocks 0x00418F7D.
// Evidence: chain packet calls 0x00418D3C with same this and value.
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
};
struct Rva00418BFB {
	Rva00418BFBNode *_head;
	int _size;
	Rva00418BFBComp _comp;
	Rva00418BFBIter rva00418C33(Rva00418BFBNode *x, Rva00418BFBNode *y, const Rva00418BFBKey &v, Rva00418BFBNode *w);
	Rva00418BFBPair rva00418D3C(const Rva00418BFBKey &v);
};
struct Rva00418DE2 {
	Rva00418BFB m_tree;
	Rva00418BFBPair rva00418DE2(const Rva00418BFBKey &v);
};

Rva00418BFBPair Rva00418DE2::rva00418DE2(const Rva00418BFBKey &v)
{
	Rva00418BFBPair tmp = m_tree.rva00418D3C(v);
	return Rva00418BFBPair(tmp.first, tmp.second);
}
