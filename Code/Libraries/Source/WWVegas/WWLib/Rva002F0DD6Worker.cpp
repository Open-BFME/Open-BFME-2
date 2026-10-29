// cl: /EHs /MD
// stlport
//
// ?rva002F0DD6@Rva002F1DDCTree@@QAE?AURva002F1DDCIter@@PAURva002F1DDCNode@@0ABVRva002F1DDCValue@@0@Z @0x002F0DD6 136B.
// Spelled with the caller's view (Rva002F1DDCHintInsert.cpp) and a by-value iterator result:
// the hinted insert at 0x002F1DDC passes its own hidden result slot straight through, and
// the worker returns that slot in eax (mov eax,[ebp+8] before the store), so the
// result is returned by value rather than through an explicit out pointer.
// The boundary is in reverse/ghidra_functions.csv. Target bytes at 0x002F0DD6
// reproduce the rowed 0x00170BFF insertion-worker shape, with its node allocator
// call redirected to 0x002EF25B. The target worker compares the value's first
// dword and links the new node; the owning class and value identity remain
// unknown, so these names describe the address and observed ABI only.
class Rva002F0DD6Value;
class Rva002F1DDCValue;

struct Rva002F1DDCNode
{
	unsigned int _color;
	Rva002F1DDCNode *_parent;
	Rva002F1DDCNode *_left;
	Rva002F1DDCNode *_right;
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
};

struct Rva002F1DDCIter
{
	Rva002F1DDCNode *node;
	Rva002F1DDCIter(Rva002F1DDCNode *treeNode) : node(treeNode) {}
};

struct Rva002F1DDCOut;
class Rva002F1DDCTree
{
public:
	Rva002F1DDCIter rva002F0DD6(Rva002F1DDCNode *x, Rva002F1DDCNode *y, const Rva002F1DDCValue &value, Rva002F1DDCNode *w);
	Rva002F1DDCOut rva002F0E5E(const Rva002F1DDCValue &value);
	Rva002F1DDCIter rva002F1DDC(Rva002F1DDCIter position, const Rva002F1DDCValue &value);
private:
	Rva002F1DDCNode *m_header; // +0x00
	unsigned int m_count; // +0x04
};

Rva002F1DDCIter Rva002F1DDCTree::rva002F0DD6(Rva002F1DDCNode *x,
	Rva002F1DDCNode *parent, const Rva002F1DDCValue &value,
	Rva002F1DDCNode *forceRight)
{
	Rva002F1DDCNode *newNode;
	if (parent == m_header || (forceRight == 0 && (x != 0 || *(const unsigned int *)&value < parent->_key))) {
		newNode = (Rva002F1DDCNode *)reinterpret_cast<Rva002F0DD6Tree *>(this)->rva002EF25B(reinterpret_cast<const Rva002F0DD6Value &>(value));
		parent->_left = newNode;
		if (parent == m_header) {
			m_header->_parent = newNode;
			m_header->_right = newNode;
		} else if (parent == m_header->_left) {
			m_header->_left = newNode;
		}
	} else {
		newNode = (Rva002F1DDCNode *)reinterpret_cast<Rva002F0DD6Tree *>(this)->rva002EF25B(reinterpret_cast<const Rva002F0DD6Value &>(value));
		parent->_right = newNode;
		if (parent == m_header->_right) {
			m_header->_right = newNode;
		}
	}
	newNode->_parent = parent;
	newNode->_left = 0;
	newNode->_right = 0;
	_STL::_Rb_global<bool>::_Rebalance((_STL::_Rb_tree_node_base *)newNode,
		(_STL::_Rb_tree_node_base *&)m_header->_parent);
	++m_count;
	return Rva002F1DDCIter(newNode);
}
