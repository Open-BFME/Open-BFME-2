// cl: /MD
//
// ?Rva001B6910Set@@YAXPAXH@Z, retail 0x001B6910, 15 bytes.
// Free setter storing the second stack arg into [first+0xC0]; ret (cdecl).
// Evidence: mov eax [esp+8], mov ecx [esp+4], mov [ecx+0xC0] eax, ret.
// Caller 0x001BD050; LINK lane; sibling of Rva001B6900Set/Rva001B6920Set.
void __cdecl Rva001B6910Set(void *p, int v)
{
	*(int *)((char *)p + 0xC0) = v;
}
