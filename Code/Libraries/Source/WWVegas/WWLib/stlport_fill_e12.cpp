// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0007E3B1Fill@@YAXPAH0ABH@Z placeholder, retail 0x0007E3B1, 40 bytes.
// Fill 12 bytes via explicit moves, no string ops.
// Evidence: callers 0x000827B0 0x000827F4; prev pod hash /O1 /EHsc next fill Pod44 same flags.
struct E12
{
	int a[3];
};

void __cdecl Rva0007E3B1Fill(int *dst, int *end, const int *value)
{
	while (dst != end) {
		dst[0] = value[0];
		dst[1] = value[1];
		dst[2] = value[2];
		dst += 3;
	}
}
