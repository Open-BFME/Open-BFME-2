// ?VerifyDelayedFreeFill@GeneralAllocatorDebug@@QAE_NPAX@Z
// partial score=0.98 date=2026-10-05
// ?VerifyDelayedFreeFill@GeneralAllocatorDebug@@QAE_NPAX@Z
// partial score=0.98 date=2026-10-04
// ?VerifyDelayedFreeFill@GeneralAllocatorDebug@@QAE_NPAX@Z
// cl: /O2 /DNDEBUG /MD
// The delayed-free guard verifier of GeneralAllocatorDebug, at retail
// 0x006C30C0 (155 bytes). The sibling of VerifyGuardFill at 0x006C3020.
//
// Class and method names are retail's own: this body carries its own failure
// string "GeneralAllocatorDebug::VerifyDelayedFreeFill failure." at 0x008E7C3C
// (0x00CE7C3C with the image base), and the sibling carries the matching
// VerifyGuardFill string at 0x008E7C0C.
//
// The run layout is the one the rowed reader Rva006C1FE0 establishes: a two
// byte length word sits in the last two bytes of the run and the body begins
// that many bytes earlier. The length this body needs is recovered by that
// rule from the caller's block header, falling back to the EA PPMalloc
// GetBlockSize 0x00032A20 both when the header dword is negative and when the
// recovered start would land below the run. The header dword at block+4 is
// masked exactly the way the rowed allocator 0x006C3940 masks it: bit 2
// selects between the header value alone and header+4.
//
// The fill start is run+8, or run+12 when the run kind at this+0x540 is 3, and
// the fill byte is the delayed-free fill at this+0x509. The run is capped at
// 0x100 bytes, and anything of 8 bytes or less needs no check.

// 0x00030E20: the CRT's internal aligned-fill memset, cdecl, three stack
// arguments, returns the destination or null. It is not the CRT import thunk
// at 0x006291AE, so it is pinned under an address-derived name. Declared to
// return unsigned char rather than a pointer: the body only ever tests the
// result, and that is what makes retail's `test al,al` a byte test instead of
// the dword test a pointer declaration produces.
unsigned char __cdecl rva00030E20Fill(void *dst, unsigned int count, unsigned char c);

// 0x006C2FB0: cdecl, two stack arguments (block, message), both cleaned by the
// CALLER. The shared verify-guard report helper, also reached from
// VerifyGuardFill at 0x006C3020.
//
// It is a FREE function, not a member of the allocator, and that is the fact
// this body's epilogue turns on. Retail's own 97-byte body at 0x006C2FB0
// opens `mov edx,[esp+8]` -- it reads its first argument off the stack and
// never touches ecx -- copies the message into a 0x300 frame and ends
// `add esp,0x300; ret` with a PLAIN ret, so it does not clean its arguments.
// Its caller therefore stages the message first and never emits an add:
// `push 0x008E7C3C / push ebx / mov ecx,edi / call`. A thiscall member spelling
// reverses the two pushes -- cdecl pushes the last argument first, and for a
// thiscall member the message is the second stack argument -- which is what put
// a `push ebx` ahead of the string immediate in the earlier bank.
//
// Note the caller still loads ecx from the allocator immediately before the
// call. That is an ordinary use of `this` in the caller, not evidence that the
// callee is a member: 0x006C2FB0's own body disproves it.
void __cdecl rva006C2FB0Report(void *block, const char *msg);

class GeneralAllocatorDebug
{
public:
	// 0x00032A20: thiscall, one stack argument, returns the usable block size.
	// Body rowed as ?rva00032A20@GeneralAllocator@Allocator@EA@@QAEIPBX@Z in
	// Code/GameEngine/Source/Common/System/memory_pool.cpp. Retail passes the
	// debug allocator object itself in ecx, so it is declared as a member of
	// this class rather than of the EA allocator it was recovered under.
	unsigned int GetBlockSize(const void *block);

	bool VerifyDelayedFreeFill(void *block);

	unsigned char m_unaccessed[0x509];
	unsigned char m_fillByte;        // +0x509
	unsigned char m_unaccessed50a;
	unsigned char m_guardFillByte;   // +0x50b, the sibling's fill byte
	unsigned char m_unaccessed50c[4];
	unsigned int m_blockKind;        // +0x510
	unsigned char m_unaccessed514[0x2c];
	unsigned int m_runKind;          // +0x540
};

// ?VerifyDelayedFreeFill@GeneralAllocatorDebug@@QAE_NPAX@Z @ 0x006C30C0 (155B)
bool GeneralAllocatorDebug::VerifyDelayedFreeFill(void *block)
{
	unsigned char *run = (unsigned char *)block + 8;
	int header = *(int *)((char *)block + 4);
	unsigned int length;

	if (!(header < 0)) {
		unsigned int span;
		// Spelled as a negated test rather than as `header & 2 ? a : b`:
		// retail jumps OVER the header+4 arm and falls into the masked value
		// alone, which is the opposite of what the positive spelling lays out.
		if (!(header & 2))
			span = ((unsigned int)header & 0x7FFFFFF8u) + 4;
		else
			span = (unsigned int)header & 0x7FFFFFF8u;

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

	// Nesting the fill rather than returning early keeps the argument group
	// from being duplicated into both arms, and leaves the success epilogue at
	// one site, which is where retail puts it.
	if (length > 8) {
		if (length >= 0x100)
			length = 0x100;

		// Retail mutates the run pointer in place: end = run + length, then the
		// fill start becomes run + 8 (or run + 12 when the run kind is 3), and
		// the count is end minus that. Keeping one pointer variable is what
		// reproduces both the add and the later sub in the same register.
		unsigned char *end = run + length;
		run += 8;
		if (m_runKind == 3)
			run += 4;

		if (rva00030E20Fill(run, (unsigned int)end - (unsigned int)run,
		                   (unsigned char)m_fillByte) == 0) {
			// Block first and message second, so the message is the LAST declared
			// argument and cdecl pushes it first -- which is retail's order.
			rva006C2FB0Report(block,
			                  "GeneralAllocatorDebug::VerifyDelayedFreeFill failure.");
			return false;
		}
	}

	return true;
}