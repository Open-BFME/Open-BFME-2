// ?VerifyGuardFill@GeneralAllocatorDebug@@QAE_NPAXHE@Z
// cl: /DNDEBUG /MD
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
//
// Two corrections the banked attempts carried, both established from retail
// bytes rather than inferred:
//
//   * The failure path RETURNS FALSE. Retail's report call at +0xA7 is followed
//     by `pop esi / pop edi / xor al,al / pop ebp / ret 0xC` -- a third exit,
//     eight bytes, with no shared epilogue. Every bank fell out of the report
//     into one `return true` at the end, which is why none of them emitted those
//     bytes and all of them came up 7-8 short of retail's 156. That is also what
//     makes retail's gate branch `je +7` over an INLINE early return rather than
//     `jne` to a relocated one at the function end: with the early return
//     spelled literally, MSVC7 reproduces both.
//   * The beyond-the-guard limit is the END OF THE CALLER'S BLOCK (block+0x10),
//     not a field of the allocator. Retail forms it with `lea edx,[esi+8]` and
//     esi holds `lea esi,[ebp+8]`, the run block. Two banks read `this+0x10`
//     because they took edi for the run block; the rowed, byte-verified MASM
//     sibling at 0x006C3180 spells the same limit as `lea edx,[edi+8]` with
//     edi holding `lea [ebp+8]` -- the same block+0x10 value.

// 0x00030E20: the CRT's internal aligned-fill memset, cdecl, three stack
// arguments. Declared to return unsigned char because the body only tests the
// result, and retail does that with a byte test (test al,al) rather than the
// dword test a pointer declaration produces.
unsigned char __cdecl rva00030E20Fill(void *dst, unsigned int count, unsigned char c);

// The report sink 0x006C2FB0 is the rowed Rva006C2D20Sink::rva006C2FB0
// (Rva006C2FB0Finish.cpp); (block, message) map to its two pointer arguments.
class Rva006C2D20Sink
{
public:
	void rva006C2FB0(const char *text, const char *extra);
};

class GeneralAllocatorDebug
{
public:
	// 0x006C25F0: thiscall with six stack arguments (ret 0x18), builds the guard
	// run and returns it in eax while writing the run length through outLen.
	// Unnamed body; the spelling is address-derived.
	//
	// Retail's push sequence is (0, &outLen, 0, 0, 0xB, runBlock), which is the
	// reverse of the declaration order because a thiscall member's stack arguments
	// are pushed right to left exactly as cdecl pushes them. The out length is
	// therefore the FIFTH declared argument, and that is what puts its frame slot
	// at [esp+0x18] for the read-back after the call.
	//
	// Both this caller and the MASM sibling at 0x006C3180 push six
	// arguments. The now-rowed provider's native RET18 and argument accesses
	// confirm this declaration; the old seven-argument claim was incorrect.
	void *rva006C25F0Run6(void *runBlock, int kind, int zero3, int zero2,
	                      unsigned int *outLen, int zero1);

	// 0x006C2FB0 as a thiscall MEMBER, the calling convention reverse/symbols.csv
	// pins. Retail's call site is `push 0x008E7C0C / push ebp / mov ecx,edi /
	// call` with no add afterward, so the callee cleans both stack arguments and
	// the LAST push is the FIRST stack argument -- which the callee's own
	// `mov edx,[esp+8]` confirms is the message.
	//
	// MSVC7 pushes a thiscall member's stack arguments right to left, exactly as
	// it does for cdecl, so the DECLARATION has to be (block, message) to push
	// the message first. Every bank so far declared (message, block) and emitted
	// `push ebp / push 0x008E7C0C`. The free __cdecl spelling gets the push
	// order right only by declaring the message last, and then necessarily costs
	// the trailing add esp,8 that retail does not have.
	void rva006C2FB0Report(void *block, const char *msg);

	unsigned int GetBlockSize(const void *block);

	bool VerifyGuardFill(void *block, int alsoBeyond, unsigned char mode);
	bool VerifyDelayedFreeFill(void *block);

	unsigned char m_unaccessed[0x509];
	unsigned char m_fillByte;        // +0x509
	unsigned char m_unaccessed50a;
	unsigned char m_guardFillByte; // +0x50b
	unsigned char m_unaccessed50c[8];
	unsigned int m_guardFlags;     // +0x514
	unsigned char m_unaccessed518[0x540-0x518];
	unsigned int m_runKind;        // +0x540
};

bool GeneralAllocatorDebug::VerifyGuardFill(void *block, int alsoBeyond,
                                            unsigned char mode)
{
	// The caller's block. Retail keeps it in ebp and forms the flag byte at
	// block+4 and the run block at block+8 from it. The beyond-the-guard limit
	// is also derived from it -- see the note at its use below.
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
	unsigned char flags = *(unsigned char *)((char *)callerBlock + 4);
	const unsigned char beyond = (unsigned char)alsoBeyond;

	if ((flags & 4) != 0) {
		return true;
	}
	{
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
				(unsigned char *)rva006C25F0Run6(runBlock, 0xB, 0, 0, outLen, 0);

			if (built) {
				unsigned int gotLen = *outLen;
				unsigned int span = gotLen < 0x40 ? gotLen : 0x40;
				span += (unsigned int)built;

				if (beyond != 0) {
					// The limit is the END OF THE CALLER'S BLOCK, not a field of the
					// allocator. Retail forms it with `lea edx,[esi+8]` at +0x7D, and
					// at that point esi holds the run block -- `lea esi,[ebp+8]` at
					// +0x56 -- so the limit is block+0x10.
					//
					// Two banks read this as a field of the allocator (`this+0x10`)
					// because they took edi for the run block. It is not: edi holds
					// `this` in this body and is what the fill byte at +0x50B is read
					// through. The rowed sibling 0x006C3180 settles it -- the same
					// limit there is `lea edx,[edi+8]` with edi holding `lea
					// [ebp+8]`, the same block+0x10 value, and that body is matched
					// and byte-verified.
					//
					// The `cmp eax,edx / jae skip / mov eax,edx` shape is a RAISE of
					// `built` to that limit, applied only when built is still below it.
					unsigned char *builtin = runBlock + 8;
					if (built < builtin)
						built = builtin;
				}

				span -= (unsigned int)built;

				if (rva00030E20Fill(built, span, m_guardFillByte) == 0) {
					// The declaration above takes (block, message) precisely so that
					// this call pushes the message first, which is retail's order.
					((Rva006C2D20Sink *)this)->rva006C2FB0(
						(const char *)callerBlock, "GeneralAllocatorDebug::VerifyGuardFill failure.");
					// Retail's third exit: the report is followed immediately by
					// `pop esi / pop edi / xor al,al / pop ebp / ret 0xC`, so the
					// verification FAILS rather than reporting and passing on. Every
					// bank so far fell out of the report into the single shared
					// `return true`, which is why none of them emitted those eight
					// bytes and all of them came up 7-8 short.
					return false;
				}
			}
		}
	}

	return true;
}
// ?VerifyDelayedFreeFill@GeneralAllocatorDebug@@QAE_NPAX@Z @0x006C30C0
// Native6C30C0..6C315B RET4. Its own failure literal establishes the name.
// A single shared fallback call avoids the ECX-before-push cross-jumped shape.
bool GeneralAllocatorDebug::VerifyDelayedFreeFill(void *block)
{
	unsigned char *run = (unsigned char *)block + 8;
	// Separate the run alias from the block header read to preserve retail's prologue.
	unsigned char *run2 = run;
	int header = *(int *)((char *)run2 - 4);
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
		if (bodyStart >= run) {
			length -= (unsigned int)run;
			goto haveLength;
		}
	}
	length = GetBlockSize(run);
haveLength:

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
			// The declaration above takes (block, message) precisely so that this
			// call pushes the message first: MSVC7 pushes a member's stack
			// arguments right to left, loads ecx from the allocator immediately
			// before the call, and emits no add afterward.
			((Rva006C2D20Sink *)this)->rva006C2FB0(
				(const char *)block, "GeneralAllocatorDebug::VerifyDelayedFreeFill failure.");
			return false;
		}
	}

	return true;
}