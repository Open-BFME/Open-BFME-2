// cl: /DNDEBUG /MD /EHs
// ??1Rva0022366C@@QAE@XZ @0x0022366C 57B
// Hash-table dtor sharing the rowed Rva000427195 clear 0x003A2A41 then freeing
// the bucket array at +4 via free 0x00030830 with a null guard.
// Evidence: call to rowed ?rva003A2A41@Rva000427195@@QAEXXZ with unadjusted ecx
// then mov esi [esi+4] null-guarded free; __EH_prolog frame with and [ebp-4] 0
// and or [ebp-4] -1. Same EH clear-plus-free shape as rowed
// ??1Rva000427195@@QAE@XZ 0x001FDEDB (Rva000427195Dtor.cpp precedent).
// Layout matches that table: unused at +0 buckets at +4/+8/+0xC count at +0x10.
// Outer reuses the rowed clear via cast since the address already has a row.
// Callers at 0x00224B09 0x00224B24 0x00224B30 0x002E044F and jmp at 0x002239AD.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport. /EHs lets free throw,
// preserving retail's unwind states.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

struct Rva0022366CBucketHandle
{
	~Rva0022366CBucketHandle()
	{
		if (m_beginBuckets)
			free(m_beginBuckets);
	}
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
};

#include "../../Include/GameLogic/Rva000427195.h"

class Rva0022366C
{
public:
	~Rva0022366C();
private:
	void *m_unused00;
	Rva0022366CBucketHandle m_buckets;
	unsigned int m_numElements;
};

Rva0022366C::~Rva0022366C()
{
	((Rva000427195 *)this)->rva003A2A41();
}
