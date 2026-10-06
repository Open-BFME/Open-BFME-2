// cl: /MD
// ?Rva00548C1ACleanup@@YAXXZ @0x00548C1A 22B: loop Free 0..8 then Close. Evidence: retail calls rowed Rva00548B97Free 0x00548B97 nine times plus tail-jmp to rowed Rva00415EF8Close 0x00415EF8; caller 0x0035BEDF calls with no ecx plus no args.
void __cdecl Rva00548B97Free(int index);
void __cdecl Rva00415EF8Close();
void __cdecl Rva00548C1ACleanup()
{
	for (int i = 0; i < 9; ++i)
		Rva00548B97Free(i);
	Rva00415EF8Close();
}
