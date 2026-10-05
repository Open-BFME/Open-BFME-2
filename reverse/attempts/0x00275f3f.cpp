// ?rva00275F3F@Rva00270BA8@@QAEXXZ
// partial score=0.95 date=2026-10-05
// ?rva00275F3F@Rva00270BA8@@QAEXXZ
// partial score=0.95 date=2026-10-05
// cl: /O1 /MD /EHsc
// ?rva00275F3F@Rva00270BA8@@QAEXXZ present-unmatched
// Retail 0x00275F3F, 220 bytes. Ghidra extent verified from the bytes:
// prev ends leave/ret, head is the EH-prolog mov/call pair, tail is the
// fs:[0] teardown + leave/ret, next starts with a fresh prologue.
//
// Same class as the rowed lazy getter ?rva00270BA8 (0x00270BA8, 49B): this
// body reads the same +0x354 slot, calls the same helper on itself five
// times, and calls ?rva0027006C (0x0027006C) on the slot. Extra members are
// read straight out of retail: flag block at +0xFC (byte flag at +0x1C8,
// tested against 0x44), ints at +0x460/+0x464/+0x46C.
//
// The +0x1C slot of Rva00270025 carries two spellings: the width/height
// calls resolve to the rowed Anim2D getters, the 4-int call to rowed
// 0x002D7127. Casts at the call sites only; zero bytes either way.
// The 0x34-byte raw allocation goes through scalar operator new (retail
// calls rowed ??2), and the 2-arg stdcall factory 0x002D6D63 is pinned in
// reverse/symbols.csv from this body's sole call site.

typedef unsigned int UnsignedInt;

class Anim2D
{
public:
	unsigned int getCurrentFrameWidth() const;
	unsigned int getCurrentFrameHeight() const;
};

class Rva002D7127
{
public:
	void rva002D7127(int a, int b, int c, int d);
};

class Rva00270025
{
public:
	void rva0027006C(int v);
public:
	void *m_pad00[7];
	void *m_1C;
};

struct Rva00270BA8FlagBlock
{
	unsigned char m_pad[0x1C8];
	unsigned char m_flags;
};

struct Rva002DFEB78
{
	unsigned int m_pad[6];
	unsigned int m_18;
};

extern unsigned int g_00DFF068;
extern Rva002DFEB78 *g_00DFEB78;

void *__cdecl operator new(unsigned int size);
extern "C" void *__stdcall rva002D6D63(unsigned int a, unsigned int b);

class Rva00270BA8
{
public:
	Rva00270025 *rva00270BA8();
	void rva00275F3F();
private:
	unsigned char m_pad00[0xFC];
	Rva00270BA8FlagBlock *m_flagBlock;
	unsigned char m_pad100[0x354 - 0x100];
	Rva00270025 *m_354;
	unsigned char m_pad358[0x460 - 0x358];
	int m_460;
	int m_464;
	int m_pad468;
	int m_46C;
};

void Rva00270BA8::rva00275F3F()
{
	if ((m_flagBlock->m_flags & 0x44) == 0)
	{
		if (m_354)
			m_354->rva0027006C(6);
	}
	else
	{
		if (rva00270BA8()->m_1C == 0)
		{
			unsigned char *buf = (unsigned char *)operator new(0x34);
			// The state transitions around the factory call (0 then -1)
			// are a try/catch with an empty handler; the EH prolog and
			// the homed allocation come with it. No named temps inside:
			// retail holds everything in registers (edi/ebx/eax).
			Anim2D *anim = 0;
			try
			{
				if (buf)
					anim = (Anim2D *)rva002D6D63(g_00DFF068, g_00DFEB78->m_18);
			}
			catch (...)
			{
			}
			rva00270BA8()->m_1C = anim;
		}
		int span = m_46C - m_464;
		int w = ((Anim2D *)rva00270BA8()->m_1C)->getCurrentFrameWidth();
		int h = ((Anim2D *)rva00270BA8()->m_1C)->getCurrentFrameHeight();
		((Rva002D7127 *)rva00270BA8()->m_1C)->rva002D7127(m_460, m_46C - h - span, w, h);
	}
}
