// ?VerifyDelayedFreeFill@GeneralAllocatorDebug@@QAE_NPAX@Z
// partial score=0.995 date=2026-10-05
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
// Two sites resist, and both are REGISTER-ASSIGNMENT artefacts rather than
// anything source-visible. Measured by instruction-level comparison: 60 emitted
// instructions against retail's 60, 57 of them identical, the three at [42]
// [46] [49] identical once the obj's relocations are resolved against the
// externs they name. With the relocations masked the residue is NINE bytes in
// exactly two runs, and both are pure instruction order -- no opcode, operand,
// displacement or branch target differs anywhere else in the body:
//
//   +0x0B-+0x10   retail  8d 73 08 57 8b f9   (lea / push edi / mov edi,ecx)
//                 ours    57 8b f9 8d 73 08   (push edi / mov edi,ecx / lea)
//   +0x39-+0x3B   retail  56 8b cf            (push esi / mov ecx,edi)
//                 ours    8b cf 56            (mov ecx,edi / push esi)
//
// Both runs are the same length on both sides, which is what makes the body
// size-exact at 155 and the score 0.995.
//
// 1. Prologue (+0x0B). Retail saves esi, computes the run, THEN saves edi and
//    copies this:
//
//        push esi / lea esi,[ebx+8] / push edi / mov edi,ecx
//
//    MSVC7 emits both register saves as one block ahead of the address
//    computation:
//
//        push esi / push edi / mov edi,ecx / lea esi,[ebx+8]
//
//    Same instruction multiset, same order otherwise; only the lea is hoisted
//    past the save group. It is completely flag-invariant: -O1, -Od, -Ob0, -Ob1,
//    -Ob2, -Ox, -Ot, -Gs999999 and their combinations all emit the same three
//    instructions in the same order. -O1 additionally shortens the body to 146
//    bytes, so it cannot be retail's setting.
//
//    WHAT MOVES IT (measured in an isolated TU, one variant per compile).
//    The scheduler is not simply refusing to interpose -- it will interpose.
//    An ebx-rooted address computation is emitted in retail's slot as soon as
//    the prologue has a SECOND ebx-rooted address computation or a test or
//    compare that is not on eax. Six spellings each produce
//
//        push esi / lea esi,[ebx+8] / <test|cmp> / push edi / mov edi,ecx
//
//    namely `run != 0 &&` (85 f6), `run >= block &&` (3b f3),
//    `run != 8 &&` (83 fe 08), a second lea from ebx, a second load from ebx,
//    and `run != 0 && header != 0 &&`. So the lea's position IS reachable.
//
//    WHAT THEN FAILS is narrower and is the real reason this is a residue. In
//    every one of those shapes the header's own `test eax,eax` leaves retail's
//    +0x08 slot and is re-emitted next to the branch that consumes it, because
//    MSVC7 materialises a test immediately before its first use as a condition.
//    With the run test added, that second test lands BETWEEN the two saves --
//    so the save group is no longer adjacent, and retail's two-save prologue
//    gains an instruction in the gap that retail does not have.
//    Retail is therefore not a shape this compiler misses: it has exactly one
//    prologue-rooted test, and it needs both that single test in retail's slot
//    AND an address computation interposed between the two saves. MSVC7 emits
//    one or the other. Every shape that keeps `test eax,eax` at +0x08 sinks the
//    `this` copy to the head of the save group (A: `header != 0 &&` keeps
//    retail's test AND its `js`, at 157B), and every shape that interposes the
//    lea displaces the header test (B: `run != 0 &&`, at 159B). The two are not
//    simultaneously reachable in one TU.
//
//    Twenty-one further shapes were measured this round against the full body
//    and are rejected: the two-term and three-term short-circuit chains in both
//    orders, `run` computed from `this` and re-derived from `block`, `block`
//    aliased through a `char*` or a `this`-typed pointer, a header read through
//    a pointer alias, the run pointer read twice, the header read twice, an
//    inline-asm barrier, a `volatile` allocator pointer, an early byte member
//    read, a member write before the branch, `run` used before the header load,
//    a run deferred into each arm of the sign test, a null-compare against the
//    block, a tautological run compare the compiler deletes outright, and a dead
//    second lea of the same and of a different width. All either sink the copy,
//    or emit a real instruction retail does not have.
//
//    WHAT IS NOW PROVEN is narrower than "the scheduler will not interpose": it
//    will, and the order is a fixed PHASE rule rather than a competition between
//    two competing instructions. Measured this round, full body, one variant per
//    compile:
//
//    * The allocator emits the `this` copy with the callee-save group and the
//      ebx-rooted `lea` after it, ALWAYS, in all sixteen shapes tried: a plain
//      initialiser, the header load declared first, `register` on the run
//      pointer, `register` on a `GeneralAllocatorDebug *me = this` alias,
//      `register` on both, the address of either local taken into a named
//      frame slot, both taken, a second ebx-rooted `lea` through a live second
//      pointer, an explicit alias with a pointer-identity use, the header word
//      read twice through two named loads, a volatile alias, and the alias
//      spelling for the header. Every one emits
//      `push esi / push edi / mov edi,ecx / lea esi,[ebx+8] / test eax,eax`,
//      byte for byte the same 155-byte body. Nothing an explicit `this` local
//      can say changes it: MSVC7 folds the alias straight back to the implicit
//      `this`, so the copy is re-formed by the allocator and placed in phase 1
//      whatever the source did. An alias that is NOT folded does move the
//      allocation -- reading the header through `me` drops ebx and yields retail's
//      five prologue instructions in retail's order with `run` in edi instead of
//      `this` -- but it changes WHICH object the header is read from, so it is a
//      wrong-object spelling rather than a candidate.
//
//    * The interposed-lea shapes put a REAL extra instruction in retail's +0x0B
//      slot and displace retail's own `test eax,eax`, exactly as recorded above.
//      The best of them is new and worth the detail: `run != 0 && !(header &
//      (int)0x80000000)` emits
//
//          push ebx / mov ebx,[esp+8] / mov eax,[ebx+4] / push esi /
//          lea esi,[ebx+8] / test esi,esi / push edi / mov edi,ecx /
//          je +0x2a / test eax,eax / js
//
//      which is retail's exact +0x0B..+0x0F -- `push esi / lea esi,[ebx+8] /
//      push edi / mov edi,ecx` -- with the lea genuinely in retail's slot. It
//      fails because the `test esi,esi` it needs to justify the lea is a real
//      six-byte test and a real `je` that retail does not have, and because
//      MSVC7 moves retail's own `test eax,eax` down to +0x0D, giving 159B.
//      The two artefacts trade against each other exactly once, so the prologue
//      cannot be right by getting the lea alone.
//
//    * Net: the body needs retail's single prologue-rooted test in retail's slot
//      AND an interposed address computation, and MSVC7 has no phase in which it
//      emits an address computation between two callee-saves.
//
//    The sibling VerifyGuardFill 0x006C3020 is NOT the control it was taken
//    for. Its file compiles byte-exact at /O2, but under a different shape: it
//    opens `push ebp / mov ebp,[esp+8] / test BYTE PTR [ebp+4],4 / push edi`
//    and reaches its `lea esi,[ebp+8]` much later, so it never has to order a
//    prologue address computation against a save group at all. Compiled at -O1
//    it degenerates to the framework prologue and loses its match. An earlier
//    bank also cited the `56 8d 73 08 57 8b f9` pattern as a matched example of
//    this shape elsewhere; the only two occurrences in the image are this body
//    and 0x0030ABB3, which is inside the byte-verified ?setOrientation@Thing and
//    is a frame-pointer body (`push ebp / mov ebp,esp / sub esp,0x58`) where
//    the bytes are a coincidence of that body's own copy loops, not this
//    schedule. No matched body in the image exhibits this prologue shape.
//
//    This body keeps `block` in ebx (as retail does) because retail reloads
//    [esp+8] exactly once and that reload is also the report call's second
//    argument, which MSVC7 forms as `push ebx`.
//
// 2. The GetBlockSize call at +0x39. Retail keeps the argument push ahead of
//    the ecx load -- `push esi / mov ecx,edi / call 0x00032A20` -- where
//    MSVC7 loads ecx first and pushes after. The callee is the EA PPMalloc
//    GetBlockSize at 0x00032A20, whose every exit is `ret 4` (six exits, all
//    `c2 04 00`), so it CLEANS its own stack argument. The canonical spelling
//    for a callee-cleaned thiscall is therefore `__stdcall`, and that is what
//    reverses the order -- measured: declared `__thiscall` it emits
//    `mov ecx,edi / push esi / call`, declared `__stdcall` it emits
//    `push esi / push edi / call`.
//
//    That does not land, for a reason worth recording. `mov ecx,edi` at +0xFA
//    is load, not arithmetic, so it is not part of a constant address
//    computation -- it cannot be folded into the `lea` the way a pointer
//    initialiser would be. A __stdcall member therefore cannot express "save
//    esi, compute the run, save edi, copy this": the ecx load floats free of
//    the address computation and MSVC7 sinks it next to the save.
//
//    A free `__stdcall(this, block)` does order the pushes first, but costs an
//    extra `push edi` that retail does not have, and a free __cdecl spelling
//    adds that push plus an `add esp,8`. __fastcall moves the argument into
//    edx instead of pushing it. A pointer-to-member spelling is not available:
//    MSVC7 defaults a member typedef to __cdecl and rejects __thiscall in a
//    typedef (error C4234). Every path trades this site for a worse one, and
//    the body is left at its recorded 0.99.
//
//    Retails single-copy structure is what closes this site. Retail emits
//    EXACTLY ONE `mov ecx,edi` in the body, the prologue copy: the call at +0xFC
//    uses it directly with no reload, and the report at +0xFA has its own. So
//    any spelling that reloads ecx at this call site must emit an instruction
//    retail does not have, and any ecx trick that avoids the reload is a no-op
//    MSVC7 deletes. Measured: a free-standing no-argument forwarding helper
//    reached through a one-argument thiscall emits `mov ecx,edx / push esi /
//    call`, the same ecx-first order, because the ecx copy for the OUTER call is
//    the argument and is sunk with it. Site 2 is a consequence of site 1: it is
//    retail's single allocator copy being reused rather than re-derived.

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
	//
	// The callee CLEANS its own argument: all six exits of its 0x4F6-byte body
	// are `ret 4` (0x00032A6A, 0x00032A96, 0x00032AAF, 0x00032AFD, 0x00032C4B,
	// 0x00032C54), none a plain ret. So the faithful declaration is __stdcall,
	// and that choice is measured rather than assumed: __thiscall emits
	// `mov ecx,edi / push esi / call` at +0x39, while __stdcall emits
	// `push esi / push edi / call`. Retail is `push esi / mov ecx,edi / call`,
	// which is neither -- see the note at the top for why __stdcall cannot
	// reach it. __thiscall is kept here because it is the one that costs no
	// extra bytes, so the body stays size-exact at 155.
	unsigned int GetBlockSize(const void *block);

	// 0x006C2FB0 as a thiscall MEMBER, the calling convention reverse/symbols.csv
	// already pins. Retail's own call site is `push 0x008E7C3C / push ebx / mov
	// ecx,edi / call` with NO add esp,8, so the callee cleans both stack
	// arguments and the LAST push is the FIRST stack argument -- which the
	// callee's own `mov edx,[esp+8]` confirms is the message.
	//
	// MSVC7 pushes a thiscall member's stack arguments right to left, exactly as
	// it does for cdecl, so the DECLARATION has to be (block, message) to push
	// the message first. Every earlier bank declared (message, block), which
	// emitted `push ebx / push 0x008E7C3C`: the wrong push order, and with the
	// message landing in the wrong stack slot besides. The free __cdecl spelling
	// gets the push order right only by declaring the message last, and then
	// necessarily costs the trailing add esp,8 retail does not have.
	void rva006C2FB0Report(void *block, const char *msg);

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
			// The declaration above takes (block, message) precisely so that this
			// call pushes the message first: MSVC7 pushes a member's stack
			// arguments right to left, loads ecx from the allocator immediately
			// before the call, and emits no add afterward.
			rva006C2FB0Report(
				block, "GeneralAllocatorDebug::VerifyDelayedFreeFill failure.");
			return false;
		}
	}

	return true;
}