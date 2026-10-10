// cl: /MD
// ?Rva00548C1ACleanup@@YAXXZ @0x00548C1A 22B: loop Free 0..8 then Close. Evidence: retail calls rowed GameSpyCloseOverlay 0x00548B97 nine times plus tail-jmp to rowed Rva00415EF8Close 0x00415EF8; caller 0x0035BEDF calls with no ecx plus no args.
enum GSOverlayType;
void __cdecl GameSpyCloseOverlay(GSOverlayType overlay);
void __cdecl Rva00415EF8Close();
void __cdecl Rva00548C1ACleanup()
{
	for (int i = 0; i < 9; ++i)
		GameSpyCloseOverlay((GSOverlayType)i);
	Rva00415EF8Close();
}
