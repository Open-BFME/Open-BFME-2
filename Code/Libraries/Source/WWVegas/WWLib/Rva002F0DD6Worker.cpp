// cl: /EHs /MD
// stlport
//
// ?rva002F0DD6@Rva002F0DD6Tree@@QAEXPAPAXPAURva002F0DD6Node@@1ABVRva002F0DD6Value@@1@Z @0x002F0DD6 136B.
// The boundary is in reverse/ghidra_functions.csv. Target bytes at 0x002F0DD6
// reproduce the rowed 0x00170BFF insertion-worker shape, with its node allocator
// call redirected to 0x002EF25B. The target worker compares the value's first
// dword and links the new node; the owning class and value identity remain
// unknown, so these names describe the address and observed ABI only.
class Rva002F0DD6Value;

struct Rva002F0DD6Node
{
	unsigned int _color;
	Rva002F0DD6Node *_parent;
	Rva002F0DD6Node *_left;
	Rva002F0DD6Node *_right;
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

class Rva002F0DD6Tree
{
public:
	void *rva002EF25B(const Rva002F0DD6Value &value);
	void rva002F0DD6(void **out, Rva002F0DD6Node *x,
		Rva002F0DD6Node *y, const Rva002F0DD6Value &value,
		Rva002F0DD6Node *w);
private:
	Rva002F0DD6Node *m_header;
	int m_count;
};

void Rva002F0DD6Tree::rva002F0DD6(void **out, Rva002F0DD6Node *x,
	Rva002F0DD6Node *y, const Rva002F0DD6Value &value,
	Rva002F0DD6Node *w)
{
	Rva002F0DD6Node *z;
	if (y == m_header || (w == 0 && (x != 0 || *(const unsigned int *)&value < y->_key))) {
		z = (Rva002F0DD6Node *)rva002EF25B(value);
		y->_left = z;
		if (y == m_header) {
			m_header->_parent = z;
			m_header->_right = z;
		} else if (y == m_header->_left) {
			m_header->_left = z;
		}
	} else {
		z = (Rva002F0DD6Node *)rva002EF25B(value);
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
