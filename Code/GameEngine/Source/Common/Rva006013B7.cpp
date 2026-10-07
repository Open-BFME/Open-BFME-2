// cl: /O1 /Oy- /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva006013B7@Rva0060126D@@QAE?AURva006013B7Pair@@ABURva00600F9CElement@@@Z @0x006013B7 155B lane=chain
// Evidence: calls 0x006012ED just landed plus rowed CStrLess 0x006038D4 Decrement 0x000242C0; prev 0x0060137F next 0x0060146B same family; callers 0x0060145F 0x006014E3; unblocks 0x0060147B.
struct Rva00600F9CElement
{
	Rva00600F9CElement(const Rva00600F9CElement &that);
};
struct Rva006038D4Less
{
	bool operator()(const char *a, const char *b) const;
};
#pragma comment(linker, "/alternatename:??RRva006038D4Less@@QBE_NPBD0@Z=?Rva0006038D4CStrLess@@YG_NPBD0@Z")
struct Rva00600991;
namespace _STL {
struct _Rb_tree_node_base {};
template<class T> struct _Rb_tree_node {};
template<class T> struct _Identity {};
template<class T> struct less {};
template<class T> class allocator {};
template<class K, class V, class KeyOfValue, class Compare, class Alloc> class _Rb_tree {
    friend struct ::Rva00600991;
protected:
    _Rb_tree_node<V> *_M_create_node(const V &);
};
template<class D> class _Rb_global {
public:
    static _Rb_tree_node_base *_M_decrement(_Rb_tree_node_base *);
    static void _Rebalance(_Rb_tree_node_base *, _Rb_tree_node_base *&);
};
}
struct Rva0060126DNode {
	unsigned color;
	Rva0060126DNode *parent;
	Rva0060126DNode *left;
	Rva0060126DNode *right;
};
struct Rva006013B7Pair {
	Rva0060126DNode *first;
	bool second;
	Rva006013B7Pair(Rva0060126DNode *f, bool s) : first(f), second(s) {}
};
struct Rva0060126D {
	Rva0060126DNode *m_header;
	int m_count;
	Rva006038D4Less m_less;
	// Native helper returns the output pointer in EAX. Provider and caller agree.
	void **rva006012ED(void **result, void *x, void *y, const void *value, void *known);
	Rva006013B7Pair rva006013B7(const Rva00600F9CElement &v);
};
Rva006013B7Pair Rva0060126D::rva006013B7(const Rva00600F9CElement &v)
{
	Rva0060126DNode *y = m_header;
	Rva0060126DNode *x = m_header->parent;
	bool comp = true;
	while (x != 0) {
		y = x;
		comp = m_less(*(const char **)&v, *(const char **)((char *)x + 0x10));
		x = comp ? x->left : x->right;
	}
	Rva0060126DNode *j = y;
	if (comp) {
		if (j == m_header->left)
		{
			Rva0060126DNode *tmp;
			void **pres = rva006012ED((void **)&tmp, y, y, &v, 0);
			tmp = (Rva0060126DNode *)*pres;
			return Rva006013B7Pair(tmp, true);
		}
		j = (Rva0060126DNode *)_STL::_Rb_global<bool>::_M_decrement((_STL::_Rb_tree_node_base *)y);
	}
	if (m_less(*(const char **)((char *)j + 0x10), *(const char **)&v))
	{
		Rva0060126DNode *tmp;
		void **pres = rva006012ED((void **)&tmp, x, y, &v, 0);
		tmp = (Rva0060126DNode *)*pres;
		return Rva006013B7Pair(tmp, true);
	}
	return Rva006013B7Pair(j, false);
}

// Retail 0x00600991 (155B) and 0x00600854 (146B): strcmp-ordered
// one-word keys, 16-byte node header, 20-byte allocation, and pointer/bool
// insertion result. The application owner is unknown. Reconstructed from the
// matched 0x006013B7/0x006012ED sibling algorithm and each body's retail bytes.
// Allocation is the existing 0x004ABCC9 integer-word node provider, viewed
// through its established receiver ABI; no alternate allocator symbol added.
// The comparator bridge above is the existing byte-verified stdcall provider.
// /O1 /Oy- reproduces both routines and preserves the original sibling.
// Return type reconciles the former explicit-output placeholder at 0x600BC6.
struct Rva00600991Element { const char *key; };
struct Rva00600991Node {
	unsigned color;
	Rva00600991Node *parent;
	Rva00600991Node *left;
	Rva00600991Node *right;
};
struct Rva00600991Pair {
	Rva00600991Node *first;
	bool second;
	Rva00600991Pair(Rva00600991Node *f, bool s) : first(f), second(s) {}
};
struct Rva00600991 {
	Rva00600991Node *m_header;
	int m_count;
	Rva006038D4Less m_less;
	// Row 0x006012ED declares void return; retail leaves the result pointer in
	// eax so the caller addresses the new node as [eax]; declared here as
	// returning void** to reproduce that (central retype pending).
	void **rva00600854(void **result, void *x, void *y, const void *value, void *known);
	Rva00600991Pair rva00600991(const Rva00600991Element &v);
};
Rva00600991Pair Rva00600991::rva00600991(const Rva00600991Element &v)
{
	Rva00600991Node *y = m_header;
	Rva00600991Node *x = m_header->parent;
	bool comp = true;
	while (x != 0) {
		y = x;
		comp = m_less(*(const char **)&v, *(const char **)((char *)x + 0x10));
		x = comp ? x->left : x->right;
	}
	Rva00600991Node *j = y;
	if (comp) {
		if (j == m_header->left)
		{
			Rva00600991Node *tmp;
			void **pres = rva00600854((void **)&tmp, y, y, &v, 0);
			tmp = (Rva00600991Node *)*pres;
			return Rva00600991Pair(tmp, true);
		}
		j = (Rva00600991Node *)_STL::_Rb_global<bool>::_M_decrement((_STL::_Rb_tree_node_base *)y);
	}
	if (m_less(*(const char **)((char *)j + 0x10), *(const char **)&v))
	{
		Rva00600991Node *tmp;
		void **pres = rva00600854((void **)&tmp, x, y, &v, 0);
		tmp = (Rva00600991Node *)*pres;
		return Rva00600991Pair(tmp, true);
	}
	return Rva00600991Pair(j, false);
}

typedef _STL::_Rb_tree<int, int, _STL::_Identity<int>, _STL::less<int>, _STL::allocator<int> > RankTree;
void **Rva00600991::rva00600854(void **result, void *x, void *y, const void *value, void *known)
{
	Rva00600991Node *yn = (Rva00600991Node *)y;
	Rva00600991Node *node;
	if (yn != m_header && (known != 0 || (x == 0 && !m_less(*(const char **)value, *(const char **)((char *)yn + 0x10))))) {
		node = (Rva00600991Node *)((RankTree *)this)->_M_create_node(*(const int *)value);
		yn->right = node;
		Rva00600991Node *header = m_header;
		if (yn == header->right)
			header->right = node;
	} else {
		node = (Rva00600991Node *)((RankTree *)this)->_M_create_node(*(const int *)value);
		yn->left = node;
		Rva00600991Node *header = m_header;
		if (yn == header) {
			header->parent = node;
			m_header->right = node;
		} else if (yn == header->left) {
			header->left = node;
		}
	}
	node->left = 0;
	node->right = 0;
	node->parent = yn;
	_STL::_Rb_global<bool>::_Rebalance(
		reinterpret_cast<_STL::_Rb_tree_node_base *>(node),
		reinterpret_cast<_STL::_Rb_tree_node_base *&>(m_header->parent));
	++m_count;
	*result = node;
	return result;
}
