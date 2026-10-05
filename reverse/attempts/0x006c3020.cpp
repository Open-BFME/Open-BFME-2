// ?VerifyGuardFill@GeneralAllocatorDebug@@QAE_NPAXHE@Z
// partial score=0.92 date=2026-10-05
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
// eax. A nonzero second argument means "also cover the 8 bytes past the guard",
// which is where the clamp against block + 16 comes from.

// 0x00030E20: the CRT's internal aligned-fill memset, cdecl, three stack
// arguments. Declared to return unsigned char because the body only tests the
// result, and retail does that with a byte test (test al,al) rather than the
// dword test a pointer declaration produces.
unsigned char __cdecl rva00030E20Fill(void *dst, unsigned int count, unsigned char c);

// 0x006C2FB0: the shared verify-guard report helper, also reached from
// VerifyDelayedFreeFill at 0x006C30C0.
//
// Its own 97-byte body reads the first argument off the stack (`mov edx,[esp+8]`)
// and returns with a plain ret, so it is a FREE cdecl function whose caller
// cleans both arguments -- not the thiscall member the 0.92 bank recorded. That
// is why the report pushes are in retail's order here: the block is the FIRST
// declared argument and the message the last, and cdecl pushes the last one
// first. The cost is a trailing `add esp,8` that retail does not have.
void __cdecl rva006C2FB0Report(void *block, const char *msg);

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

	unsigned int GetBlockSize(const void *block);

	// 0x006C2FB0 as a MEMBER of the allocator. The callee's own 97-byte body
	// ends with a plain `ret`, so it cleans nothing itself, but retail's call
	// site here also carries no `add esp,8` and does pass ecx -- so the member
	// spelling is the one that reproduces both, at the cost of the push order
	// (cdecl pushes the last declared argument first, and for thiscall the
	// message is the second stack argument). The free cdecl spelling gets the
	// push order right and costs an `add esp,8` plus 16 bytes.
	void rva006C2FB0Report(void *block, const char *msg);

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
				// The clamp limit is a field of the ALLOCATOR, not of the
				// caller's block: retail forms it with `lea edx,[edi+0x10]`
				// where edi holds `this`, while the caller's block is in ebp
				// and the run start is ebp+8. Spelling this against
				// callerBlock+16 (as an earlier bank did) addresses the wrong
				// object.
				unsigned char *beyond = (unsigned char *)this + 0x10;
				if (built >= beyond)
					built = beyond;
			}

			span -= (unsigned int)built;

			if (rva00030E20Fill(built, span, m_guardFillByte) == 0)
				rva006C2FB0Report(block,
				                  "GeneralAllocatorDebug::VerifyGuardFill failure.");
		}
	}

	return true;
}