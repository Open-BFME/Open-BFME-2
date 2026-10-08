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

// Clean BF1 9cbfb551fe20dae985f91f2319d8997287b6a705
// Common/R1MemberPredicates.cpp supplies the one-argument equality expression
// under /O1 /arch:SSE /G7. Native2E6E7F..2E6E8A is a complete stack-argument
// leaf between this file's matched2E6E6C RET and matched2E6E8A range predicate.
// It returns EAX0 or1 for equality with raw32 value1, with no calls or memory
// reads beyond the argument. This unsigned view preserves all bit patterns;
// original callable identity and signedness/bool-vs-int spelling are unknown.
unsigned Rva002E6E7FEqualsOne(unsigned value)
{
    return value == 1;
}
