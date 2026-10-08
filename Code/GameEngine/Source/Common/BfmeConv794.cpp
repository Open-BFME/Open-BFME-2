// A sub-object call followed by its drop (trimmed from a five-body donor;
// the other three are declared-only here).
//
// The T2 body needs one ledger pin (bfmeCallDXH at 0x0070E5D0). The DXK body
// below reaches oleaut32!SysFreeString for the BSTR handle (the donor's
// bfmeCloseDXK import name) and the ledger's ??_V array-delete helper for
// the payload (the donor's bfmeFreeDXK).

class BfmeSubDXH
{
	unsigned char m_bfmeHead[4];
};

// Native70E6D1 reaches the same E177A0 matrix callback defined by
// AptRenderingContextStacks.cpp; Apt.cpp405 names pfnSetVertexMatrix.
// Reuse that owner directly instead of a second global plus linker alias.
struct AptMatrix;
extern void (__cdecl *g_bfmeAptMatrixCallbackAtE177A0)(AptMatrix *);
void __cdecl bfmeCallDXH(BfmeSubDXH *a, void *b, BfmeSubDXH *c);

struct BfmeThingDXH
{
	void bfmeGoDXH(void *a);
	unsigned char m_bfmeHead[0x20];
	BfmeSubDXH m_bfmeSub;
};

// ?bfmeGoDXH@BfmeThingDXH@@QAEXPAX@Z
void BfmeThingDXH::bfmeGoDXH(void *a)
{
	BfmeSubDXH *s = &m_bfmeSub;
	bfmeCallDXH(s, a, s);
	g_bfmeAptMatrixCallbackAtE177A0(reinterpret_cast<AptMatrix *>(s));
}

struct BfmeThingDXG
{
	void *bfmeGoDXG(unsigned char flags);
	void bfmeDtorDXG();
};

void bfmeGoDXI(void *a);

struct BfmeThingDXK
{
	void bfmeGoDXKa();
	void bfmeGoDXKb();
	void *m_bfmeH;
	void *m_bfmeP;
};

extern "C" __declspec(dllimport) void __stdcall SysFreeString(void *value);
void __cdecl operator delete[](void *p);

// ?bfmeGoDXKa@BfmeThingDXK@@QAEXXZ
//
// The donor's bfmeGoDXKa/bfmeGoDXKb twins are source-identical (the sweep's
// pick is DXKa); the ICF-sharing Close/delTVB names are eliminated by the
// void return plus the SysFreeString import. The body is dead in game.dat
// (no callers, no data refs).
void BfmeThingDXK::bfmeGoDXKa()
{
	if (m_bfmeH)
		SysFreeString(m_bfmeH);
	void *p = m_bfmeP;
	if (p)
		::operator delete[](p);
}

