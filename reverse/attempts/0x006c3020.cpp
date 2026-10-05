// ?VerifyGuardFill@GeneralAllocatorDebug@@QAE_NPAXHE@Z
// partial score=0.98 date=2026-10-05
// ?VerifyGuardFill@GeneralAllocatorDebug@@QAE_NPAXHE@Z
// cl: /O2 /DNDEBUG /MD
// The guard verifier of GeneralAllocatorDebug, at retail 0x006C3020 (156
// bytes). The sibling of VerifyDelayedFreeFill at 0x006C30C0, and named the
// same way: this body carries its own retail failure string
// "GeneralAllocatorDebug::VerifyGuardFill failure." at 0x008E7C0C and reports
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
// eax. A nonzero `mode` argument means "also cover the 8 bytes past the guard",
// which is where the clamp against the run block + 8 comes from.

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
	// Retail's push sequence is (0, &outLen, 0, 0, 0xB, runBlock), which is the
	// reverse of the declaration order because cdecl pushes the last argument
	// first. The out length is the fourth declared argument, which is what puts
	// its frame slot at [esp+0x18] for the read-back after the call.
	void *rva006C25F0Run(void *runBlock, int kind, unsigned int zero3,
	                     unsigned int zero2, unsigned int *outLen, int zero1);

	// 0x006C2FB0 as a thiscall MEMBER, the spelling reverse/symbols.csv pins.
	// Retail's call site is `push 0x008E7C0C / push ebp / mov ecx,edi / call`
	// with no add afterward, so the callee cleans both stack arguments: for a
	// thiscall member the message is the FIRST stack argument and the block the
	// second, and the compiler then pushes the block and the message in retail's
	// order. The free __cdecl spelling gets the same push order only by
	// declaring the message last, and then necessarily emits the trailing
	// add esp,8 that retail does not have.
	void rva006C2FB0Report(const char *msg, void *block);

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
	// The caller's block. Retail keeps it in ebp and forms every derived address
	// from it -- the flag byte at block+4, the run block at block+8, and the
	// beyond-the-guard limit at run block + 8 -- so the clamp is a limit of the
	// CALLER's block and not of the allocator. Two earlier banks read retail's
	// `lea edx,[esi+8]` as `lea edx,[edi+0x10]` with edi holding `this` and moved
	// the limit onto the wrong object.
	void *callerBlock = block;

	// The flag byte is read into a named value and the bit compared with `!= 0`.
	// That pair is what produces retail's two-instruction test
	// `test BYTE PTR [ebp+4],4`. Neither the bare `& 4` nor the `== 0` spelling
	// does: MSVC7 rewrites those as `mov al,[ebp+4] / shr al,2 / test al,1`,
	// because it has already loaded the byte when it folds the bit into it.
	//
	// The result is held in a named bool that the whole work is nested under, and
	// that is what produces the `je` rather than the `jne` MSVC7 otherwise emits
	// here: with the work nested, the flag test branches forward over the body,
	// exactly as retail's `je 0x6c3035` does. The direct
	// `if (set) return true;` spelling instead relocates the early return to the
	// end of the function and branches to it with `jne`.
	const unsigned char flags = *(const unsigned char *)((const char *)callerBlock + 4);
	const bool needsGuard = (flags & 4) != 0;

	if (needsGuard) {
		// Retail reads the flags dword and tests bit 3 of its HIGH byte, which is
		// why the test is written against a shifted dword rather than against a
		// narrowed field: the narrow spelling emits the byte test the body does
		// not have. A clear bit 3 means the run needs no check, so the body
		// returns true -- and only a non-zero `mode` overrides that.
		if (mode || ((this->m_guardFlags >> 8) & 8)) {
			unsigned int len;
			unsigned int *outLen = &len;
			unsigned char *runBlock = (unsigned char *)callerBlock + 8;
			unsigned char *built =
				(unsigned char *)rva006C25F0Run(runBlock, 0xB, 0, 0, outLen, 0);

			if (built) {
				unsigned int gotLen = *outLen;
				unsigned int span = gotLen < 0x40 ? gotLen : 0x40;
				span += (unsigned int)built;

				if (alsoBeyond) {
					// RAISE built to the limit rather than lowering it: retail is
					// `cmp eax,edx / jae skip / mov eax,edx`, so it applies only
					// when built is still BELOW the limit.
					unsigned char *beyond = runBlock + 8;
					if (built < beyond)
						built = beyond;
				}

				span -= (unsigned int)built;

				if (rva00030E20Fill(built, span, m_guardFillByte) == 0)
					rva006C2FB0Report(
						"GeneralAllocatorDebug::VerifyGuardFill failure.", block);
			}
		}
	}

	return true;
}