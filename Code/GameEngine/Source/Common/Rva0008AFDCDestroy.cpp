// cl: /MD
//
// ?Rva0008AFDCDestroy@@YAXPAX0@Z @0x0008AFDC 24B: two-arg range-destroy
// forwarder in the Rva003B8E13DestroyRange shape (push ebp / mov ebp,esp /
// push ecx / lea eax,[ebp-1] / push eax / push [ebp+0xC] / push [ebp+8] /
// call aux / add esp,0xC / leave / ret). Forwards (first,last) plus a tag
// temporary to the pinned 3-arg aux ?Rva0008A1FDDestroy@@YAXPAX0H@Z at
// 0x0008A1FD (27B, Ghidra FUN_0048a1fd; re_log blocked 5457: needs push-0
// deleting-dtor recipe for rowed ??_GRva00087A93 at 0x00087A93, so the aux
// itself stays pinned-not-rowed and only this forwarder is verified).
// Retail bytes at 0x8AFDC match the forwarder verbatim (E8 at +14 ->
// 0x8A1FD). Element type is unclaimed (void* pass-through; stride lives in
// the aux, not here). Caller is the sibling vector 0x0008B470 (63B, same
// batch, separate TU to keep this callee declaration-only per the
// fifth-pattern register-save rule).

void __cdecl Rva0008A1FDDestroy(void *first, void *last, int tag);

void __cdecl Rva0008AFDCDestroy(void *first, void *last)
{
	char tag;
	Rva0008A1FDDestroy(first, last, (int)&tag);
}
