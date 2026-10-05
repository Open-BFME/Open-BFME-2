// cl: /O1 /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
//
// ?rva002F0E5E@Rva002F1DDCTree@@QAE?AURva002F1DDCOut@@ABVRva002F1DDCValue@@@Z @0x002F0E5E 134B.
// This target-inventory body is the STLport insert_unique(value) sibling of
// Rva0043B2E2::rva0043B429 at 0x0043B429. The caller at 0x002F1DDC reaches it
// when the hint cannot prove a neighboring slot. It compares the first
// unsigned dword, returns an 8-byte iterator/flag record, and inserts through
// the rowed worker at 0x002F0DD6. The owning container and full value layout
// remain unknown; names are address-derived.
#include <map>

class Rva002F1DDCValue;

struct Rva002F1DDCNode
{
	unsigned int _color;
	Rva002F1DDCNode *_parent;
	Rva002F1DDCNode *_left;
	Rva002F1DDCNode *_right;
	unsigned int _key;
};

struct Rva002F1DDCIter
{
	::_STL::_Rb_tree_node_base *_M_node;
	Rva002F1DDCIter &operator--()
	{
		_M_node = _STL::_Rb_global<bool>::_M_decrement(_M_node);
		return *this;
	}
};

struct Rva002F1DDCOut
{
	Rva002F1DDCNode *node;
	bool inserted;
	Rva002F1DDCOut(const Rva002F1DDCIter &iter, bool flag)
		: node((Rva002F1DDCNode *)iter._M_node), inserted(flag) {}
};

class Rva002F1DDCTree
{
	Rva002F1DDCNode *m_header;
	unsigned int m_count;
public:
	Rva002F1DDCIter rva002F0DD6(Rva002F1DDCNode *x,
		Rva002F1DDCNode *y, const Rva002F1DDCValue &value,
		Rva002F1DDCNode *w);
	Rva002F1DDCOut rva002F0E5E(const Rva002F1DDCValue &value);
};

Rva002F1DDCOut Rva002F1DDCTree::rva002F0E5E(
	const Rva002F1DDCValue &value)
{
	Rva002F1DDCNode *y = m_header;
	Rva002F1DDCNode *x = m_header->_parent;
	bool comp = true;
	while (x != 0) {
		y = x;
		comp = _STL::less<unsigned int>()(
			*(const unsigned int *)&value, x->_key);
		x = comp ? x->_left : x->_right;
	}
	Rva002F1DDCIter j;
	j._M_node = (::_STL::_Rb_tree_node_base *)y;
	if (comp && y == m_header->_left)
		return Rva002F1DDCOut(rva002F0DD6(y, y, value, 0), true);
	if (comp)
		--j;
	if (_STL::less<unsigned int>()(
		((Rva002F1DDCNode *)j._M_node)->_key,
		*(const unsigned int *)&value))
		return Rva002F1DDCOut(rva002F0DD6(x, y, value, 0), true);
	return Rva002F1DDCOut(j, false);
}
