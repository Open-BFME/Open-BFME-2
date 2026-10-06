// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva004D39DEGet@@YAHHH@Z @0x004D39DE 18B
// Signed int helper. Evidence: free-function via two stack args plus ret
// (__cdecl); signed cmp plus jl plus jne; or-eax-minus-1 for equal plus
// dec for greater; 12 callers plus 11 unblocks; name stays
// address-derived.
int Rva004D39DEGet(int a, int b);

int Rva004D39DEGet(int a, int b)
{
	return (a < b) ? a : ((a == b) ? -1 : a - 1);
}
