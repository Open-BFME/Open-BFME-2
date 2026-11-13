# Rva002D9508 shared partial prefix

Base: `9ad29a51f6f`. Owner: `codex-01a1071d-root-isolated-r20`, isolated
worktree `build/r20`. The header picker served all five remaining private
views, including the setter provider in `Rva002D9531CondSetter.cpp`.

## Target facts

Retail RVA `0x002D9508`, 41 bytes:

```
56 8b 74 24 08 85 f6 74 1c 8b 41 38 85 c0 74 05
83 f8 06 75 10 57 8d 79 3c a5 a5 a5 83 61 38 00
c6 41 48 01 5f 5e c2 04 00
```

The method returns without copying for a null argument or a selector at
`+0x38` other than zero/six. Three `movsd` instructions copy twelve bytes
to `+0x3C..0x47`, then it clears the selector and writes one to the byte
at `+0x48`. The minimum accessed extent is `0x49`; the C++ partial view's
aligned size of `0x4C` is not evidence of the full retail object size.

`BfmeAudioEventPrefix136.h` independently has fields at these offsets;
the rowed position constructor and position worker in `AudioEventRTS.cpp`
support the position/selector/validity interpretation. This adoption
preserves the existing three-int helper and trivial aggregate assignment;
it does not assert original member names or change their types.

The exact class's uses across `Code/` are declarations, includes and
pointer casts/calls. No allocation, embedding, by-value instance or
`sizeof(Rva002D9508)` was found. ShroudCrateCollide and the queued
ObjectRva00291A8C companion contain unused declarations. SpecialPower's
caller casts an existing `BfmeAudioEventPrefix136`; Miles casts a lookup
result. The eight already-adopted consumers also use pointer calls.
A separate method-only private declaration remains in
`GameLogic/System/LogicDispatch/owner_context.inc`, used by
`GameLogicDispatch.cpp`. It is outside this five-entry queue/cohort and
does not currently include the shared header.

## Change and remaining identity work

The existing manual header now carries the provider's consumed prefix and
helper. `header_adopt_lane.py adopt --class Rva002D9508 --header
Code/GameEngine/Include/GameLogic/Module/Rva002D9508.h --apply` removed
the private views in the complete five-source queued cohort. The setter
body, linker symbol, ledgers and canonical registration remain unchanged.

The stored discovery contract reports size one from nine opaque views and
classifies the one provider's fields as outliers. That majority result
does not establish retail size or invalidate these direct native accesses.
This uses the existing fixed-header route rather than regenerating a
header from that incomplete survey. No contract evidence was rewritten.

LINK-004's conflicting AudioEventRTS pins still block the complete class
identity repair. Moving this member onto the native 0x88 prefix would need
coordinated provider/caller reconciliation beyond this header cohort; this
change makes no claim that the complete AudioEventRTS class is recovered.

## Verification

- Original five-source normal build: 432/432 rows and one data row pass.
- Changed cohort plus eight existing dependents: normal `./build.sh` and
  strict `link_check.py --prepare-current` both pass 509/509 rows, two data
  rows, 35 string references, 52 float references and 107 named imports.
- All 1,883 external COMDAT fingerprints across these thirteen sources
  retain their bytes and relocation identities, with no additions or
  removals. See the companion JSON. This comparison does not prove that
  every pre-existing callee binding is correct.
- The owning `header_adopt_lane.py accept` test passes all five queued
  sources and retires all five queue entries itself.
- Thirteen ordinary per-source link previews retain 54,755/54,755 bytes.
  The index is `aa7acf764d`, 2026-11-12 19:19, and warns about seven
  subsequent source-path changes. Miles' allocator diagnostics are
  unreadable majority copies classified as unreferenced, not blockers.
  This is a scoped prediction against that index, not a fresh census.

No whole-game link or runtime result is inferred from these checks.

The commit hook additionally passes83/83 exact EH graphs. Its shadow data
check reports two wrong-name findings in MilesAudioManager at retail
addresses0x009E1E68/0x009E1E70; the adoption does not clear those findings.
