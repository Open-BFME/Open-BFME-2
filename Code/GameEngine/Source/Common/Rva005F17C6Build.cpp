// cl: /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
//
// ?Rva005F17C6Build@@YA?AURva005F17C6S16@@ABURva005F17C6S12@@H@Z, retail 0x005F17C6, 39 bytes.
// Free function building a 16-byte struct from a 12-byte struct plus a dword:
// copies 12 bytes to a local then stores the dword at local+12 then copies 16
// bytes to the hidden return buffer. Same struct-concat family as rowed
// operator+ at 0x000B49C5 (12-byte AsciiStringPlusText) and unclaimed
// 0x000B6AA9/0x000B6AF5 (12-byte) and 0x000B64C5 (28-byte from 16+12).
// Leaf (no callees). Callers include 0x000BDE16 0x0020F95F 0x00578078 0x005780E2.
// Prev 0x005F17B1 Disp8PtrChase getter / next 0x005F2278 map-contains. Honest address name.
struct Rva005F17C6S12
{
	int m0, m1, m2;
};

struct Rva005F17C6S16
{
	int m0, m1, m2, m3;
};

struct Rva005F17C6S16 __cdecl Rva005F17C6Build(const struct Rva005F17C6S12 &src, int v)
{
	struct Rva005F17C6S16 r;
	*(struct Rva005F17C6S12 *)&r = src;
	r.m3 = v;
	return r;
}
