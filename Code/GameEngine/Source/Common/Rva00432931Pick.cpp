// cl: /MD
// ?Rva00432931Pick@@YAPAURva00432931Entry@@PAU1@0@Z, retail 0x00432931, 55 bytes.
// Picks the valid (bit0 at +0x14 clear) entry with the larger unsigned field at +0x10;
// null if none valid. Callers 0x00432AA2 (types 4 vs 14) and 0x00432AC5 (types 6 vs 16)
// pass Rva00432A3BEntry pointers (24B entries at this+8); prev/next share layout
// (Payload +0x10 int, +0x14 flag) and /O1 flags.
struct Rva00432931Entry
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	unsigned int m_10;
	unsigned char m_14;
	char m_pad15[3];
};

struct Rva00432931Entry *Rva00432931Pick(struct Rva00432931Entry *a, struct Rva00432931Entry *b)
{
	if (a != 0 && ((a->m_14 & 1) == 0)) {
		if (b == 0 || (b->m_14 & 1))
			return a;
		return (a->m_10 <= b->m_10) ? b : a;
	} else {
		if (b != 0 && ((b->m_14 & 1) == 0))
			return b;
		return 0;
	}
}
