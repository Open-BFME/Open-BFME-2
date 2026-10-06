// cl: /MD
// stlport
// ?rva003962E7@Rva003962E7@@QAE_NHH@Z @0x003962E7 42B
// Tree walk at +0xa0 via header left chain, value at node+0x10 vs key,
// increment via rowed 0x00024250, mismatch returns true, end returns false.
// Evidence: ret 8 thiscall, push esi, [ecx+0xa0] header, [esi+8] first,
// callers 2x in 0x00396F2C, callees rowed.
namespace _STL {
struct _Rb_tree_node_base {
	bool _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};
template <class D> class _Rb_global {
public:
	static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *);
};
}

class Rva003962E7 {
public:
	bool rva003962E7(int key, int dummy);
private:
	char m_pad00[0xa0];
	_STL::_Rb_tree_node_base *m_headerA0;
};

bool Rva003962E7::rva003962E7(int key, int dummy)
{
	_STL::_Rb_tree_node_base *header = m_headerA0;
	_STL::_Rb_tree_node_base *node = header->_M_left;
	while (node != header) {
		if (*(int *)((char *)node + 0x10) != key)
			return true;
		node = _STL::_Rb_global<bool>::_M_increment(node);
	}
	return false;
}
