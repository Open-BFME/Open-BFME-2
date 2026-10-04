// cl: /O1 /DNDEBUG /MD
//
// 0x00289371 (73 bytes): clear() of the hash table the ExperienceLevels
// store (vftable 0x00BFB8F4, class Rva00289ABD) holds by pointer at +0x10;
// its reload notice (slot 4, 0x00289812) calls it first. The shape is
// STLport's hashtable::clear: walk the bucket vector (+4 begin, +8 end), free
// every node of each chain through the out-of-line node deleter 0x00289164
// (destroy the value, operator delete), null the bucket, then zero the
// element count (+0x10). Target evidence fixes the layout; that it is the
// STLport template instantiation is inference from the shape, and the
// value type (a member at node +8 with destructor 0x002889A4) is not modelled.

typedef unsigned int UnsignedInt;

class Rva00289371HashTable
{
public:
	void clear();
private:
	struct Node
	{
		Node *m_next;
	};
	void deleteNode(Node *node);	// 0x00289164
	char m_functors[4];
	Node **m_bucketsBegin;
	Node **m_bucketsEnd;
	Node **m_bucketsCapacity;
	UnsignedInt m_numElements;
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
