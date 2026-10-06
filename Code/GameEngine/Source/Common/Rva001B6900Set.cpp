// cl: /MD
//
// ?Rva001B6900Set@@YAXPAXH@Z, retail 0x001B6900, 12 bytes.
// Free setter storing the second stack arg into [first+0x6C]; ret (cdecl).
// Evidence: mov eax [esp+8], mov ecx [esp+4], mov [ecx+0x6C] eax, ret.
// Caller 0x001BD050; LINK lane; sibling of Rva001B6920Set (+0xC4) same page.
void __cdecl Rva001B6900Set(void *p, int v)
{
	*(int *)((char *)p + 0x6C) = v;
}
