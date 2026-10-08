// cl: /MD
//
// AptCIH neighbourhood cluster.  Address-derived names; identities unproven
// except where the body carries them.  Reconstructed from retail bytes under
// the layout of AptCIHLevel006E0B80.cpp.

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

// global at VA 0x00E180C0; only the loaded pointer value is used (DIR32)
extern class AptRenderingContext *g_aptRenderingContextAtE180C0;

class AptCIH
{
public:
	virtual void vtableSlot0();
	unsigned char _pad[0x40];
	void *m_44;
	AptCIH *m_parent;
	void *m_4C;
	unsigned char _pad3[8];
	int m_code;

	void rva006E1DD0(void *pRect);
	void rva006E1C40(void *a, void *b);
};

// ?rva006E1DD0@AptCIH@@QAEXPAX@Z
void AptCIH::rva006E1DD0(void *pRect)
{
	if (pRect == 0) {
		g_bfmeAptAssertAtE17734("pRect", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCIH.cpp", 0x44D);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}
	unsigned *u = (unsigned *)pRect;
	unsigned neg = 0xCE6E6B28u;
	u[0] = 0x4E6E6B28u;
	u[2] = neg;
	u[3] = neg;
	u[1] = 0x4E6E6B28u;
	rva006E1C40((void *)(*(void **)&g_aptRenderingContextAtE180C0), pRect);
}
