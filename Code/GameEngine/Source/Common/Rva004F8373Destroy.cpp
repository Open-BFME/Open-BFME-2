// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva004F8373Destroy@@YAXPAURva004F6986@@0@Z, retail 0x004F8373, 25 bytes.
// Destroy loop stride 8 via add esi 8 plus rowed dtor 0x004F6986 61B.
// Evidence: chain from 0x004F6986; callers 0x004F880D 0x004F89E3; prev Create 0x004F711C next Destroy 0x004F838C both /O1.

struct Rva004F6986
{
	~Rva004F6986();
	char m_pad[8];
};

void __cdecl Rva004F8373Destroy(Rva004F6986 *first, Rva004F6986 *last)
{
	while (first != last) {
		first->~Rva004F6986();
		++first;
	}
}
