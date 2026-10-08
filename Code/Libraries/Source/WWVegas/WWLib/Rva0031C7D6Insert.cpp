// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva0031C7D6@Rva000427195@@QAEPAXABU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@Z @0x0031C7D6 68B: hashtable insert_noresize for AsciiString-keyed 12B node family shared with new_node 0x0031BEF1 and bucketIndex 0x00223149 plus reserve 0x00212858. Evidence: reserve with count+1 then bucketIndex then new_node then link at bucket head then inc count then return node+4; buckets at +4 count at +0x10; caller 0x0031DB83; same table Rva000427195 as EvaBucketIndex.
#define _STLP_NO_EXCEPTIONS 1
#include <map>

#include "ascii_string.h"

struct NoCaseTreeValue4
{
public:
	unsigned char m_data[4];
	NoCaseTreeValue4() { *(unsigned int *)m_data = 0; }
};

typedef _STL::pair<const AsciiString, NoCaseTreeValue4> Bef1Pair;

struct Bef1Node
{
	Bef1Node *m_next;
	Bef1Pair m_pair;
};

struct Rva0031BEF1
{
	void *rva0031BEF1(Bef1Pair const &src);
};

class Rva000427195
{
public:
	void rva00212858(unsigned int n);
	int bucketIndex(const AsciiString *name);
	void *rva0031C7D6(const Bef1Pair &x);
	void **rva0031DB83(const AsciiString &name);

	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

void *Rva000427195::rva0031C7D6(const Bef1Pair &x)
{
	rva00212858(m_numElements + 1);
	int bucket = bucketIndex((const AsciiString *)&x);
	void *head = m_beginBuckets[bucket];
	Bef1Node *node = (Bef1Node *)((Rva0031BEF1 *)this)->rva0031BEF1(x);
	node->m_next = (Bef1Node *)head;
	m_beginBuckets[bucket] = node;
	++m_numElements;
	return &node->m_pair;
}

// Native 31DB83..31DBFC and WB C318E0; ControlBar command-set map +30.
// The iterator provider only hashes and compares existing string bytes.
// End its nonthrowing lookup scope before constructing the conditional pair.
class Rva00056F61;
struct Rva0041534BIter {
    void *m_node; Rva00056F61 *m_table;
    Rva0041534BIter(void *n,Rva00056F61 *t) : m_node(n),m_table(t) {}
    Rva0041534BIter(const Rva0041534BIter &it) : m_node(it.m_node),m_table(it.m_table) {}
};
class Rva00056F61 { public: __declspec(nothrow) Rva0041534BIter rva0041534B(const AsciiString *); };

void **Rva000427195::rva0031DB83(const AsciiString &name)
{
    void *node;
    {
        Rva0041534BIter it=((Rva00056F61 *)this)->rva0041534B(&name);
        node=it.m_node;
    }
    return node==0
        ? (void **)((char *)rva0031C7D6(Bef1Pair(name,NoCaseTreeValue4()))+4)
        : (void **)((char *)node+8);
}

