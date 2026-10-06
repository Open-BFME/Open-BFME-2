// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva0018C2E7Copy@@YAPAFPAURva0018C2E7Node@@0PAF0H@Z @ 0x0018C2E7 39B unlock: tree-to-short copy via rowed _M_increment. Caller 0x0018C3C9 passes 5 args.
namespace _STL {
struct _Rb_tree_node_base {
	int m_color;
	_Rb_tree_node_base *m_parent;
	_Rb_tree_node_base *m_left;
	_Rb_tree_node_base *m_right;
};
template <class _Dummy> struct _Rb_global {
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *);
};
}
struct Rva0018C2E7Node {
	int m_00;
	void *m_04;
	void *m_08;
	void *m_0C;
	short m_10;
};
short *__cdecl Rva0018C2E7Copy(Rva0018C2E7Node *first, Rva0018C2E7Node *last, short *result, void *tag1, int tag2);
short *__cdecl Rva0018C2E7Copy(Rva0018C2E7Node *first, Rva0018C2E7Node *last, short *result, void *tag1, int tag2)
{
	(void)tag1;
	(void)tag2;
	for (; first != last;) {
		short v = first->m_10;
		*result = v;
		++result;
		first = (Rva0018C2E7Node *)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base *)first);
	}
	return result;
}
