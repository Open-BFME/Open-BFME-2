// cl: /MD
//
// ?Rva001B6920Set@@YAXPAXH@Z, retail 0x001B6920, 15 bytes.
// Free setter storing the second stack arg into [first+0xC4]; ret (cdecl,
// caller cleans). Evidence: mov eax [esp+8], mov ecx [esp+4],
// mov [ecx+0xC4] eax, ret. Caller 0x001B5910 (389B) pushes two args;
// LINK lane: landing this unblocks 0x001B5910 and 308B of matched files.
void __cdecl Rva001B6920Set(void *p, int v)
{
	*(int *)((char *)p + 0xC4) = v;
}
