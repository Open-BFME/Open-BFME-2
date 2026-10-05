// cl: /O1 /MD
namespace _STL
{
typedef bool _Rb_tree_Color_type;
struct _Rb_tree_node_base
{
	_Rb_tree_Color_type _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};
template <class Dummy> class _Rb_global
{
public:
	static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *);
};
}
struct Rva005E4E1BNode
{
	_STL::_Rb_tree_node_base m_base;
	int m_key10;
};
struct Rva005E4E1BHeader
{
	char m_00[8];
	Rva005E4E1BNode *m_first08;
};
class Rva005F2278
{
public:
	bool rva005F2278(int v) const;
};
class Rva005E4DAF
{
public:
	void rva005E4DAF(int v);
};
class Rva005E4E1B
{
public:
	void rva005E4E1B();
private:
	char m_00[0x14];
	Rva005F2278 *m_14;
	char m_pad18[0x1C - 0x18];
	Rva005E4E1BHeader *m_1C;
};
void Rva005E4E1B::rva005E4E1B()
{
	Rva005E4E1BHeader *end = m_1C;
	Rva005E4E1BNode *it = end->m_first08;
	if (it == (Rva005E4E1BNode *)end)
		return;
	do {
		int k = it->m_key10;
		if (m_14->rva005F2278(k))
			((Rva005E4DAF *)this)->rva005E4DAF(k);
		it = (Rva005E4E1BNode *)&*_STL::_Rb_global<bool>::_M_increment(&it->m_base);
	} while (it != (Rva005E4E1BNode *)end);
}
