# AsciiString header adoption, AttributeModifierPoolUpdateCtor.cpp: blocked by retail's dtor

Seat dd-11, 2026-10-29. Queue row `class:AsciiString`,
`Code/GameEngine/Source/GameLogic/Object/Update/AttributeModifierPoolUpdateCtor.cpp`
(RVAs 0x00403A12, 0x00403BEF, 0x00403C8C, 0x00784D35). Base 2a7e3dc198.

## What retail proves

The unit's private view is byte-verified (12/12 rows, `./build.sh`), and retail's
own bytes refuse the canonical header's shape for the 15 four-byte pool names at
+0x30..+0x6B:

- Dtor `??1AttributeModifierPoolUpdate@@UAE@XZ` 0x00403A12 (73 B, range
  0x403A12-0x403A5A) sets the three vftables, calls the +0x20 vector dtor
  (0x403960), then calls 0x24A797 with `ecx = this`. 0x24A797 is UpdateModule's
  dtor: it sets its three vftables and `jmp 0x49b47c`. Nothing reads or releases
  +0x30..+0x6B, so the 15 names are destroyed trivially.
- Ctor `??0AttributeModifierPoolUpdate@@QAE@PAVThing@@PBVModuleData@@@Z`
  0x00403BEF (157 B) builds them with `vector_constructor_iterator` 0x1423:
  `push ctor, 15, 4, esi+0x30`; 0x1423 loops `count` times calling the function
  pointer with `ecx = element` and advancing by the 4-byte element size. It then
  zeroes names and counts in one loop (`and dword [eax-0x3c],0` /
  `and dword [eax],0`, 15 iterations, eax from esi+0x6C).

So each element is a 4-byte object with a user-provided default constructor and
a trivial destructor.

## Why the canonical header cannot pass

`reference/shims/bfme2_ascii/ascii_string.h` declares
`~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }` and has no
`reset()`. Adopting it would:

- make the dtor destroy 15 strings (retail's 73-byte body has no such loop, and
  the byte gate compares the whole range), and
- replace `m_poolNames[i].reset()` with `clear()`, whose releaseBuffer is not the
  raw null store the ctor loop contains.

The lane's pass test (`header_adopt_lane.py accept --class AsciiString <file>`)
compiles the unit against the header and fails at the missing `reset` (C2039),
then would fail the byte gate for the dtor. No source form of the canonical class
reproduces both bodies.

## Hypothesis for the next attempt

The member type is probably not `AsciiString` at all: a 4-byte, ctor-only type
(candidates: `PooledString`, already forward-declared in the same shim, or a
TU-private name type). Establishing that identity would let the unit drop the
private `AsciiString` class honestly (removing the `class_gate` finding) and
leave the class-wide queue row a false positive that only a maintainer exemption
can retire, because `accept` is the only path that deletes a header queue row.

Prior verdict for this row: `re_attempts.log`, `AsciiString-header-AttributeModifierPoolUpdateCtor`,
0x00403A12, blocked (t=0.70, gpt-6.1-sol) — same conclusion, without the dtor
disassembly. Do not re-run the header lane on this unit; it cannot pass while the
row's premise (that the member is the canonical class) is false.
