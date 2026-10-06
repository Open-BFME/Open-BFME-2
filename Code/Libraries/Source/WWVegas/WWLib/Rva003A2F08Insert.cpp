// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva003A2F08@Rva000427195@@QAEPAXABU?$pair@$$CBVAsciiString@@UTreeHintPayload00207343@@@_STL@@@Z @0x003A2F08 68B: hashtable insert_noresize for AsciiString-keyed 12B node family shared with new_node 0x003A2539 and bucketIndex 0x00223149 plus reserve 0x00212858. Evidence: reserve with count+1 then bucketIndex then new_node then link at bucket head then inc count then return node+4; buckets at +4 count at +0x10; caller 0x003A37AA; same table Rva000427195 as EvaBucketIndex.
#define _STLP_NO_EXCEPTIONS 1
#include <map>

#include "ascii_string.h"

struct TreeHintPayload00207343
{
	unsigned char value;
	~TreeHintPayload00207343();
};

typedef _STL::pair<const AsciiString, TreeHintPayload00207343> TreeHintPair003A2F08;

struct Rva003A2539Node
{
	void *_M_next;
	TreeHintPair003A2F08 _M_val;
};

struct Rva003A2539
{
	Rva003A2539Node *rva003A2539(TreeHintPair003A2F08 const &src);
};

class Rva000427195
{
public:
	void rva00212858(unsigned int n);
	int bucketIndex(const AsciiString *name);
	void *rva003A2F08(const TreeHintPair003A2F08 &x);

	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

void *Rva000427195::rva003A2F08(const TreeHintPair003A2F08 &x)
{
	rva00212858(m_numElements + 1);
	int bucket = bucketIndex((const AsciiString *)&x);
	void *head = m_beginBuckets[bucket];
	Rva003A2539Node *node = ((Rva003A2539 *)this)->rva003A2539(x);
	node->_M_next = head;
	m_beginBuckets[bucket] = node;
	++m_numElements;
	return &node->_M_val;
}
