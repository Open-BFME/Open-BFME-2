// cl: /MD
// ?rva004FF5B7@Rva004FF5B7@@QAE?AU Rva004FF5B7Iter@@H@Z @0x004FF5B7 60B: linear scan via rowed _M_increment 0x00024250 for node+0x14 == key, returns iterator via hidden out, miss returns begin. Evidence: unlock lane ret 8 thiscall out-plus-int, header at +0x10 leftmost at +8, callers 0x0059BC97 0x0059DA96.
namespace _STL {
struct _Rb_tree_node_base
{
	bool _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};
template <class D> class _Rb_global
{
public:
	static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *);
};
}

struct Rva004FF5B7Node : public _STL::_Rb_tree_node_base
{
	int m_10;
	int m_14;
};

struct Rva004FF5B7Iter
{
	Rva004FF5B7Node *m_ptr;
};

class Rva004FF5B7
{
public:
	Rva004FF5B7Iter rva004FF5B7(int key);
private:
	char m_pad[0x10];
	_STL::_Rb_tree_node_base *m_header;
};

Rva004FF5B7Iter Rva004FF5B7::rva004FF5B7(int key)
{
	_STL::_Rb_tree_node_base *cur = m_header->_M_left;
	if (cur == m_header)
		goto miss;
	do {
		if (((Rva004FF5B7Node *)cur)->m_14 == key)
			return *(Rva004FF5B7Iter *)&cur;
		cur = _STL::_Rb_global<bool>::_M_increment(cur);
	} while (cur != m_header);
miss:
	Rva004FF5B7Iter out;
	out.m_ptr = (Rva004FF5B7Node *)m_header->_M_left;
	return out;
}
