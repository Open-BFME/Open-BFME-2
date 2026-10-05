// ?VerifyDelayedFreeFill@GeneralAllocatorDebug@@QAE_NPAX@Z
// partial score=0.99 date=2026-10-05
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
//
// Both fixes were isolated in a scratch TU under build/ with fourteen source
// shapes and eleven flag sets (/O1 /O2 /Ob0 /Ob1 /Ob2 /Od /Gr /Gs999999); none of
// those flag sets touches either branch, and neither does any of the shapes.
// Only the two predicate spellings move them.

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
// Its 97-byte body opens `mov edx,[esp+8]` -- it reads its first argument off
// the stack and never touches ecx -- copies the message into a 0x300 frame and
// ends `add esp,0x300; ret 8`, so the CALLER cleans both arguments.
// Its caller therefore stages the message first and never emits an add:
// `push 0x008E7C3C / push ebx / mov ecx,edi / call`. A thiscall member spelling
// reverses the two pushes -- cdecl pushes the last argument first, and for a
// thiscall member the message is the second stack argument -- which is what put
// a `push ebx` ahead of the string immediate in the earlier bank.
//
// Note the caller still loads ecx from the allocator immediately before the
// call. That is an ordinary use of `this` in the caller, not evidence that the
// callee is a member, and it is not evidence that the allocator object is
// passed: the helper reads both of its arguments off the stack and has no ECX
// parameter. The body below therefore calls it as a free function and lets it
// read that block argument off the stack, which is what removes the trailing
// `add esp,8` and holds the emitted body to retail's exact 155 bytes.
//
// reverse/symbols.csv currently pins this address as
// ?rva006C2FB0Report@GeneralAllocatorDebug@@QAEXPBDPAX@Z, a thiscall MEMBER with
// the message first. The callee's own `ret 8` disproves that spelling, and the
// address is claimed by nothing, so the free-cdecl name below is available.
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
			// Block first and message second, so the message is the LAST declared
			// argument and cdecl pushes it first -- which is retail's order.
			rva006C2FB0Report(block,
			                  "GeneralAllocatorDebug::VerifyDelayedFreeFill failure.");
			return false;
		}
	}

	return true;
}

// STILL OPEN, and measured again this round in the scratch TU: the +0x0B
// prologue order. Retail reserves THREE callee-saves -- ebx for the caller
// block, esi for the run, edi for `this` -- and emits the lea between the two
// saves. This body needs the same three registers but MSVC7 always sinks the
// `push edi / mov edi,ecx` pair to the head of the save group, ahead of the
// lea.
//
// Swept and rejected, all still `push esi / push edi / mov edi,ecx / lea`:
//
//   * Declaration order of the prologue locals: run first, header first, run
//     defined only inside the arms, and a const pointer alias. All four keep
//     the same order; none of them moves the lea.
//   * Every flag set: -O1 (drops the frame, 146B), -O1 -Ob0, -O1 -Ob2,
//     -O2 -Ob0, -O2 -Ob1, -O2 -Od, -O2 -Gr, -O1 -Gr, and -Gs999999 at both
//     levels. None touches the save order.
//   * Giving the two callees real bodies so they can be inlined, versus leaving
//     them extern: no change, so the ordering is not an artefact of the probe.
//   * A local `saved` for the run kind written before the branch and consumed
//     after the fill, and the same local read into the fill's third argument:
//     no change.
//
// One shape DOES change the allocation, and it points at what retail actually
// did: spelling the report call as a MEMBER of the allocator (`reportHere(block)`
// rather than the free cdecl helper) drops edi entirely and puts `this` on
// ebp instead -- `push ebx / push ebp / mov ebp,[esp+0xc] / mov eax,[esp+4]`.
// That is the 0x006C3020 sibling's prologue, not this body's: it costs an extra
// saved register, pushes `block` to [esp+0xc], and makes the header load read
// [esp+4] instead of [ebx+4]. So the member spelling trades this body's
// prologue for the sibling's and is not the answer here.
//
// What retail must therefore have been doing is keeping `this` live across
// exactly two side-effecting calls while never folding it into an argument --
// which is why its frame is ebx/esi/edi rather than ebp/esi. Nothing in the
// source that keeps those three registers reproduces that schedule.