// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
//
// ?rva00079B41@Rva00079D14Tree@@QAE?AURva00079D14Out@@ABVRva00079D14Value@@@Z @0x00079B41 134B.
// This target-inventory body is the STLport insert_unique(value) sibling of
// Rva0043B2E2::rva0043B429 at 0x0043B429. The caller at 0x00079D14 reaches it
// when the hint cannot prove a neighboring slot. It compares the first
// unsigned dword, returns an 8-byte iterator/flag record, and inserts through
// the rowed worker at 0x00079AB9. The owning container and full value layout
// remain unknown; names are address-derived.
#include <map>

class Rva00079D14Value;

struct Rva00079D14Node
{
	unsigned int _color;
	Rva00079D14Node *_parent;
	Rva00079D14Node *_left;
	Rva00079D14Node *_right;
	unsigned int _key;
};

struct Rva00079D14Iter
{
	::_STL::_Rb_tree_node_base *_M_node;
	Rva00079D14Iter &operator--()
	{
		_M_node = _STL::_Rb_global<bool>::_M_decrement(_M_node);
		return *this;
	}
};

struct Rva00079D14Out
{
	Rva00079D14Node *node;
	bool inserted;
	Rva00079D14Out(const Rva00079D14Iter &iter, bool flag)
		: node((Rva00079D14Node *)iter._M_node), inserted(flag) {}
};

class Rva00079D14Tree
{
	Rva00079D14Node *m_header;
	unsigned int m_count;
public:
	Rva00079D14Iter rva00079AB9(Rva00079D14Node *x,
		Rva00079D14Node *y, const Rva00079D14Value &value,
		Rva00079D14Node *w);
	Rva00079D14Out rva00079B41(const Rva00079D14Value &value);
};

Rva00079D14Out Rva00079D14Tree::rva00079B41(
	const Rva00079D14Value &value)
{
	Rva00079D14Node *y = m_header;
	Rva00079D14Node *x = m_header->_parent;
	bool comp = true;
	while (x != 0) {
		y = x;
		comp = _STL::less<unsigned int>()(
			*(const unsigned int *)&value, x->_key);
		x = comp ? x->_left : x->_right;
	}
	Rva00079D14Iter j;
	j._M_node = (::_STL::_Rb_tree_node_base *)y;
	if (comp && y == m_header->_left)
		return Rva00079D14Out(rva00079AB9(y, y, value, 0), true);
	if (comp)
		--j;
	if (_STL::less<unsigned int>()(
		((Rva00079D14Node *)j._M_node)->_key,
		*(const unsigned int *)&value))
		return Rva00079D14Out(rva00079AB9(x, y, value, 0), true);
	return Rva00079D14Out(j, false);
}
