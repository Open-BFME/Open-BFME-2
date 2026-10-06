// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00210347@Rva00210347@@QAEAAU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@ABU23@@Z @0x00210347 68B hash insert via resize plus bucketIndex plus node alloc
// Evidence: same 68B shape as rowed Rva002249ED 0x002249ED calling resize 0x00212858 plus rowed bucketIndex 0x00223149 plus node allocator; allocator is thiscall twin of rowed free Rva0020F569Alloc 0x0020F569 via call-site mov ecx esi like 0x001DE556; buckets at +4 and count at +0x10; caller 0x002104ED.
#include "ascii_string.h"
#include <map>

struct NoCaseTreeValue4
{
	char m_body[4];
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
