// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva00051B89Mod@@YGIPAXI@Z @0x00051B89 24B
// Unsigned modulo helper. Evidence: free-function via two stack args plus
// ret-8 (__stdcall); dword chase [esp+4] plus [eax+8] with null skip;
// xor-edx plus div plus mov-eax-edx remainder; 3 callers plus 2 unblocks;
// name stays address-derived.
unsigned __stdcall Rva00051B89Mod(void *p, unsigned div);

unsigned __stdcall Rva00051B89Mod(void *p, unsigned div)
{
	unsigned q = *(unsigned *)p;
	if (q != 0)
		q = *(unsigned *)(q + 8);
	return q % div;
}
