// cl: /O1 /arch:SSE /G7 /MD
// ?Rva006005D5RTrim@@YAXPAD@Z @0x006005D5 60B. RTrim trailing 9 10 13 32 via strlen then backward scan; null or empty returns early; prev 0x006005D0 next 0x00600611 contiguous; callee strlen via ji_00629170 row; callers 0x006015FD 0x0060165D; address-derived honest free name.
// Evidence: retail push esi mov esi [esp+8] test je cmp byte 0 je push call pop ecx lea eax [eax+esi-1] jmp cmp jae mov cl cmp 9 je cmp a je cmp d je cmp 20 jne dec cmp jae mov [eax+1] 0 pop ret.
extern "C" unsigned int __cdecl strlen(const char *s);

void __cdecl Rva006005D5RTrim(char *s)
{
	if (!s)
		return;
	if (*s == 0)
		return;
	char *p = s + strlen(s) - 1;
	while (p >= s) {
		char c = *p;
		if (c == 9 || c == 10 || c == 13 || c == 32)
			--p;
		else
			break;
	}
	*(p + 1) = 0;
}
