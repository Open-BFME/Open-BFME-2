// cl: /O2 /MD
//
// ?rva006E1E30@Rva006E1E30@@QAEXPAURva006F9FC0Rect@@@Z, retail 0x006E1E30
// (197 bytes).  Bounding-box builder for an AptCIH node: seed a 24-byte
// six-float box from the global rectangle at VA 0x00E180C4, fold each
// ancestor's 0x0C matrix in with the rowed bfmeMul1208 (VA 0x00B0E5D0), push
// the vertex matrix on the global AptRenderingContext at VA 0x00E180C0, emit
// the box through the BfmeThingDXH view of that context, fill the caller's
// 16-byte rect through the rowed AptCIH::rva006E1DD0 and pop the matrix.
// The parent chain and matrix offset repeat Rva006E1DD0Cluster.cpp's layout.

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

struct Rva006F9FC0Rect
{
	float x1;
	float y1;
	float x2;
	float y2;
};

struct BfmeM1208
{
	float m_w[6];
};

void __cdecl bfmeMul1208(const BfmeM1208 *a, const BfmeM1208 *b, BfmeM1208 *out);

class AptRenderingContext
{
public:
	void pushVertexMatrix();
	void popVertexMatrix();
};

class BfmeThingDXH
{
public:
	void bfmeGoDXH(void *a);
};

class AptCIH
{
public:
	void rva006E1DD0(void *pRect);
};

AptRenderingContext *g_aptRenderingContextAtE180C0; // VA 0x00E180C0
BfmeM1208 g_aptBoxAtE180C4;                         // VA 0x00E180C4

class Rva006E1E30
{
public:
	virtual void v0();

	char m_pad04[0x48 - 0x04];
	Rva006E1E30 *m_parent;  // +0x48

	void rva006E1E30(Rva006F9FC0Rect *out);
};

// ?rva006E1E30@Rva006E1E30@@QAEXPAURva006F9FC0Rect@@@Z
void Rva006E1E30::rva006E1E30(Rva006F9FC0Rect *out)
{
	if (out == 0) {
		g_bfmeAptAssertAtE17734("pRect", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCIH.cpp", 0x46C);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}

	BfmeM1208 box = g_aptBoxAtE180C4;
	for (Rva006E1E30 *p = m_parent; p != 0; p = p->m_parent)
		bfmeMul1208(&box, (const BfmeM1208 *)((char *)p + 0xC), &box);

	g_aptRenderingContextAtE180C0->pushVertexMatrix();
	((BfmeThingDXH *)g_aptRenderingContextAtE180C0)->bfmeGoDXH(&box);
	((AptCIH *)this)->rva006E1DD0(out);
	g_aptRenderingContextAtE180C0->popVertexMatrix();
}
