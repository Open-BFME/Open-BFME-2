// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// ?rva002234BA@Rva000427195@@QAEPAU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@PBU23@@Z @0x002234BA 68B
// Hash insert old-before-new over the Eva bucket vector. Buckets at +4,
// count at +0x10 (same layout as rowed erase 0x00223429 and bucketIndex
// 0x00223149). Resizes via pin 0x00212858 with count+1, hashes key via rowed
// 0x00223149, allocates node via rowed 0x002230FF, links old head, bumps
// count, returns value at +4. Same shape as landed 0x00223854 68B insert.
// Callers 0x0022363A. Returns pair pointer for LINK BONUS style callers.
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

struct NoCaseTreeValue4
{
	char m_body[4];
};

namespace _STL {
template <class T1, class T2> struct pair
{
	~pair();
	T1 first;
	T2 second;
};
}

class Rva002230FF
{
public:
	void *rva002230FF(const void *obj);
};

class Rva000427195
{
public:
	void rva00212858(unsigned int n);
	int bucketIndex(const AsciiString *key);
	_STL::pair<const AsciiString, NoCaseTreeValue4> *rva002234BA(const _STL::pair<const AsciiString, NoCaseTreeValue4> *arg);
private:
	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

_STL::pair<const AsciiString, NoCaseTreeValue4> *Rva000427195::rva002234BA(const _STL::pair<const AsciiString, NoCaseTreeValue4> *arg)
{
	rva00212858(m_numElements + 1);
	int b = bucketIndex(&arg->first);
	void *old = m_beginBuckets[b];
	void *n = ((Rva002230FF *)this)->rva002230FF(arg);
	*(void **)n = old;
	m_beginBuckets[b] = n;
	++m_numElements;
	return (_STL::pair<const AsciiString, NoCaseTreeValue4> *)((char *)n + 4);
}
