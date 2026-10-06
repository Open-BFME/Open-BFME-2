// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva002249ED@Rva00056F61@@QAEAAVRva0022304A@@ABV2@@Z @0x002249ED 68B
// Address-derived STLport hash-table insert. Caller 0x00224BDB passes a
// key/value pair after find misses; this body calls rowed bucketIndex 0x00223149
// and node allocator 0x002241AC. Its _M_insert role agrees with vendored
// STLport _hashtable.c. Target reads the bucket vector begin at +4 and element
// count at +0x10; the Rva00056F61 class label follows the caller's rowed find
// type, while the bucketIndex/new-node callees use the equivalent Rva000427195
// view. Ghidra boundary: 68 bytes ending in ret 4 at 0x00224A2E.

#include "ascii_string.h"

class Rva0022304A
{
public:
	AsciiString m_key;
	char m_value[0x10];
};

struct Rva002241ACNode
{
	Rva002241ACNode *m_next;
	Rva0022304A m_value;
};

class Rva000427195
{
public:
	void rva00212858(unsigned int count);
	int bucketIndex(const AsciiString *key);
	Rva002241ACNode *rva002241AC(const Rva0022304A &value);
};

class Rva00056F61
{
public:
	Rva0022304A &rva002249ED(const Rva0022304A &value);

private:
	void *m_unused;
	Rva002241ACNode **m_beginBuckets;
	Rva002241ACNode **m_endBuckets;
	Rva002241ACNode **m_capacity;
	unsigned int m_numElements;
};

Rva0022304A &Rva00056F61::rva002249ED(const Rva0022304A &value)
{
	Rva000427195 *table = (Rva000427195 *)this;
	table->rva00212858(m_numElements + 1);
	unsigned int bucket = table->bucketIndex(&value.m_key);
	Rva002241ACNode *first = m_beginBuckets[bucket];
	Rva002241ACNode *node = table->rva002241AC(value);
	node->m_next = first;
	m_beginBuckets[bucket] = node;
	++m_numElements;
	return node->m_value;
}
