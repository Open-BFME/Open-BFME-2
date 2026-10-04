// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// stlport
// ?rva002BFAD6@Rva002BFAD6@@QAEPAXPBX@Z @0x002BFAD6 68B
// Hashtable insert over Eva bucket vector: resize via pin 0x00212858 with
// count+1 hashes key via rowed bucketIndex 0x00223149 allocates node via rowed
// 0x002BF735 links old head bumps count returns value at +4. Same shape as
// landed 0x00410E67 68B insert and 0x002CFB4C 68B insert. Buckets at +4 count
// at +0x10. Caller is unclaimed 0x002BFCA9 so owner uses honest Rva name.
// Evidence: REL32 callees match this TU call graph; layout from EvaBucketIndex
// and Rva002BF735NewNode neighbours; landing unblocks caller chain.
#include "ascii_string.h"

class Rva000427195
{
public:
	void rva00212858(unsigned int n);
	int bucketIndex(const AsciiString *key);
};

class Rva002BF735
{
public:
	void *rva002BF735(const void *src);
};

class Rva002BFAD6
{
public:
	void *rva002BFAD6(const void *src);
private:
	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

void *Rva002BFAD6::rva002BFAD6(const void *src)
{
	((Rva000427195 *)this)->rva00212858(m_numElements + 1);
	int b = ((Rva000427195 *)this)->bucketIndex((const AsciiString *)src);
	void *old = m_beginBuckets[b];
	void *n = ((Rva002BF735 *)this)->rva002BF735(src);
	*(void **)n = old;
	m_beginBuckets[b] = n;
	++m_numElements;
	return (char *)n + 4;
}
