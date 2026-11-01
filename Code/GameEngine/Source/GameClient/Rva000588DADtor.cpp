// cl: /DNDEBUG /MD /EHs
// ??1Rva000588DA@@QAE@XZ @0x000588DA 57B.
// Hash-table scalar dtor: clears via the rowed rva003A2A41 then the inline
// bucket-handle member dtor frees the bucket array at +4 via the rowed free
// 0x00030830 with a null guard. Same EH clear-plus-free shape as the rowed
// ??1Rva000427195@@QAE@XZ 0x001FDEDB (Rva000427195Dtor.cpp precedent:
// a throwing free under /EHs emits retail's unwind state store). Callers at 0x00061349
// and jmp at 0x00059259.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport. /EHs lets free throw,
// preserving retail's unwind states.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

#include "../../Include/GameLogic/Rva000427195.h"

struct Rva000588DABucketHandle
{
	~Rva000588DABucketHandle()
	{
		if (m_beginBuckets)
			free(m_beginBuckets);
	}
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
};

struct Rva000588DA
{
	~Rva000588DA();
	void *m_unused00;
	Rva000588DABucketHandle m_buckets;
	unsigned int m_numElements;
};

Rva000588DA::~Rva000588DA()
{
	((Rva000427195 *)this)->rva003A2A41();
}
