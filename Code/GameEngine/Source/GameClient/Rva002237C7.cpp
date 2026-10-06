// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva002237C7@Rva00223591@@QAEPAXPBX@Z @0x002237C7 68B
// Hashtable insert for 16-byte node (4 next + 12 BfmeStringRecord00222E08): grow via pinned 0x00212858 then bucket via rowed 0x00223149 then new-node via rowed 0x0022356C then link and return node+4.
// Evidence: same shape as rowed Rva00223591::rva00223854 in Rva00223591Free.cpp; neighbours 0x00223736 erase and 0x0022380B clear share layout +4 buckets +0x10 count; unblocks 0x0022402A.
#include "ascii_string.h"

class Rva000427195
{
public:
	void rva00212858(unsigned int n);
	int bucketIndex(const AsciiString *name);
};

class Rva0022356C
{
public:
	void *rva0022356C(const void *obj);
};

class Rva00223591
{
public:
	void *rva002237C7(const void *arg);
private:
	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

void *Rva00223591::rva002237C7(const void *arg)
{
	((Rva000427195 *)this)->rva00212858(m_numElements + 1);
	int b = ((Rva000427195 *)this)->bucketIndex((const AsciiString *)arg);
	void *old = m_beginBuckets[b];
	void *n = ((Rva0022356C *)this)->rva0022356C(arg);
	*(void **)n = old;
	m_beginBuckets[b] = n;
	++m_numElements;
	return (char *)n + 4;
}
