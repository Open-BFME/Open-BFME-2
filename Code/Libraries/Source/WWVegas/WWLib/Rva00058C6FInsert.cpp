// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva00058C6F@Rva000427195@@QAEPAU?$pair@$$CBVAsciiString@@UTreeHintPayload0005808E@@@_STL@@PBU23@@Z @0x00058C6F 68B: hashtable insert for AsciiString-keyed 12B node family shared with new_node 0x00056E53 and bucketIndex 0x00223149 plus reserve 0x00212858. Evidence: reserve with count+1 then bucketIndex then new_node then link at bucket head then inc count then return node+4; buckets at +4 count at +0x10; same table Rva000427195 as EvaBucketIndex and 0x003A2F08.
#define _STLP_NO_EXCEPTIONS 1
#include <map>

#include "ascii_string.h"

struct TreeHintPayload0005808E
{
	char m_body[4];
};

typedef _STL::pair<const AsciiString, TreeHintPayload0005808E> TreeHintPair0005808E;

struct HashNode00056E53
{
	HashNode00056E53 *m_next;
	TreeHintPair0005808E m_val;
};

class Rva000427195
{
public:
	void rva00212858(unsigned int n);
	int bucketIndex(const AsciiString *name);
	HashNode00056E53 *rva00056E53(const TreeHintPair0005808E &value);
	TreeHintPair0005808E *rva00058C6F(const TreeHintPair0005808E *arg);

	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

TreeHintPair0005808E *Rva000427195::rva00058C6F(const TreeHintPair0005808E *arg)
{
	rva00212858(m_numElements + 1);
	int bucket = bucketIndex((const AsciiString *)arg);
	void *head = m_beginBuckets[bucket];
	HashNode00056E53 *node = rva00056E53(*arg);
	node->m_next = (HashNode00056E53 *)head;
	m_beginBuckets[bucket] = node;
	++m_numElements;
	return &node->m_val;
}

// Retail calls the new-node through this receiver (mov ecx esi) while the
// ledger rows the stdcall free copy; same ICF-twin pattern as 0x00056E8C.
// Bind the thiscall spelling to the rowed free body for the linked build.
#pragma comment(linker, "/alternatename:?rva00056E53@Rva000427195@@QAEPAUHashNode00056E53@@ABU?$pair@$$CBVAsciiString@@UTreeHintPayload0005808E@@@_STL@@@Z=?Rva00056E53New@@YGPAUHashNode00056E53@@ABU?$pair@$$CBVAsciiString@@UTreeHintPayload0005808E@@@_STL@@@Z")
