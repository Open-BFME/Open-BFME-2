// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
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
namespace _STL {
	struct _Rb_tree_node_base {};
	template <typename D> class _Rb_global {
	public:
		static _Rb_tree_node_base *_M_decrement(_Rb_tree_node_base *x);
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
	// Row 0x006012ED declares void return; retail leaves the result pointer in
	// eax so the caller addresses the new node as [eax]; declared here as
	// returning void** to reproduce that (central retype pending).
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
