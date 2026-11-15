### LINK-678: g_aptDateInterpreter was 72 bytes; retail's interpreter is 0x6C (retail-order startup crash)

Status: Repaired (awaiting the retail-order confirmation image). Updated: 2026-11-15 (ancalgonn-swarm-waste, P156);
inspected revision: `e0580c2c61e`. Related: LINK-659 (Debug::Instance), the other retail-order startup blocker.

**The crash.** Crash triage, deep-R3 (srv1 `~/bfme2-ops/seat2/build/triage/lookahead/deep-R3/finding.md`, TEST ONLY
captures). A retail-order image (R3) crashed in `isUndefined` under `Rva006CCB80CallFunction("HideEndGame")`. Its
undefined-value path pushes gpUndefinedValue, then tests `[this+0x60]` (mpThrownValue). In R3 that word was non-zero,
so it popped the stack back to the base, and CallFunction then read the dword before the stack's array. The same
code and data in ALL order (C2V) ran clean.

**Cause.** AptDate.cpp defined `g_aptDateInterpreter` (VA 0x00E182E0) through a private 72-byte view. Retail's
AptActionInterpreter is 0x6C bytes, and matched code uses it to +0x68:
- The init 0x006FEAF0, called on it from Rva006CF230Initialize (ecx = 0x00E182E0 at 0x006CF8F3), writes +0x64 and
  +0x68.
- The throw writes +0x60, and callFunction reads +0x60.
The linker put another global at +0x48, so those members read and wrote it: `_bfmeObjDAE` in R3 (crash), and
Rva008A4AC0First/Second and `g_pRva006E97A0Object` in ALL order (silent corruption).

**Three ledger rows inside the span were interpreter members.** No other global can sit inside retail's object, so
these are members that matched bodies reach by absolute address:
- Rva008A5250LastKey, 0x00E18328, +0x48 (e.g. 0x006E8BF0 `mov eax,[abs]`);
- g_aptInitializerCounters, 0x00E1832C, +0x4C, 16 bytes (cleared by 0x006DF470);
- g_00E18348, 0x00E18348, +0x68 (f68; e.g. 0x006E2B6D `mov al,[abs]`).

**Repair (three commits, one push).**
1. The three definitions move into AptDate.cpp, the unit that defines the interpreter.
2. Canonical AptActionInterpreter.h carries the retail layout: mLastKey +0x48, mInitializerCounters +0x4C,
   mpThrownValue +0x60, mnStackFrameBase +0x64, f68 +0x68. sizeof is asserted at 0x6C.
3. AptDate.cpp defines the global from the header, with no private view. The nine readers use the members:
   aptKeyCode, AptAnimation (its byte-required view gains mLastKey), AptKey, AptKeyLookup (its view goes),
   Rva008A5360PackedKeyField, Rva006DF470Initialize, AptCIH, AptCIHMCInfo006E2560 and AptShutdownRva006CFAB0.
   In data_rows.csv the interpreter row becomes 108 bytes and the three member rows go, recorded in
   deleted_rows.csv. The coordinator approved this hand edit because no data-row tool resizes or retires a row, and
   `rename.py --retype` refuses class types by design.

**Still open.**
- data_ledger.csv is generated and not edited here. Its three owned rows at 0x00A18328, 0x00A1832C and 0x00A18348
  name globals that no longer exist, until the next ledger refresh regenerates them.
- tu_map.csv's data approvals for 0x00A18328 (AptAnimation.cpp) and 0x00A1832C (AptValue.cpp) assumed separate
  globals.
- AptActionInterpreter.cpp still holds its own complete class, and AptAnimation.cpp a byte-required view. Both are
  candidates for header adoption.
- Crash triage reruns a retail-order image to confirm.
