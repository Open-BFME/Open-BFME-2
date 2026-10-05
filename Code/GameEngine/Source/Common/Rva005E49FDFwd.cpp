// cl: /O1 /DNDEBUG /MD
// ?rva005E49FD@@YAXHHHH@Z @0x005E49FD 30B cdecl forwarder.
// Takes (a, b, c, d), allocates a bool tmp, calls pinned 0x005E4817
// (cdecl, 5 args: bool* + 4 ints), cleans 0x14, returns void.
// Address-derived; callee identity unproven (partition bank is 4-arg,
// this site passes 5 with a bool* head).
void __cdecl Rva005E4817Forward(int a, int b, int c, int d, bool *tmp);

void __cdecl rva005E49FD(int a, int b, int c, int d)
{
	bool tmp;
	Rva005E4817Forward(a, b, c, d, &tmp);
}
