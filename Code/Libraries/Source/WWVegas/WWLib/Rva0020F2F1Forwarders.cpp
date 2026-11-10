// cl: /DNDEBUG /MD
//
// ?rva0020F2F1@@YGXPAXH@Z @0x0020F2F1 24B and ?rva0020F309@Rva0020EE29@@QAEXPAXH@Z
// @0x0020F309 24B: homogeneous stdcall forwarder twins into the unrowed
// stdcall worker at 0x0020ED51 (pinned from the emitted spelling; callee
// cleanup proven by the missing add-esp; 3 args from the 3 pushes, no ecx).
// Each forwards (obj+off, x, flag) with off 0xBC/flag 0 for the first and
// off 0xC8/flag 1 for the second (Rva0020EE29 neighbourhood: inner vectors
// at +0x2c; the +0xBC/+0xC8 members are unproven). Both params transient
// (no saved regs, frameless). Strict types unproven.
// 0x0020F309 is a thiscall member of the region manager Rva0020EE29 that never
// reads ECX: its only caller 0x0020F832 loads ECX=this (mov ecx,ebx) for it.
void __stdcall rva0020ED51(void *obj, int x, int flag);

#include "../../../../GameEngine/Include/GameLogic/Rva0020EE29.h"

void __stdcall rva0020F2F1(void *obj, int x)
{
	rva0020ED51((char *)obj + 0xBC, x, 0);
}

void Rva0020EE29::rva0020F309(void *obj, int x)
{
	rva0020ED51((char *)obj + 0xC8, x, 1);
}
