// cl: /O1 /EHs /MD
// stlport
//
// ?rva00079AB9@Rva00079AB9Tree@@QAEXPAPAXPAURva00079AB9Node@@1ABVRva00079AB9Value@@1@Z @0x00079AB9 136B.
// The boundary is in reverse/ghidra_functions.csv. Target bytes at 0x00079AB9
// reproduce the rowed 0x00170BFF insertion-worker shape, with its node allocator
// call redirected to 0x0007989C. The target worker compares the value's first
// dword and links the new node; the owning class and value identity remain
// unknown, so these names describe the address and observed ABI only.
class Rva00079AB9Value;

struct Rva00079AB9Node
{
	unsigned int _color;
	Rva00079AB9Node *_parent;
	Rva00079AB9Node *_left;
	Rva00079AB9Node *_right;
	unsigned int _key;
};

namespace _STL
{
struct _Rb_tree_node_base;
template <class _D> class _Rb_global
{
public:
	static void _Rebalance(_Rb_tree_node_base *__x, _Rb_tree_node_base *&__root);
};
}

class Rva00079AB9Tree
{
public:
	void *rva0007989C(const Rva00079AB9Value &value);
	void rva00079AB9(void **out, Rva00079AB9Node *x,
		Rva00079AB9Node *y, const Rva00079AB9Value &value,
		Rva00079AB9Node *w);
private:
	Rva00079AB9Node *m_header;
	int m_count;
};

void Rva00079AB9Tree::rva00079AB9(void **out, Rva00079AB9Node *x,
	Rva00079AB9Node *y, const Rva00079AB9Value &value,
	Rva00079AB9Node *w)
{
	Rva00079AB9Node *z;
	if (y == m_header || (w == 0 && (x != 0 || *(const unsigned int *)&value < y->_key))) {
		z = (Rva00079AB9Node *)rva0007989C(value);
		y->_left = z;
		if (y == m_header) {
			m_header->_parent = z;
			m_header->_right = z;
		} else if (y == m_header->_left) {
			m_header->_left = z;
		}
	} else {
		z = (Rva00079AB9Node *)rva0007989C(value);
		y->_right = z;
		if (y == m_header->_right) {
			m_header->_right = z;
		}
	}
	z->_parent = y;
	z->_left = 0;
	z->_right = 0;
	_STL::_Rb_global<bool>::_Rebalance((_STL::_Rb_tree_node_base *)z,
		(_STL::_Rb_tree_node_base *&)m_header->_parent);
	++m_count;
	*out = z;
}
