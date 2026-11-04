// ?rva00531720@PathfindZoneManager@@QAEEII@Z
// partial score=0.93 date=2026-10-04
// cl: /MD
// ?rva00531720@PathfindZoneManager@@QAEEII@Z @ 0x00531720 (55B): __thiscall bit-gated element test;
// array at +0xC stride 4 tests [e+1]&0x80 when (a>>1)&1 and [e+2]&1 when (a>>2)&1;
// callers at 0x0053192B 0x0053193A. The two gate masks live in a local two-byte
// ARRAY rather than two scalars: that keeps both computed mask values
// simultaneously live across the whole body, which is what makes MSVC 7.1 /O1
// allocate a callee-save for the index and emit the retail
// push esi / mov esi,[esp+0xc] bracket with the index still live at the lea.
// Two scalar locals (the previous bank) collapse to the same shape at 53B with
// no register save at all. See re_attempts.log row.
#include "../../Include/GameLogic/PathfindZoneManager.h"

unsigned char PathfindZoneManager::rva00531720(unsigned int a, unsigned int idx)
{
	unsigned int flags = a;
	unsigned char m[2];
	m[0] = (unsigned char)((flags >> 1) & 1);
	m[1] = (unsigned char)((flags >> 2) & 1);
	const unsigned char *element = (const unsigned char *)&field0C[idx].value;
	if (m[0] && (element[1] & 0x80))
		return 0;
	if (m[1] && (element[2] & 1))
		return 0;
	return 1;
}