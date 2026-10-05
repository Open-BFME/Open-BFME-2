// ?VerifyDelayedFreeFill@GeneralAllocatorDebug@@QAE_NPAX@Z
// partial score=0.99 date=2026-10-05
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
//
// Two branch OPCAODES, not just their displacements, are source-visible:
//
//   * The header test must be spelled as a sign-bit test on the raw dword
//     (`!(header & (int)0x80000000)`) rather than as `header >= 0`. Both are
//     the same predicate, but MSVC7 lowers `header >= 0` on a SIGNED int to
//     `jl` (7c) while retail branches on the sign, `js` (78). Only the explicit
//     sign-bit spelling produces 78.
//   * The body-start compare must be a plain pointer compare
//     (`bodyStart >= run`), not the cast-to-int form `((int)bodyStart >=
//     (int)run)`. The casts make the comparison signed and MSVC7 emits `jl`
//     (7c) where retail compares the two addresses as UNSIGNED and emits `jb`
//     (72). The same header-and-flag reading rules out the other two
//     possibilities: a sub eax,esi / jae form would compare run against bodyStart
//     and fail on the equal case, and `test`/`sbb`-based forms are longer.

// 0x00030E20: the CRT's internal aligned-fill memset, cdecl, three stack
// arguments, returns the destination or null. It is not the CRT import thunk
// at 0x006291AE, so it is pinned under an address-derived name. Declared to
// return unsigned char rather than a pointer: the body only ever tests the
// result, and that is what makes retail's `test al,al` a byte test instead of
// the dword test a pointer declaration produces.
unsigned char __cdecl rva00030E20Fill(void *dst, unsigned int count, unsigned char c);

// 0x006C2FB0: the shared verify-guard report helper, also reached from
// VerifyGuardFill at 0x006C3020. Spelled as a thiscall MEMBER of the allocator,
// the reverse/symbols.csv pin, and declared inside the class below.
//
// Both arguments are cleaned by the CALLEE: retail's call site is
// `push 0x008E7C3C / push ebx / mov ecx,edi / call 0x006C2FB0` with no add
// afterward. For a thiscall member the message is the FIRST stack argument and
// the block the second, so the compiler pushes the message and then the block --
// which is retail's order -- and loads ecx from the allocator immediately before
// the call. A free __cdecl spelling gets the same push order only by declaring
// the message LAST, and then necessarily emits the trailing `add esp,8` that
// retail does not have: that add was the one byte this body was always over.
//
// The callee's own 97-byte body opens `mov edx,[esp+8]`, reading its first
// stack argument, so that argument is the message and the second is the block.

class GeneralAllocatorDebug
{
public:
	// 0x00032A20: thiscall, one stack argument, returns the usable block size.
	// Body rowed as ?rva00032A20@GeneralAllocator@Allocator@EA@@QAEIPBX@Z in
	// Code/GameEngine/Source/Common/System/memory_pool.cpp. Retail passes the
	// debug allocator object itself in ecx, so it is declared as a member of
	// this class rather than of the EA allocator it was recovered under.
	unsigned int GetBlockSize(const void *block);

	// 0x006C2FB0 as a thiscall MEMBER, the spelling reverse/symbols.csv already
	// pins (?). Retail's own call site is `push 0x008E7C3C / push ebx / mov
	// ecx,edi / call` with NO add esp,8, so the callee cleans its two stack
	// arguments; for a thiscall member the message is the FIRST stack argument
	// and the block the second, and the compiler pushes the message first --
	// which is retail's order -- then loads ecx with this and never emits an
	// add. The free __cdecl spelling above gets the push order only by putting
	// the message LAST, which necessarily costs the trailing add.
	void rva006C2FB0Report(const char *msg, void *block);

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

	// Spelled as an explicit sign-bit test rather than as `header >= 0`.
	// MSVC7 folds `header >= 0` into a `jl` because the value is SIGNED, but
	// retail branches on the SIGN (`78`, js). Reading the header as unsigned and
	// testing bit 31 directly keeps the same predicate while letting the
	// compiler emit the sign branch.
	if (!(header & (int)0x80000000)) {
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
		// Likewise a plain pointer compare, not the cast-to-int form: the cast
		// makes MSVC branch on `jl`, while retail branches on `rb` (72, jb)
		// because it compares the addresses as unsigned.
		if (bodyStart >= run)
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
		//
		// The count is spelled as a SIGNED pointer difference. That is what puts
		// retail's `mov ecx,[edi+0x540]` -- the load of the run kind -- after the
		// `sub eax,esi` and before the argument pushes: with an unsigned count the
		// whole expression is evaluated first and the compiler sinks the fill byte
		// and the count ahead of the run-kind test that selects the fill start.
		unsigned char *end = run + length;
		run += 8;
		if (m_runKind == 3)
			run += 4;

		if (rva00030E20Fill(run, end - run, (unsigned char)m_fillByte) == 0) {
			// Message first and block second: for a thiscall member the message is
			// the first stack argument, so the compiler pushes the message and then
			// the block, which is retail's order, and loads ecx from the allocator
			// immediately before the call with no add afterward.
			rva006C2FB0Report(
				"GeneralAllocatorDebug::VerifyDelayedFreeFill failure.", block);
			return false;
		}
	}

	return true;
}