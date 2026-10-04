// ?VerifyGuardFill@GeneralAllocatorDebug@@QAE_NPAXHE@Z
// partial score=0.85 date=2026-10-04
// cl: /O2 /DNDEBUG /MD
// ?VerifyGuardFill@GeneralAllocatorDebug@@QAE_NPAXPAXE@Z @ 0x006C3020 (156B).
//
// The sibling of VerifyDelayedFreeFill at 0x006C30C0 and named the same way:
// this body carries its own retail failure string
// "GeneralAllocatorDebug::VerifyGuardFill failure." at 0x00CE7C0C and reports
// through the same unnamed helper 0x006C2FB0, so the class and method names are
// retail's own rather than address-derived.
//
// The guard path differs from the delayed-free path in three measurable ways:
// the caller block's flag byte at block+4 is tested for bit 2 first (set means
// the block needs no guard, so the verifier passes immediately), the fill start
// comes from the unrowed run builder 0x006C25F0 capped at 0x40 rather than from
// a run the caller already holds, and the fill byte is this+0x50B (the guard
// fill) rather than this+0x509 (the delayed-free fill).
//
// The 0x006C25F0 out parameter is an unsigned length the builder writes into the
// caller's frame; the guard run itself is returned in eax. A nonzero second
// argument means "also cover the 8 bytes past the guard", which is where the
// clamp `eax = block + 8` comes from.

void *__cdecl rva00030E20Fill(void *dst, unsigned int count, unsigned char c);

// 0x006C2FB0: the shared verify-guard report helper, also used by
// VerifyDelayedFreeFill at 0x006C30C0. Unnamed body; address-derived here.
void rva006C2FB0Report(const char *what, void *block);

class GeneralAllocatorDebug
{
public:
	bool VerifyGuardFill(void *block, int alsoBeyond, unsigned char mode);

	// 0x006C25F0: thiscall with six stack arguments (ret 0x18), builds the guard
	// run and returns it in eax while writing the run length through outLen.
	// Unnamed body; the spelling is address-derived. Retail pushes its five
	// stack arguments as (kind, 0, 0, outLen, runBlock), which is the reverse
	// of this declaration order -- cdecl pushes the last argument first.
	void *rva006C25F0(int kind, int a, int b, unsigned int *outLen,
	                  void *runBlock);

	unsigned char m_unaccessed[0x50b];
	unsigned char m_guardFillByte; // +0x50b
	unsigned char m_unaccessed50c[8];
	unsigned int m_guardFlags;     // +0x514
};

// ?VerifyGuardFill@GeneralAllocatorDebug@@QAE_NPAXHE@Z @ 0x006C3020 (156B)
// Retail keeps the caller block in ebp: three stack arguments plus this exhaust
// the argument slots once 0x006C25F0's five arguments are pushed, so the block
// pointer has to live in a callee-saved register across that call.
//
// Retail's own epilogue is the two bytes `pop ebp / ret 0xC` with no register
// restores at all: it restores edi on each exit path individually and never
// needs esi, so MSVC is given no callee-saved register to preserve by writing
// the body as a single `return`.
bool GeneralAllocatorDebug::VerifyGuardFill(void *block, int alsoBeyond, unsigned char mode)
{
	void *const callerBlock = block;

	if (*(unsigned char *)((char *)callerBlock + 4) & 4)
		return true;

	if (!mode && !(m_guardFlags & 8)) {
		unsigned char *const run = (unsigned char *)callerBlock + 8;
		unsigned int len;

		void *built = rva006C25F0(0xB, 0, 0, &len, run);
		if (built) {
			unsigned char *fill = (unsigned char *)built;
			unsigned int span = len < 0x40 ? len : 0x40;
			span += (unsigned int)fill;
			if (alsoBeyond) {
				unsigned char *beyond = run + 8;
				if (fill < beyond)
					fill = beyond;
			}
			span -= (unsigned int)fill;

			if (!rva00030E20Fill(fill, span, (unsigned char)m_guardFillByte))
				rva006C2FB0Report("GeneralAllocatorDebug::VerifyGuardFill failure.", callerBlock);
		}
	}

	return true;
}
