// cl: /EHs /MD
// stlport
//
// ?rva00079AB9@Rva00079D14Tree@@QAE?AURva00079D14Iter@@PAURva00079D14Node@@0ABVRva00079D14Value@@0@Z @0x00079AB9 136B.
// Spelled with the caller's view (Rva00079D14HintInsert.cpp) and a by-value iterator result:
// the hinted insert at 0x00079D14 passes its own hidden result slot straight through, and
// the worker returns that slot in eax (mov eax,[ebp+8] before the store), so the
// result is returned by value rather than through an explicit out pointer.
// The boundary is in reverse/ghidra_functions.csv. Target bytes at 0x00079AB9
// reproduce the rowed 0x00170BFF insertion-worker shape, with its node allocator
// call redirected to 0x0007989C. The target worker compares the value's first
// dword and links the new node; the owning class and value identity remain
// unknown, so these names describe the address and observed ABI only.
class Rva00079AB9Value;
class Rva00079D14Value;

struct Rva00079D14Node
{
	unsigned int _color;
	Rva00079D14Node *_parent;
	Rva00079D14Node *_left;
	Rva00079D14Node *_right;
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
};

struct Rva00079D14Iter
{
	Rva00079D14Node *node;
	Rva00079D14Iter(Rva00079D14Node *p) : node(p) {}
};

class Rva00079D14Tree
{
public:
	Rva00079D14Iter rva00079AB9(Rva00079D14Node *x,
		Rva00079D14Node *y, const Rva00079D14Value &value,
		Rva00079D14Node *w);
private:
	Rva00079D14Node *m_header;
	int m_count;
};

Rva00079D14Iter Rva00079D14Tree::rva00079AB9(Rva00079D14Node *x,
	Rva00079D14Node *y, const Rva00079D14Value &value,
	Rva00079D14Node *w)
{
	Rva00079D14Node *z;
	if (y == m_header || (w == 0 && (x != 0 || *(const unsigned int *)&value < y->_key))) {
		z = (Rva00079D14Node *)reinterpret_cast<Rva00079AB9Tree *>(this)->rva0007989C(reinterpret_cast<const Rva00079AB9Value &>(value));
		y->_left = z;
		if (y == m_header) {
			m_header->_parent = z;
			m_header->_right = z;
		} else if (y == m_header->_left) {
			m_header->_left = z;
		}
	} else {
		z = (Rva00079D14Node *)reinterpret_cast<Rva00079AB9Tree *>(this)->rva0007989C(reinterpret_cast<const Rva00079AB9Value &>(value));
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
	return Rva00079D14Iter(z);
}
