int __stdcall rva00406ED7g(int a);
void __cdecl rva005B24CDg(int a, int b, int c);
void __cdecl rva005B2295(int a, int b, int c, int d);

// ?rva005B0416@@YGXH@Z @0x005B0416 48B: global stdcall wrapper threading one
// arg through three pinned/rowed cdecl callees with a single batched cleanup.
void __stdcall rva005B0416(int a)
{
	int r = rva00406ED7g(a);
	rva005B24CDg(r, 0xC728DC, a);
	rva005B2295(r, 0xC728D0, a, -1);
}
