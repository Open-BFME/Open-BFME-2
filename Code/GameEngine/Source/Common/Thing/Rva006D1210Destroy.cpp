// ?Rva006D1210Destroy@@YAXPAX@Z, retail 0x006D1210, 32 bytes.
//
// Destroy helper for the Nugget-chain block family: null-guarded teardown
// of a 16-byte block through 0x006D0F20, then sized release through the
// shared deallocator at 0x006DB270 (allocator object at 0x00E176E8, args
// (block, 16)). Both callees resolve via pins; the allocator global is a
// TU-local extern (DIR32 auto-patches). No // cl: line (defaults match).
#include "../../../Include/Common/Rva006D0F20.h"

#include "../../../Include/Common/Rva006DB270.h"

extern Rva006DB270 *g_pChainBlockAllocator; // 0x00E176E8

// ?Rva006D1210Destroy@@YAXPAX@Z
void Rva006D1210Destroy(void *block)
{
	Rva006D0F20 *target = (Rva006D0F20 *)block;
	if (target == 0)
		return;
	target->release();
	g_pChainBlockAllocator->freeBlock(target, 0x10);
}
