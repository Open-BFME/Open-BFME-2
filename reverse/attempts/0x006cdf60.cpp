// ?Rva006CDF60Shutdown@@YAXXZ
// partial score=0.96 date=2026-10-06
// cl: /O2 /MD
// ?Rva006CDF60Shutdown@@YAXXZ @0x006CDF60 284B evidence Apt.cpp shutdown6CDF60 DogmaPoolBytes GetTotalBytesUsed both pools plus Apt assert 0x29a plus Log 0x006CC110
extern int g_bfmeAptInitAtE17700;
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
extern void (__cdecl *g_bfmeAptFreeSizeAtE17730)(void *, unsigned int);
void __cdecl Rva006CC110Log(int, const char *, ...);
class DOGMA_PoolManager
{
public:
	unsigned int GetTotalBytesUsed();
};
class Rva006CC4A0
{
public:
	void rva00ADAFA0();
};
void __cdecl rva00ACBC50(Rva006CC4A0 *, int);
class Rva006CD6C0SizedDeleting
{
public:
	virtual ~Rva006CD6C0SizedDeleting();
};
class Rva006DB270
{
public:
	unsigned char m_pad[0x14];
	int m_14;
	int m_18;
};
extern Rva006DB270 *g_pChainBlockAllocator;
class Rva006D2A60
{
public:
	unsigned char m_pad[0x14];
	int m_14;
	int m_18;
};
extern Rva006D2A60 *g_00E176F4;
extern const char g_00CE8D70[];
extern const char g_00CE92C8[];
extern const char g_00CE92A0[];
extern const char g_00CE9280[];
extern const char g_00CE9228[];
extern const char g_00CE9208[];
extern const char g_00CE91D8[];
void __cdecl Rva006CDF60Shutdown()
{
	if (g_bfmeAptInitAtE17700) {
		g_bfmeAptAssertAtE17734(g_00CE92C8, g_00CE8D70, 0x29A);
		if (g_bfmeAptBreakOnAssertAtDDC01C) {
			__asm int 3
		}
	}
	Rva006CC110Log(0, g_00CE92A0);
	Rva006CC110Log(0, g_00CE9280, g_pChainBlockAllocator->m_18);
	if (g_pChainBlockAllocator->m_14)
		Rva006CC110Log(0, g_00CE9228, g_pChainBlockAllocator->m_14);
	Rva006CC110Log(0, g_00CE9208, ((DOGMA_PoolManager *)g_pChainBlockAllocator)->GetTotalBytesUsed());
	Rva006CC110Log(0, g_00CE91D8);
	int m18 = g_00E176F4->m_18;
	Rva006CC110Log(0, g_00CE9280, m18);
	if (g_00E176F4->m_14)
		Rva006CC110Log(0, g_00CE9228, g_00E176F4->m_14);
	Rva006CC110Log(0, g_00CE9208, ((DOGMA_PoolManager *)g_00E176F4)->GetTotalBytesUsed());
	Rva006CC4A0 *p1 = (Rva006CC4A0 *)g_pChainBlockAllocator;
	if (p1) {
		p1->rva00ADAFA0();
		rva00ACBC50(p1, 0x1C);
	}
	Rva006CD6C0SizedDeleting *p2 = (Rva006CD6C0SizedDeleting *)g_00E176F4;
	if (p2) {
		p2->Rva006CD6C0SizedDeleting::~Rva006CD6C0SizedDeleting();
		g_bfmeAptFreeSizeAtE17730(p2, 0x1C);
	}
}
