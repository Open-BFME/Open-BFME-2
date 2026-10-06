// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva000B64C5Build@@YA?AURva000B64C5S28@@ABURva000B64C5S16@@ABURva000B64C5S12@@@Z, retail 0x000B64C5, 44 bytes.
// Free function building a 28-byte struct from a 16-byte struct plus a 12-byte
// struct: copies 16 bytes to a local then 12 bytes to local+16 then copies 28
// bytes to the hidden return buffer. Same struct-concat family as rowed
// Rva005F17C6Build at 0x005F17C6 (12-byte plus dword to 16-byte) which names
// this address as 28-byte from 16+12. Leaf (no callees). Caller 0x000BDD6C.
// Honest address name.
struct Rva000B64C5S16
{
	int m0, m1, m2, m3;
};

struct Rva000B64C5S12
{
	int m0, m1, m2;
};

struct Rva000B64C5S28
{
	int m0, m1, m2, m3, m4, m5, m6;
};

struct Rva000B64C5S28 __cdecl Rva000B64C5Build(const struct Rva000B64C5S16 &src1, const struct Rva000B64C5S12 &src2)
{
	struct Rva000B64C5S28 r;
	*(struct Rva000B64C5S16 *)&r = src1;
	*(struct Rva000B64C5S12 *)((char *)&r + 16) = src2;
	return r;
}
