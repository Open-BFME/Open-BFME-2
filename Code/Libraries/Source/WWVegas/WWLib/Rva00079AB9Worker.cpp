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

// The rowed 34-byte allocator uses STLport's actual _M_create_node name.
// Its 0x20 allocation and 0x10 value offset establish a 16-byte pair payload;
// the record's application meaning and original owning tree remain unresolved.
class Rva00079D14Tree;
struct Rva0007989CRecord { int word0, word1, word2; };
namespace _STL {
template<class A, class B> struct pair;
template<class T> struct _Select1st;
template<class T> struct less;
template<class T> class allocator;
template<class T> struct _Rb_tree_node;
template<class K, class V, class S, class C, class A> class _Rb_tree {
protected:
 _Rb_tree_node<V> *_M_create_node(const V &);
 friend class ::Rva00079D14Tree;
};
}
typedef _STL::pair<const int, Rva0007989CRecord> Rva0007989CValue;
typedef _STL::_Rb_tree<int, Rva0007989CValue, _STL::_Select1st<Rva0007989CValue>,
 _STL::less<int>, _STL::allocator<Rva0007989CValue> > Rva0007989CTree;

struct Rva00079D14Iter
{
	Rva00079D14Node *node;
	Rva00079D14Iter(Rva00079D14Node *p) : node(p) {}
};

class Rva00079D14Tree
{
public:
	Rva00079D14Iter rva00079AB9(Rva00079D14Node *hintNode,
		Rva00079D14Node *parent, const Rva00079D14Value &value,
		Rva00079D14Node *w);
private:
	Rva00079D14Node *m_header;
	int m_count;
};

Rva00079D14Iter Rva00079D14Tree::rva00079AB9(Rva00079D14Node *hintNode,
	Rva00079D14Node *parent, const Rva00079D14Value &value,
	Rva00079D14Node *w)
{
	Rva00079D14Node *z;
	if (parent == m_header || (w == 0 && (hintNode != 0 || *(const unsigned int *)&value < parent->_key))) {
		z = (Rva00079D14Node *)reinterpret_cast<Rva0007989CTree *>(this)->_M_create_node(reinterpret_cast<const Rva0007989CValue &>(value));
		parent->_left = z;
		if (parent == m_header) {
			m_header->_parent = z;
			m_header->_right = z;
		} else if (parent == m_header->_left) {
			m_header->_left = z;
		}
	} else {
		z = (Rva00079D14Node *)reinterpret_cast<Rva0007989CTree *>(this)->_M_create_node(reinterpret_cast<const Rva0007989CValue &>(value));
		parent->_right = z;
		if (parent == m_header->_right) {
			m_header->_right = z;
		}
	}
	z->_parent = parent;
	z->_left = 0;
	z->_right = 0;
	_STL::_Rb_global<bool>::_Rebalance((_STL::_Rb_tree_node_base *)z,
		(_STL::_Rb_tree_node_base *&)m_header->_parent);
	++m_count;
	return Rva00079D14Iter(z);
}
