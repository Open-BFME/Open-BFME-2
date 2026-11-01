// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs
// ??1Rva00415366@@QAE@XZ @0x00415366 57B
// Hash-table dtor sharing the rowed Rva000427195 clear 0x003A2A41 then freeing
// the bucket array at +4 via free 0x00030830 with a null guard.
// Evidence: call to rowed ?rva003A2A41@Rva000427195@@QAEXXZ with unadjusted ecx
// then mov esi [esi+4] null-guarded free; __EH_prolog frame with and [ebp-4] 0
// and or [ebp-4] -1. Same EH clear-plus-free shape as rowed
// ??1Rva000427195@@QAE@XZ 0x001FDEDB and ??1Rva0022366C@@QAE@XZ 0x0022366C.
// Layout matches that table: unused at +0 buckets at +4/+8/+0xC count at +0x10.
// Callers at 0x00415D15 and jmp at 0x0041547C.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport. /EHs lets free throw,
// preserving retail's unwind states.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

struct Rva00415366BucketHandle
{
	~Rva00415366BucketHandle()
	{
		if (m_beginBuckets)
			free(m_beginBuckets);
	}
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
};

#include "../../Include/GameLogic/Rva000427195.h"

class Rva00415366
{
public:
	~Rva00415366();
private:
	void *m_unused00;
	Rva00415366BucketHandle m_buckets;
	unsigned int m_numElements;
};

Rva00415366::~Rva00415366()
{
	((Rva000427195 *)this)->rva003A2A41();
}

// Native41547C tail JMP0x415366: unchanged thiscall receiver,
// no stack arguments and RET0. Original wrapper and outer type unknown.
struct Rva0041547CCleanupForward { void cleanup(); };
void Rva0041547CCleanupForward::cleanup() {
    reinterpret_cast<Rva00415366 *>(this)->~Rva00415366();
}
