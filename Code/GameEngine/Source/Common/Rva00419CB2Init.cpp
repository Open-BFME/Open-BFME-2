// cl: /MD
//
// ?Rva00419CB2Init@@YAXPAX@Z, retail 0x00419CB2, 22 bytes. memset 4 bytes to
// 0 then bitwise-NOT the dword (sets to -1). Evidence: call to rowed memset
// thunk 0x006291AE with pushes 4 0 ptr; caller 0x00419CC8 passes global
// 0x00E030D0; unblocks 0x00419CC8.
#pragma function(memset)

extern "C" void *memset(void *dst, int value, unsigned int size);

void __cdecl Rva00419CB2Init(void *p)
{
	memset(p, 0, 4);
	*(int *)p = ~*(int *)p;
}
