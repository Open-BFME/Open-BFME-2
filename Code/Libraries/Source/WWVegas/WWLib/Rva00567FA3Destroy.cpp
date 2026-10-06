// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva00567FA3Destroy@@YAXPAURva004F691E@@0@Z @0x00567FA3 25B
// Evidence: unlock Destroy stride 16 via rowed dtor 0x004F691E; same recipe as Rva004F838CDestroy stride 12; caller 0x005681CE.
struct Rva004F691E
{
	~Rva004F691E();
	char m_pad[16];
};

void __cdecl Rva00567FA3Destroy(Rva004F691E *first, Rva004F691E *last)
{
	while (first != last) {
		first->~Rva004F691E();
		++first;
	}
}

