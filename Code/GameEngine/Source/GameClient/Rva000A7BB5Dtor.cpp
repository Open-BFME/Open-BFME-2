// cl: /DNDEBUG /MD /EHs
// ??1Rva000A7BB5@@QAE@XZ @0x000A7BB5 57B
// Hash-table dtor sharing the rowed Rva000427195 clear 0x003A2A41 then freeing
// the bucket array at +4 via free 0x00030830 with a null guard.
// Evidence: call to rowed ?rva003A2A41@Rva000427195@@QAEXXZ with unadjusted ecx
// then mov esi [esi+4] null-guarded free; __EH_prolog frame with and [ebp-4] 0
// and or [ebp-4] -1. Same EH clear-plus-free shape as rowed
// ??1Rva000427195@@QAE@XZ 0x001FDEDB and ??1Rva0022366C@@QAE@XZ 0x0022366C.
// Layout matches that table: unused at +0 buckets at +4/+8/+0xC count at +0x10.
// Callers at 0x000A7DBA and jmp at 0x000A7CE9.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport. /EHs lets free throw,
// preserving retail's unwind states.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

struct Rva000A7BB5BucketHandle
{
	~Rva000A7BB5BucketHandle()
	{
		if (m_beginBuckets)
			free(m_beginBuckets);
	}
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
};

#include "../../Include/GameLogic/Rva000427195.h"

class Rva000A7BB5
{
public:
	~Rva000A7BB5();
private:
	void *m_unused00;
	Rva000A7BB5BucketHandle m_buckets;
	unsigned int m_numElements;
};

Rva000A7BB5::~Rva000A7BB5()
{
	((Rva000427195 *)this)->rva003A2A41();
}
