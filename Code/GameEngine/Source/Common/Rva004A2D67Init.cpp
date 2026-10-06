// cl: /DNDEBUG /MD
// ?Rva004A2D67Init@@YGPAXPAX@Z @0x004A2D67 27B.
// Leaf free function: memset(p, 0, 4) via the 0x006291AE import thunk, set
// bit 3 (*p |= 8) and return p. Evidence: slot 19 refs in the
// AutoHealBehavior (0x0083FC88) and ReplenishUnitsBehavior (0x00849F20)
// vtables; no callers; sole callee is the rowed ji_006291ae import.
void *__cdecl ji_006291ae(void *dest, int val, unsigned int count);
#pragma comment(linker, "/alternatename:?ji_006291ae@@YAPAXPAXHI@Z=?ji_006291ae@@YAXXZ")

void *__stdcall Rva004A2D67Init(void *p)
{
	ji_006291ae(p, 0, 4);
	*(int *)p |= 8;
	return p;
}
