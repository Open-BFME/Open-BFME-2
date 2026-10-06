// cl: /DNDEBUG /MD /EHsc
// ?rva00418EEB@Rva00418EEB@@QAE_NPAXPBX@Z @ 0x00418EEB 146B: map lower_bound plus bit search
// calls rowed 0x00418BFB lower_bound and rowed 0x000242C0 decrement.
// Evidence: chain packet calls 0x00418BFB, head+8 begin check, 8-entry loop.
// The final check is spelled `if (!atBegin) { found; return true; } return false;`
// rather than `if (atBegin) return false; found;`: that orientation is what
// places the shared found block directly after the loop, matching retail's
// `jne`-to-false / fall-through-to-found tail layout.
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
struct Rva00418BFB {
	Rva00418BFBNode *_head;
	int _size;
	Rva00418BFBComp _comp;
	void *rva00418BFB(const void *key);
};
namespace _STL {
struct _Rb_tree_node_base {
	bool _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};
template <class Dummy> class _Rb_global {
public:
	static _Rb_tree_node_base *__cdecl _M_decrement(_Rb_tree_node_base *);
};
};
struct Rva00418EEB {
	int _c0;
	Rva00418BFB _map;
	unsigned _bits[8];
	bool rva00418EEB(void *outKey, const void *inKey);
};
bool Rva00418EEB::rva00418EEB(void *outKey, const void *inKey)
{
	Rva00418BFB *mp = &_map;
	Rva00418BFBNode *lb = (Rva00418BFBNode *)mp->rva00418BFB(inKey);
	const Rva00418BFBKey *in = (const Rva00418BFBKey *)inKey;
	Rva00418BFBNode *head = mp->_head;
	bool atBegin;
	if (lb != head->_left) {
		lb = (Rva00418BFBNode *)_STL::_Rb_global<bool>::_M_decrement((_STL::_Rb_tree_node_base *)lb);
		atBegin = false;
	} else
		atBegin = true;
	int hi = in->hi;
	if (hi < 0)
		goto check;
	if (!atBegin && lb->_key.hi >= 0) {
		((Rva00418BFBKey *)outKey)->lo = lb->_key.lo;
		((Rva00418BFBKey *)outKey)->hi = lb->_key.hi;
		return true;
	}
	{
		int i = (hi > 0) ? 0 : in->lo + 1;
		for (; i < 8; ++i) {
			if (_bits[(unsigned)i >> 5] & (1u << (i & 31))) {
				((Rva00418BFBKey *)outKey)->lo = i;
				((Rva00418BFBKey *)outKey)->hi = 0;
				return true;
			}
		}
	}
check:
	if (!atBegin) {
		((Rva00418BFBKey *)outKey)->lo = lb->_key.lo;
		((Rva00418BFBKey *)outKey)->hi = lb->_key.hi;
		return true;
	}
	return false;
}
