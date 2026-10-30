# SpecialPowerModuleData pair cleanup

Base: `23bfc966db`; 2026-10-30; claim owner `yasinschroeder-codex3`.

## Target facts and repair

The default picker served TU approval for
`Code/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModule.cpp`.
Its seven proposed rows are the cleanup funclets and frame handler
`0078CD53..0078CD9C`, attached to destructor `0049334F` by
`FuncInfo0093C994`. They already have ledger owners; they are not missing
coverage. Six remain in generated sources and the handler belongs to
`SpecialPowerModuleDataDtor.cpp`.

The destructor passed both of its existing rows before this change, but
`eh_verify.py` reported its baselined `.text$x` difference: one byte at
`0078CD5B`. The old view split an integer at `+10` and a reference holder at
`+14`. Its cleanup therefore added `14` to `this` and called
`RefHolder14::~RefHolder14`. Retail adds `10` and jumps to `004C9F38`.

The existing constructor view already groups these fields in the eight-byte
`Rva004CEE6EMember`. Its compiler-emitted destructor is rowed at `004C9F38`:
`8B 49 04 85 C9 74 05 E9 <rel32> C3`, with the jump targeting
`OpaqueRefCounted::Release_Ref` at `00050ED3`. This is target layout and
relocation evidence, not a recovered donor name.

The destructor now uses that same pair view. Its emitted pair destructor has
the same 13 bytes and relocation target as the constructor's copy (normalized
COMDAT digest `ec0eaef79a80`). The cleanup at `0078CD5B` now adds `10` and
references this pair destructor. The 115-byte parent and ten-byte frame
handler retain their existing matches. No pin, row, source path or TU map was
changed. `eh_verify.py SOURCE --write-baseline` removes this single debt key;
the EH baseline shrinks from 32 to 31 entries.

## TU approval boundary

The supported naming planner was run for the SpecialPower subsystem and
`tu_skeleton.py --plan` rebuilt the current assignments in memory. The parent
destructor remains displaced, with only the convention hint
`SpecialPower/SpecialPower.cpp`. `tu_map.py` excludes ModuleData constructors
and destructors from its ordinary class-name COMDAT anchor, and the naming
convention strips the ModuleData suffix. These seven P rows consequently
remain proposed. The ZH SpecialPowerModule source supplies a constructor and
field parser, but no out-of-line destructor definition establishing a Z anchor
for this address. Do not promote a naming hint to approval or move these rows
until target TU evidence resolves the parent. No generated source was edited.

## Verification

- `find_declared_unmatched.py` before and after the edit: all definitions
  accounted for; the constructor provider also passes.
- `./build.sh SpecialPowerModuleDataDtor.cpp`: 2/2 rows exact.
- `./build.sh SpecialPowerModuleDataCtor.cpp`: 11/11 rows and its data row
  exact, including the existing pair destructor provider.
- `link_check.py --prepare-current` on both sources: 13/13 rows and one data
  row verified with strict reusable receipts.
- `eh_verify.py` on both sources: EXACT 2; no missing objects.
- `eh_verify.py --assert-shrink-only HEAD`: passes against the base.

Ordinary `link_check.py` on the pair predicts LINKS for both sources against
index `85f6b7f40c`: destructor 125 authored bytes, constructor 383, retaining
508 total. That index predates the base, so this is bounded compatibility
evidence. Full affected-consumer selection and census confirmation remain
unverified; carry the pair and their reference-holder consumers into the next
scheduled census. No census or unique-byte gain is claimed.
