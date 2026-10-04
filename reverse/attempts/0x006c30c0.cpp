// ?VerifyDelayedFreeFill@GeneralAllocatorDebug@@QAE_NPAX@Z
// partial score=0.9 date=2026-10-04
// cl: /O2 /DNDEBUG /MD
// The two guard verifiers of GeneralAllocatorDebug. Both carry their own retail
// failure string, so the class and method names are retail's own:
//   0x006C30C0 -> "GeneralAllocatorDebug::VerifyDelayedFreeFill failure."
//   0x006C3020 -> "GeneralAllocatorDebug::VerifyGuardFill failure."
// Both hand the failing block to the shared report helper 0x006C2FB0 (the
// address-derived verify-guard-dump) and both refill the run with the debug
// fill byte at this+0x509.
//
// The run layout is the one the rowed reader Rva006C1FE0 establishes: a two
// byte length word sits in the last two bytes of the run and the body begins
// that many bytes earlier. Both bodies recover a run length by that rule, and
// 0x006C30C0 falls back to the EA allocator's GetBlockSize 0x00032A20 when the
// header dword is negative. The block header dword at run-4 is masked exactly
// the way the rowed allocator 0x006C3940 masks it: bit 2 selects between the
// header value alone and header+4.

// 0x00030E20: the CRT's internal aligned-fill memset, cdecl, three stack
// arguments, returns the destination or null. It is not the CRT import thunk
// at 0x006291AE, so it is pinned under an address-derived name.
void *__cdecl rva00030E20Fill(void *dst, unsigned int count, unsigned char c);

// 0x00032A20: EA PPMalloc GetBlockSize, called with ecx = this and one stack
// argument. Named from reverse/symbols.csv, where the caller _GetBlockSize
// note records it. Declared as a GeneralAllocatorDebug member because retail
// passes the debug allocator object itself in ecx.

// 0x006C2FB0: thiscall, two stack arguments (message, block); the shared
// verify-guard report helper that formats the block and asserts. Its body is
// unnamed, so the spelling here is address-derived.
void rva006C2FB0Report(const char *what, void *block);

// 0x006C25F0: thiscall, four stack arguments; the guard-run builder VerifyGuardFill
// calls to obtain the run it is about to check. Body unnamed, address-derived.
void *rva006C25F0(void *a, int b, int c, int kind, void *fillBlock);

class GeneralAllocatorDebug
{
public:
	unsigned int GetBlockSize(const void *block);

	bool VerifyDelayedFreeFill(void *block);

	unsigned char m_unaccessed[0x509];
	unsigned char m_fillByte;        // +0x509
	unsigned char m_unaccessed50a;
	unsigned char m_guardFillByte;   // +0x50b
	unsigned char m_unaccessed50c[4];
	unsigned int m_blockKind;        // +0x510
	unsigned char m_unaccessed514[0x2c];
	unsigned int m_runKind;          // +0x540
};

// ?VerifyDelayedFreeFill@GeneralAllocatorDebug@@QAEPAX@Z @ 0x006C30C0 (155B)
bool GeneralAllocatorDebug::VerifyDelayedFreeFill(void *block)
{
	unsigned char *run = (unsigned char *)block + 8;
	int header = *(int *)((char *)block + 4);
	unsigned int length;

	if (!(header < 0)) {
		unsigned int span = header & 2 ? (unsigned int)header & 0x7FFFFFF8u
		                               : ((unsigned int)header & 0x7FFFFFF8u) + 4;
		unsigned char *word = run + span - 10;
		unsigned char *bodyStart = word - *(unsigned short *)word;
		length = (unsigned int)bodyStart;
		if (length >= (unsigned int)run)
			length -= (unsigned int)run;
		else
			length = GetBlockSize(run);
	} else {
		length = GetBlockSize(run);
	}

	if (length <= 8)
		return true;
	if (length >= 0x100)
		length = 0x100;

	// Retail mutates the run pointer in place: end = run + length, then the
	// fill start becomes run + 8 (or run + 12 when the run kind is 3), and the
	// count is end minus that. Keeping one pointer variable is what reproduces
	// both the add and the later lea in the same register.
	unsigned char *end = run + length;
	run += 8;
	if (m_runKind == 3)
		run += 4;


	unsigned char *filled = (unsigned char *)rva00030E20Fill(
		run, (unsigned int)end - (unsigned int)run, (unsigned char)m_fillByte);
	if (filled)
		return true;

	rva006C2FB0Report("GeneralAllocatorDebug::VerifyDelayedFreeFill failure.", block);
	return false;
}