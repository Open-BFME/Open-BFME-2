// ?rva00212858@Rva000427195@@QAEXI@Z
// partial score=0.6699 date=2026-10-06
// ?rva00212858@Rva000427195@@QAEXI@Z
// partial score=0.95 date=2026-10-01
// 197B of 199B (the previous best was 184B). Needs pins: ?rva00055041@Rva000427195@@QBEIPBVAsciiString@@@Z -> 0x00055041 (hasher, thiscall ICF twin of the stdcall row) and ?rva0005571B@Rva000427195@@QBEII@Z -> 0x0005571B (_M_next_size). Remaining diff: ebx/edi swapped and oldN kept in a register (retail spills it to [ebp-0x10] and holds &buckets[bucket] in edi), frame 0x18 vs 0x1c.
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs-c-
// ?rva00212858@Rva000427195@@QAEXI@Z @0x00212858 199B
// STLport hashtable::resize of the AsciiString-keyed hash_map family (class Rva000427195:
// hasher at +0, bucket vector<void *> at +4/+8/+0xC, count at +0x10). Grows only when the
// hint exceeds the bucket count and _M_next_size (ICF twin 0x0005571B) is larger: builds a
// zeroed vector through the rowed get_allocator 0x00023B50 and fill ctor 0x00026A40, rehashes
// every node through the hasher (ICF twin 0x00055041, called with ecx = this), swaps
// (0x00026B60) and frees the old storage inline (_STLP_USE_MALLOC). No EH frame, ret 4.
// Evidence: 36 callers are the family's 36B/68B insert wrappers (resize(n + 1), then the
// noresize insert); the node's key sits at +4, as in the rowed bucketIndex 0x00223149.
#include <stdlib.h>
#include "ascii_string.h"

// (CRT prototype from the standard header)

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A = allocator<T> > class vector;
template <> class vector<void *, allocator<void *> >
{
public:
	vector(unsigned int n, void *const &value, const allocator<void *> &a);
	~vector() { if (_M_start) free(_M_start); }
	allocator<void *> get_allocator() const;
	void swap(vector &other);
	unsigned int size() const { return _M_finish - _M_start; }
	void *&operator[](unsigned int n) { return *(_M_start + n); }
	void **_M_start;
	void **_M_finish;
	void **_M_end_of_storage;
};
}

struct Rva00212858Node
{
	Rva00212858Node *next;
	AsciiString key;
};

struct Rva000427195Hash
{
	// ICF twin of the rowed stdcall Rva00055041AsciiHash (the body ignores ecx)
	unsigned int operator()(const AsciiString &key) const;
};

class Rva000427195
{
public:
	unsigned int rva00055041(const AsciiString *key) const;
	unsigned int rva0005571B(unsigned int hint) const;
	void rva00212858(unsigned int hint);
private:
	unsigned int bucketOf(const Rva00212858Node *node, unsigned int n) const { return m_hash(node->key) % n; }
	Rva000427195Hash m_hash;
	char m_functors[3];
	_STL::vector<void *> m_buckets;
	unsigned int m_numElements;
};

void Rva000427195::rva00212858(unsigned int hint)
{
	const unsigned int oldN = m_buckets._M_finish - m_buckets._M_start;
	if (hint > oldN)
	{
		const unsigned int n = rva0005571B(hint);
		if (n > oldN)
		{
			_STL::vector<void *> tmp(n, (void *)0, m_buckets.get_allocator());
			for (unsigned int bucket = 0; bucket < oldN; ++bucket)
			{
				Rva00212858Node *first = (Rva00212858Node *)m_buckets._M_start[bucket];
				while (first)
				{
					unsigned int newBucket = rva00055041(&first->key) % n;
					m_buckets._M_start[bucket] = first->next;
					first->next = (Rva00212858Node *)tmp._M_start[newBucket];
					tmp._M_start[newBucket] = first;
					first = (Rva00212858Node *)m_buckets._M_start[bucket];
				}
			}
			m_buckets.swap(tmp);
		}
	}
}
