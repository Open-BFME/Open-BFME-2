// cl: /MD /EHsc
// ??1Rva006CBF40@@UAE@XZ @0x006E2A70 193B. AptCIH-derived teardown dtor.
//
// Evidence: assert string 0x00CEB8D8 "pNext == NULL && pPrev == NULL &&
// \"This should already be done!\"" at AptCIH.cpp line 0x7B; 0x00CEB4A8 is the
// AptCIH.cpp path. Member +0x44 is a 0x30-byte chain-block allocation freed
// through g_pChainBlockAllocator 0x00E176E8 / freeBlock 0x006DB270. Member +0x08
// is an EAStringC whose rowed dtor 0x006D3010 runs after the body; base dtor is
// the rowed Rva006DE350 at 0x006DE350; vtable 0x00CE8C24 (DIR32 auto-patch).
// The +0x50/+0x54 pair are pPrev/pNext and +0x5C the 0xC0000 flag word gated on
// 0x40000. The teardown helper 0x006E2690 is pinned ?rva006E2690@AptCIH@@QAEXH@Z
// (unrowed) and takes one int argument (retail pushes 0). nDepth check is
// followed by bfmeUnlinkNestedBE 0x006F7090.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class Rva006DB270
{
public:
	void freeBlock(void *block, int blockSize);
};

extern Rva006DB270 *g_pChainBlockAllocator; // 0x00E176E8

class BfmeNestedBE;
BfmeNestedBE *bfmeUnlinkNestedBE(BfmeNestedBE *node); // 0x006F7090

class EAStringC
{
public:
	~EAStringC();

private:
	void *m_data;
};

class Rva006DE350
{
public:
	virtual ~Rva006DE350();

private:
	unsigned int m_flags;
};

class AptCIH
{
public:
	void rva006E2690(int arg);
};

class Rva006CBF40 : public Rva006DE350
{
public:
	virtual ~Rva006CBF40();

private:
	EAStringC m_08;            // +0x08, rowed dtor 0x006D3010
	char m_pad0C[0x44 - 0x0C];
	void *m_44;                // +0x44, 0x30-byte chain block
	char m_pad48[0x50 - 0x48];
	void *m_50;                // +0x50, pPrev
	void *m_54;                // +0x54, pNext
	char m_pad58[0x5C - 0x58];
	int m_5C;                  // +0x5C, flag word
};

Rva006CBF40::~Rva006CBF40()
{
	if (m_44 != 0) {
		g_pChainBlockAllocator->freeBlock(m_44, 0x30);
		m_44 = 0;
	}
	((AptCIH *)this)->rva006E2690(0);
	if ((m_5C & 0xC0000) != 0x40000) {
		if (m_54 != 0 || m_50 != 0) {
			g_bfmeAptAssertAtE17734(
				"pNext == NULL && pPrev == NULL && \"This should already be done!\"",
				"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCIH.cpp", 0x7B);
			if (g_bfmeAptBreakOnAssertAtDDC01C)
				__debugbreak();
		}
		bfmeUnlinkNestedBE((BfmeNestedBE *)this);
	}
}
