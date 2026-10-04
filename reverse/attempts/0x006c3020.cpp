// ?VerifyGuardFill@GeneralAllocatorDebug@@QAE_NPAXHE@Z
// partial score=0.92 date=2026-10-04
// ?VerifyGuardFill@GeneralAllocatorDebug@@QAE_NPAXHE@Z
// cl: /O2 /DNDEBUG /MD
// The guard verifier of GeneralAllocatorDebug, at retail 0x006C3020 (156
// bytes). The sibling of VerifyDelayedFreeFill at 0x006C30C0, and named the
// same way: this body carries its own retail failure string
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
// The 0x006C25F0 out parameter is an unsigned length the builder writes through
// a pointer into the caller's own frame; the guard run itself is returned in
// eax. A nonzero second argument means "also cover the 8 bytes past the guard",
// which is where the clamp against block + 16 comes from.

// 0x00030E20: the CRT's internal aligned-fill memset, cdecl, three stack
// arguments. Declared to return unsigned char because the body only tests the
// result, and retail does that with a byte test (test al,al) rather than the
// dword test a pointer declaration produces.
unsigned char __cdecl rva00030E20Fill(void *dst, unsigned int count, unsigned char c);

class GeneralAllocatorDebug
{
public:
	// 0x006C25F0: thiscall with six stack arguments (ret 0x18), builds the guard
	// run and returns it in eax while writing the run length through outLen.
	// Unnamed body; the spelling is address-derived.
	//
	// Retail's push sequence is (0, &outLen, 0, 0, 0xB, runBlock), which is
	// the reverse of this declaration order because cdecl pushes the last
	// argument first. The out length is the fourth declared argument, which is
	// what puts its frame slot at [esp+0x18] for the read-back after the call.
	void *rva006C25F0Run(void *runBlock, int kind, unsigned int zero3,
	                     unsigned int zero2, unsigned int *outLen, int zero1);

	// 0x006C2FB0: thiscall, two stack arguments (message, block) cleaned by the
	// callee. The shared verify-guard report helper, also reached from
	// VerifyDelayedFreeFill at 0x006C30C0, which is where the thiscall
	// spelling was proved: retail loads ecx from the allocator object
	// immediately before the call and never emits an add esp,8.
	void rva006C2FB0Report(const char *what, void *block);

	unsigned int GetBlockSize(const void *block);

	bool VerifyGuardFill(void *block, int alsoBeyond, unsigned char mode);

	unsigned char m_unaccessed[0x50b];
	unsigned char m_guardFillByte; // +0x50b
	unsigned char m_unaccessed50c[8];
	unsigned int m_guardFlags;     // +0x514
};

// ?VerifyGuardFill@GeneralAllocatorDebug@@QAE_NPAXHE@Z @ 0x006C3020 (156B)
bool GeneralAllocatorDebug::VerifyGuardFill(void *block, int alsoBeyond,
                                            unsigned char mode)
{
	void *const callerBlock = block;

	if (*(unsigned char *)((char *)callerBlock + 4) & 4)
		return true;

	// Retail reads the flags dword and tests bit 3 of its HIGH byte, which is
	// why the test is written against a shifted dword rather than against a
	// narrowed field: the narrow spelling emits the byte test the body does not
	// have. The polarity is inverted relative to the delayed-free sibling --
	// a clear bit 3 means the run needs no check, so the body returns true.
	if (mode || !(((this->m_guardFlags >> 8) & 8) == 0)) {
		unsigned int len;
		unsigned int *outLen = &len;
		void *runBlock = (char *)callerBlock + 8;
		unsigned char *built =
			(unsigned char *)rva006C25F0Run(runBlock, 0xB, 0, 0, outLen, 0);

		if (built) {
			unsigned int gotLen = *outLen;
			unsigned int span = gotLen < 0x40 ? gotLen : 0x40;
			span += (unsigned int)built;

			if (alsoBeyond) {
				unsigned char *beyond = (unsigned char *)callerBlock + 16;
				if (built >= beyond)
					built = beyond;
			}

			span -= (unsigned int)built;

			if (rva00030E20Fill(built, span, m_guardFillByte) == 0)
				rva006C2FB0Report("GeneralAllocatorDebug::VerifyGuardFill failure.", block);
		}
	}

	return true;
}