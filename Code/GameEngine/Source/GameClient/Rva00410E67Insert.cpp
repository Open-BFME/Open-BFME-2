// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// stlport
// ?rva00410E67@Rva000427195@@QAEPAU?$pair@$$CBVAsciiString@@UTreeHintPayload00410B17@@@_STL@@PBU23@@Z, retail 0x00410E67 68B. Hashtable insert
// over the Eva bucket vector for the AsciiString-keyed 12-byte node family.
// Buckets at +4 count at +0x10 (same layout as rowed erase 0x00223429 and
// bucketIndex 0x00223149). Resizes via pin 0x00212858 with count+1 hashes key
// via rowed 0x00223149 allocates node via pinned twin 0x00410997 (ICF twin of
// free NewNode) links old head bumps count returns value at +4. Same shape as
// landed 0x002234BA 68B insert. Caller 0x004112E7 in 0x004112A0.
#include "ascii_string.h"

struct TreeHintPayload00410B17
{
	unsigned char m_body[4];
};

namespace _STL {
template <class T1, class T2> struct pair
{
	~pair();
	T1 first;
	T2 second;
};
}

class Rva000427195
{
public:
	void rva00212858(unsigned int n);
	int bucketIndex(const AsciiString *key);
	void *rva00410997(const void *src);
	_STL::pair<const AsciiString, TreeHintPayload00410B17> *rva00410E67(const _STL::pair<const AsciiString, TreeHintPayload00410B17> *arg);
private:
	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

_STL::pair<const AsciiString, TreeHintPayload00410B17> *Rva000427195::rva00410E67(const _STL::pair<const AsciiString, TreeHintPayload00410B17> *arg)
{
	rva00212858(m_numElements + 1);
	int b = bucketIndex(&arg->first);
	void *old = m_beginBuckets[b];
	void *n = rva00410997(arg);
	*(void **)n = old;
	m_beginBuckets[b] = n;
	++m_numElements;
	return (_STL::pair<const AsciiString, TreeHintPayload00410B17> *)((char *)n + 4);
}
