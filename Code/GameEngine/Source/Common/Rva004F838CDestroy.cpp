// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva004F838CDestroy@@YAXPAURva004F691E@@0@Z retail 0x004F838C 25B
// Evidence: unlock lane; stride 12 via add esi 0xC plus rowed dtor 0x004F691E 13B; callers 0x004F887C 0x004F89A8 0x004F8A17 plus vector dtor next; prev Create same /O1.
struct Rva004F691E
{
	~Rva004F691E();
	char m_pad[12];
};

void __cdecl Rva004F838CDestroy(Rva004F691E *first, Rva004F691E *last)
{
	while (first != last) {
		first->~Rva004F691E();
		++first;
	}
}
