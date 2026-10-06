// cl: /MD
// ?Rva004ECE14Clear@@YAXXZ @ 0x004ECE14, 8 bytes.
// Clears dword at data VA to 0 via and [mem],0.
// Evidence: single and [0x00E044AC],0 plus ret; no ecx use so free function;
// caller 0x002A9647; /O1 per and [m],0 idiom; g_ stopgap per linking rules.
extern int g_00E044AC;
// g_00E044AC: matched references place it at VA 0xe044ac (zero-filled .bss).
int g_00E044AC;
void __cdecl Rva004ECE14Clear()
{
	g_00E044AC = 0;
}
