// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Three retail lookup-or-zero wrappers (21B each). Retail shape per member:
// push [esp+4], call <lookup>, test eax, eax, pop ecx, je +4,
// mov eax, [eax+off], ret, xor eax, eax, ret.
// Reads as: p = lookup(key); return p ? p->value : 0.
// /O1 keeps the push on the stack slot and cleans it with pop ecx;
// /O2 preloads eax and uses add esp, 4. Lookup identities unproven;
// pin names are address-derived. One ledger row per wrapper.

struct Rva003FE245Holder
{
	unsigned char pad[0x38];
	unsigned value;
};

struct Rva0052B1EFHolder
{
	unsigned char pad[0xBC];
	unsigned value;
};

struct Rva0059E0C1Holder
{
	unsigned char pad[0xBC];
	unsigned value;
};

extern "C" Rva003FE245Holder *__cdecl Rva003FE245Lookup(unsigned key);
extern "C" Rva0052B1EFHolder *__cdecl Rva0052B1EFLookup(unsigned key);
extern "C" Rva0059E0C1Holder *__cdecl Rva0059E0C1Lookup(unsigned key);

unsigned Rva00318D4E(unsigned key)
{
	Rva003FE245Holder *found = Rva003FE245Lookup(key);
	return found ? found->value : 0;
}

unsigned Rva0052B225(unsigned key)
{
	Rva0052B1EFHolder *found = Rva0052B1EFLookup(key);
	return found ? found->value : 0;
}

unsigned Rva0059E0F7(unsigned key)
{
	Rva0059E0C1Holder *found = Rva0059E0C1Lookup(key);
	return found ? found->value : 0;
}
