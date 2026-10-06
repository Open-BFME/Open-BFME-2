// cl: /MD
// stlport
// ?rva00396722@Rva00396722@@QAE_NPAX@Z @0x00396722 131B
// Contains check: +0x38 fast path, RB-tree at +0x8c via rowed _M_increment
// 0x00024250, vectors at +0x5c/+0x60 and +0x68/+0x6c. Caller at 0x002CCF9D
// passes [esi+0x74] with Module in ecx found via findModule.
#include <vector>
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

class Rva00396722 {
public:
	bool rva00396722(void *p);
private:
	char m_pad00[0x38];
	void *m_38;
	char m_pad3c[0x5c - 0x3c];
	_STL::vector<void *> m_vec5c;
	_STL::vector<void *> m_vec68;
	char m_pad74[0x8c - 0x74];
	_STL::_Rb_tree_node_base *m_header8c;
};

bool Rva00396722::rva00396722(void *p)
{
	if (p == m_38)
		return true;
	_STL::_Rb_tree_node_base *node = m_header8c->_M_left;
	while (node != m_header8c) {
		if (p == *(void **)((char *)node + 0x10))
			return true;
		node = _STL::_Rb_global<bool>::_M_increment(node);
	}
	for (unsigned i = 0; i < m_vec5c.size(); ++i) {
		if (p == m_vec5c[i])
			return true;
	}
	for (unsigned i = 0; i < m_vec68.size(); ++i) {
		if (p == m_vec68[i])
			return true;
	}
	return false;
}
