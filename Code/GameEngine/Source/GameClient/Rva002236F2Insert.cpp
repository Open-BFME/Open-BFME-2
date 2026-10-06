// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva002236F2@Rva002236F2@@QAEAAURva002236F2Value@@ABU2@@Z @0x002236F2 68B
// Hashtable insert over AsciiString->4B mapped: resize via pin 0x00212858 then
// rowed bucketIndex 0x00223149 then rowed new-node 0x00223547; links node into
// bucket and returns pair at +4. Same shape as rowed 0x002249ED (68B) with
// 12-byte node (4 next + 8 pair). Buckets at +4 count at +0x10. Callers at
// 0x00223F9B. Evidence: rowed callees plus layout from neighbours 0x0022366C
// and 0x00223736.
#include "ascii_string.h"

struct Rva002236F2Value
{
	AsciiString m_key;
	int m_mapped;
};

struct Rva002236F2Node
{
	Rva002236F2Node *m_next;
	Rva002236F2Value m_value;
};

class Rva000427195
{
public:
	void rva00212858(unsigned int count);
	int bucketIndex(const AsciiString *key);
};

class Rva00223547
{
public:
	void *rva00223547(const void *obj);
};

class Rva002236F2
{
public:
	Rva002236F2Value &rva002236F2(const Rva002236F2Value &value);
private:
	void *m_unused;
	Rva002236F2Node **m_beginBuckets;
	Rva002236F2Node **m_endBuckets;
	Rva002236F2Node **m_capacity;
	unsigned int m_numElements;
};

Rva002236F2Value &Rva002236F2::rva002236F2(const Rva002236F2Value &value)
{
	Rva000427195 *table = (Rva000427195 *)this;
	table->rva00212858(m_numElements + 1);
	unsigned int bucket = table->bucketIndex(&value.m_key);
	Rva002236F2Node *first = m_beginBuckets[bucket];
	Rva002236F2Node *node = (Rva002236F2Node *)((Rva00223547 *)this)->rva00223547(&value);
	node->m_next = first;
	m_beginBuckets[bucket] = node;
	++m_numElements;
	return node->m_value;
}
