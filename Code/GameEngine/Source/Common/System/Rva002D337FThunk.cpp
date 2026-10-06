// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva002D337FHide@@YAXXZ @ 0x002D337F 10B: call setHideScroll then tail-jmp hideSpellBook
// Evidence: leaf packet calls rowed 0x003FE8EB and 0x003FE99C, caller 0x002BF462.
void __cdecl setHideScroll();
void __cdecl hideSpellBook();
void Rva002D337FHide(void)
{
	setHideScroll();
	hideSpellBook();
}
