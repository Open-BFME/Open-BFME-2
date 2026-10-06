// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva002E6E6CGet@@YAHH@Z @0x002E6E6C 19B.
// Honest address name: free __cdecl predicate with 22 UNCLAIMED callers and
// no donor string vtable or export to prove a real identity. Byte-exact model:
// return v == 1 || v >= 16. Evidence: 22 callers pushing one int and testing
// al; prev/next are Disp getters in the same Common dir; flags /O1 from
// Rva002E6ECAGet sibling with the same xor-inc and cmp-imm8 idioms.

int Rva002E6E6CGet(int v);

int Rva002E6E6CGet(int v)
{
	return v == 1 || v >= 16;
}
