// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00210347@Rva00210347@@QAEAAU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@ABU23@@Z @0x00210347 68B hash insert via resize plus bucketIndex plus node alloc
// Evidence: same 68B shape as rowed Rva002249ED 0x002249ED calling resize 0x00212858 plus rowed bucketIndex 0x00223149 plus node allocator; allocator is thiscall twin of rowed free Rva0020F569Alloc 0x0020F569 via call-site mov ecx esi like 0x001DE556; buckets at +4 and count at +0x10; caller 0x002104ED.
#include "ascii_string.h"
#include <map>

struct NoCaseTreeValue4
{
	char m_body[4];
	NoCaseTreeValue4() { *(unsigned int *)m_body = 0; }
};

typedef _STL::pair<const AsciiString, NoCaseTreeValue4> NocasePair;

struct Rva00210347Node
{
	Rva00210347Node *m_next;
	NocasePair m_value;
};

class Rva000427195
{
public:
	void rva00212858(unsigned int count);
	int bucketIndex(const AsciiString *key);
};

class Rva00210347
{
public:
	NocasePair &rva00210347(const NocasePair &value);
	void *rva0020F569(const NocasePair &src);
private:
	void *m_unused;
	Rva00210347Node **m_beginBuckets;
	Rva00210347Node **m_endBuckets;
	Rva00210347Node **m_capacity;
	unsigned int m_numElements;
};

NocasePair &Rva00210347::rva00210347(const NocasePair &value)
{
	((Rva000427195 *)this)->rva00212858(m_numElements + 1);
	unsigned int bucket = ((Rva000427195 *)this)->bucketIndex(&value.first);
	Rva00210347Node *first = m_beginBuckets[bucket];
	Rva00210347Node *node = (Rva00210347Node *)rva0020F569(value);
	node->m_next = first;
	m_beginBuckets[bucket] = node;
	++m_numElements;
	return node->m_value;
}

// Native 2104ED..210566 RET4; existing insert210347 owns the name/value pair.
// The iterator provider only hashes and compares existing string bytes.
// End its nonthrowing lookup scope before constructing the conditional pair.
class Rva00056F61;
struct Rva0041534BIter
{
	void *m_node;
	Rva00056F61 *m_table;
 Rva0041534BIter(void *n, Rva00056F61 *t) : m_node(n), m_table(t) {}
};

class Rva00056F61
{
public:
	__declspec(nothrow) Rva0041534BIter rva0041534B(const AsciiString *key);
};

class Rva002104ED
{
public:
	NoCaseTreeValue4 &rva002104ED(const AsciiString *key);
private:
	char m_pad[0];
};


NoCaseTreeValue4 &Rva002104ED::rva002104ED(const AsciiString *key)
{
	void *node;
 { Rva0041534BIter it = ((Rva00056F61 *)this)->rva0041534B(key); node = it.m_node; }
	return node == 0 ? ((Rva00210347 *)this)->rva00210347(NocasePair(*key, NoCaseTreeValue4())).second
		: *(NoCaseTreeValue4 *)((char *)node + 8);
}


