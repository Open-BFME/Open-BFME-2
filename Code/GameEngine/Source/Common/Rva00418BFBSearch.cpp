// cl: /DNDEBUG /MD /EHsc
// ?rva00418BFB@Rva00418BFB@@QAEPAXPBX@Z @ 0x00418BFB 56B: tree lower_bound search
// calling rowed 0x00418BB7 less over keys at +0x10, left at +8, right at +0xC.
// Evidence: chain packet calls 0x00418BB7, loop shape matches lower_bound.
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

// The empty comparator forwards the same two key pointers to the rowed
// signed-pair less function at 0x00418BB7; its this pointer is unused.
#pragma comment(linker, "/alternatename:??RRva00418BFBComp@@QBE_NPBX0@Z=?Rva00418BB7Less@@YG_NPBX0@Z")

struct Rva00418BFB {
	Rva00418BFBNode *_head;
	int _size;
	Rva00418BFBComp _comp;
	void *rva00418BFB(const void *key);
};
void *Rva00418BFB::rva00418BFB(const void *key)
{
	Rva00418BFBNode *ans = _head;
	Rva00418BFBNode *cur = _head->_parent;
	while (cur != 0) {
		const void *curKey = &cur->_key;
		if (!_comp(curKey, key)) {
			ans = cur;
			cur = cur->_left;
		} else {
			cur = cur->_right;
		}
	}
	return ans;
}
