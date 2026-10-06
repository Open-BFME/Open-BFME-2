// cl: /O2 /MD /EHsc
// Rva0070E440::rva0070E440, retail 0x0070E440 (151 B).
// Asserts the out pointer (the AptRenderingContext.cpp "pMatrix" assert at line
// 0x49 through the shared g_bfmeAptAssertAtE17734 hook), then writes the six-float box at
// this+0x20 when the count at this+0x3BC is positive, otherwise the six-float
// default box in .data at 0x00E180C4.  This is a body-only getter: each stored
// dword is a separate mov, not a rep movsd, so struct assignment is the shape.
// The class is the TU-scoped view; the count/box offsets are target evidence.
struct Rva0070E440Box
{
	float v[6];
};

class Rva0070E440
{
public:
	void rva0070E440(Rva0070E440Box *out);

private:
	char m_pad[0x20];
	Rva0070E440Box m_box;	// +0x20
	char m_pad2[0x3bc - 0x20 - 0x18];
	int m_count;			// +0x3BC
};

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
// g_00E180C4: VA 0x00E180C4 default six-float box (zero-filled; beyond
// .data raw, Ghidra shows zeros). Defined here; nothing else rowed or pinned it.
Rva0070E440Box g_00E180C4;

void Rva0070E440::rva0070E440(Rva0070E440Box *out)
{
	if (!out) {
		g_bfmeAptAssertAtE17734("pMatrix", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptRenderingContext.cpp", 0x49);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__asm int 3
	}

	if (m_count > 0)
		*out = m_box;
	else
		*out = g_00E180C4;
}
