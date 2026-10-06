// cl: /MD
// ?Rva000E1D51Forward@@YAPAVRva00072A94@@PAV1@00PAX@Z, RVA 0x000E1D51, 29B.
// Forwarder via local tag to rowed copy 0x000E1860. Same 29B shape as
// Rva00219947Forward and Rva00150265Copy: push ebp/mov ebp esp/push ecx/
// push 0/lea eax [ebp-1]/push eax/push [ebp+0x10]/push [ebp+0xc]/push
// [ebp+8]/call/add esp 0x14/leave/ret. Callers at 0x000E3AEF and 0x000E3B0D
// push 4 and use eax return. Callee 0x000E1860 rowed as 3-arg but takes
// dummy tag plus 0; 5-arg overload shares identical 47B body (extra args
// dead) as in Rva0014FA90Copy precedent. Honest address names.
class Rva00072A94;

Rva00072A94 *__cdecl Rva000E1860Copy(Rva00072A94 *first, Rva00072A94 *last, Rva00072A94 *dest, void *tag, int extra);

Rva00072A94 *__cdecl Rva000E1D51Forward(Rva00072A94 *first, Rva00072A94 *last, Rva00072A94 *dest, void *ignored)
{
	char tag;
	return Rva000E1860Copy(first, last, dest, &tag, 0);
}
