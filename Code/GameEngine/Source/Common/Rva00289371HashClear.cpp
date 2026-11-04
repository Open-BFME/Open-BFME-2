// cl: /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfmelist /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// 0x00289371 (73 bytes): clear() of the hash table the ExperienceLevels
// store (vftable 0x00BFB8F4, class ExperienceLevelSystem) holds by pointer at +0x10;
// its reload notice (slot 4, 0x00289812) calls it first. The shape is
// STLport's hashtable::clear: walk the bucket vector (+4 begin, +8 end), free
// every node of each chain through the out-of-line node deleter 0x00289164
// (destroy the value, operator delete), null the bucket, then zero the
// element count (+0x10). Target evidence fixes the layout; that it is the
// STLport template instantiation is inference from the shape, and the
// value type (a member at node +8 with destructor 0x002889A4) is not modelled.

typedef unsigned int UnsignedInt;

#include <list>
#include <utility>
struct BfmePod264;
// Retail's pair destructor at 0x00288B89 calls the already-owned list
// base destructor at 0x002889A4. Keep that out-of-line boundary with real STLport.
namespace _STL {
template <> void _List_base<BfmePod264, allocator<BfmePod264> >::clear();
template <> _List_base<BfmePod264, allocator<BfmePod264> >::~_List_base();
}
typedef _STL::pair<const int, _STL::list<BfmePod264> > Rva00288B89;

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#include <stdlib.h>

class Rva00289371HashTable
{
private:
    struct Node;
public:
    void clear(); // 0x00289371
    ~Rva00289371HashTable(); // 0x002895BF
private:
    void deleteNode(Node *node); // 0x00289164
    char m_functors[4];
    Node **m_bucketsBegin;
    Node **m_bucketsEnd;
    Node **m_bucketsCapacity;
    unsigned int m_numElements;
};

struct Rva00289371HashTable::Node
{
    Node *m_next;
    Rva00288B89 m_value04;
};

void Rva00289371HashTable::clear()
{
	for (UnsignedInt i = 0; i < (UnsignedInt)(m_bucketsEnd - m_bucketsBegin); ++i)
	{
		Node *cur = m_bucketsBegin[i];
		while (cur != 0)
		{
			Node *next = cur->m_next;
			deleteNode(cur);
			cur = next;
		}
		m_bucketsBegin[i] = 0;
	}
	m_numElements = 0;
}

void Rva00289371HashTable::deleteNode(Node *node)
{
	node->m_value04.~pair();
	if (node)
		free(node);
}
