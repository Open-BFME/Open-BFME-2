// cl: /Ireference/shims/bfmelist /O1 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?_M_erase@Rva0018C262@@QAEXPAURva0018C262Node@@@Z @ 0x0018C262 45B unlock: recursive node free via rowed _free. Caller 0x0018C316 passes node+4.
#include <stdlib.h>
struct Rva0018C262Node {
	int m_00;
	int m_04;
	Rva0018C262Node *m_08;
	Rva0018C262Node *m_0C;
	unsigned short m_10;
};
struct Rva0018C262Head {
	int m_00;
	Rva0018C262Node *m_04;
	Rva0018C262Head *m_08;
	Rva0018C262Head *m_0C;
};
namespace _STL { void __cdecl free(void *block); }
// ?Rva0018C262HeaderOwner::~Rva0018C262HeaderOwner present-unmatched
struct Rva0018C262HeaderOwner {
	Rva0018C262Head *m_head;
	inline ~Rva0018C262HeaderOwner() {
		if (m_head)
			_STL::free(m_head);
	}
};
class Rva0018C262 : public Rva0018C262HeaderOwner {
public:
	__declspec(noinline) ~Rva0018C262();
	void _M_erase(Rva0018C262Node *node);
	void clear();
	Rva0018C262Node *rva0018C28F(const unsigned short *key);
	Rva0018C262Node *&rva0018C33F(Rva0018C262Node *&out, Rva0018C262Node *insertionPosition, Rva0018C262Node *insertionParent, const unsigned short *nodeValue, Rva0018C262Node *forceRight);
	int m_size;
};
namespace _STL {
template <class T> class allocator {
public:
	static char *allocate(unsigned int n, const void *hint);
};
struct _Rb_tree_node_base {};
template <typename D> class _Rb_global {
public:
	static void _Rebalance(_Rb_tree_node_base *x, _Rb_tree_node_base *&root);
	static _Rb_tree_node_base *_M_decrement(_Rb_tree_node_base *x);
};
}
void Rva0018C262::_M_erase(Rva0018C262Node *node)
{
	if (!node)
		return;
	do {
		_M_erase(node->m_0C);
		Rva0018C262Node *next = node->m_08;
		free(node);
		node = next;
	} while (node);
}
void Rva0018C262::clear()
{
	if (m_size == 0)
		return;
	_M_erase(m_head->m_04);
	m_head->m_08 = m_head;
	m_head->m_04 = 0;
	m_head->m_0C = m_head;
	m_size = 0;
}
Rva0018C262Node *Rva0018C262::rva0018C28F(const unsigned short *key)
{
	char *mem = _STL::allocator<char>::allocate(0x14, 0);
	unsigned short *dst = (unsigned short *)(mem + 0x10);
	if (dst)
		*dst = *key;
	return (Rva0018C262Node *)mem;
}
Rva0018C262Node *&Rva0018C262::rva0018C33F(Rva0018C262Node *&out, Rva0018C262Node *insertionPosition, Rva0018C262Node *insertionParent, const unsigned short *nodeValue, Rva0018C262Node *forceRight)
{
	Rva0018C262Node *node;
	if (insertionParent != (Rva0018C262Node *)m_head && (forceRight != 0 || (insertionPosition == 0 && (short)*nodeValue >= (short)insertionParent->m_10))) {
		node = rva0018C28F(nodeValue);
		insertionParent->m_0C = node;
		Rva0018C262Head *root = m_head;
		if (insertionParent == (Rva0018C262Node *)root->m_0C)
			root->m_0C = (Rva0018C262Head *)node;
	} else {
		node = rva0018C28F(nodeValue);
		insertionParent->m_08 = node;
		Rva0018C262Head *root = m_head;
		if (insertionParent == (Rva0018C262Node *)root) {
			root->m_04 = node;
			m_head->m_0C = (Rva0018C262Head *)node;
		} else if (insertionParent == (Rva0018C262Node *)root->m_08) {
			root->m_08 = (Rva0018C262Head *)node;
		}
	}
	node->m_08 = 0;
	node->m_0C = 0;
	node->m_04 = (int)insertionParent;
	_STL::_Rb_global<bool>::_Rebalance((_STL::_Rb_tree_node_base *)node, (_STL::_Rb_tree_node_base *&)m_head->m_04);
	++m_size;
	out = node;
	return out;
}
// Target 0x0018C3E6..0x0018C41D: clear the same tree, then release its
// base-owned header through 0x00030830. The C++ allocator declaration preserves
// the target unwind transition; node erasure above retains its C declaration.
// Header ownership follows STLport _Rb_tree_base; target application name is
// still unknown. No change to the established header/count offsets 0/4.
Rva0018C262::~Rva0018C262()
{
	clear();
}

// Native 0x0018C4A9..0x0018C533 compares signed short keys at node+0x10,
// walks the same header links and calls the rowed insertion worker above.
// Its caller 0x0018C6D5 supplies an eight-byte node/bool result packet.
// The worker returns the result-slot address in EAX; the existing void
// declaration discarded that independently observed part of its ABI.
// The algorithm follows matched Rva004D1C81::rva0046ABA6. Application
// identity remains unknown. Returning the node/bool packet reproduces
// retail's hidden result slot and returned slot address without a raw pin.
struct Rva0018C4A9Result {
	Rva0018C262Node *first;
	bool second;
	Rva0018C4A9Result(Rva0018C262Node *node, bool inserted);
};
// ?Rva0018C4A9Result::Rva0018C4A9Result present-unmatched
inline Rva0018C4A9Result::Rva0018C4A9Result(Rva0018C262Node *node, bool inserted) : first(node), second(inserted) {}
class Rva0018C4A9 {
	Rva0018C262Head *m_head;
	unsigned int m_size;
public:
	Rva0018C4A9Result insert_unique(short *key);
};
Rva0018C4A9Result Rva0018C4A9::insert_unique(short *key)
{
	Rva0018C262Head *header = m_head;
	Rva0018C262Node *currentNode = header->m_04;
	Rva0018C262Node *parentNode = (Rva0018C262Node *)header;
	bool comp = true;
	while (currentNode != 0) {
		parentNode = currentNode;
		comp = *key < (short)currentNode->m_10;
		currentNode = comp ? currentNode->m_08 : currentNode->m_0C;
	}
	Rva0018C262Node *j = parentNode;
	if (comp) {
		if (j == (Rva0018C262Node *)header->m_08) {
			Rva0018C262Node *node;
			return Rva0018C4A9Result(((Rva0018C262 *)this)->rva0018C33F(node, parentNode, parentNode, (const unsigned short *)key, 0), true);
		}
		j = (Rva0018C262Node *)_STL::_Rb_global<bool>::_M_decrement((_STL::_Rb_tree_node_base *)parentNode);
	}
	if ((short)j->m_10 < *key) {
		Rva0018C262Node *node;
		return Rva0018C4A9Result(((Rva0018C262 *)this)->rva0018C33F(node, currentNode, parentNode, (const unsigned short *)key, 0), true);
	}
	return Rva0018C4A9Result(j, false);
}

// Native0018C5FB standalone5B JMP to owned56B tree teardown0018C3E6.
// Original wrapper identity and full receiver extent are unknown.
class Rva0018C5FBTreeCleanupForward { public: void cleanup(); };
void Rva0018C5FBTreeCleanupForward::cleanup()
{
    reinterpret_cast<Rva0018C262 *>(this)->~Rva0018C262();
}
