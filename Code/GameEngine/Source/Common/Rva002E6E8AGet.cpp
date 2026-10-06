// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva002E6E8AGet@@YAHH@Z @0x002E6E8A 21B.
// Honest address name: unclaimed free-function range predicate testing
// 0x11 <= v <= 0x40. Byte-exact model: two cmp-imm8 guards sharing one
// false epilogue with xor-inc true path.
// Evidence: 12 UNCLAIMED callers pushing one int and testing al
// in Pathfind-adjacent bodies 0x002E7D6D 0x002E85AD 0x002E916A 0x002EE64A
// and others; callees none; prev/next are Disp getters in the same Common
// dir; flags /O1 from Rva002E6ECAGet sibling with the same xor-inc idioms.

int __cdecl Rva002E6E8AGet(int v);

int __cdecl Rva002E6E8AGet(int v)
{
	if (v < 0x11 || v > 0x40)
		return 0;
	return 1;
}
