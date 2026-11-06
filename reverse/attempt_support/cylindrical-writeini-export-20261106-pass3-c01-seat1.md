# Cylindrical emission-velocity writer export reconciliation

2026-11-06; base `64ff2f11655`; worker `codex-fleet-20261106-c01-seat1`.
Source: `Code/GameEngine/Source/GameClient/System/FXParticleSystem/Rva0055EBFAWrite.cpp`.

## Target facts and change

`next_work.py --claim --shard 0/30` served the real-link candidate and
acquired the parent RVA and source-file scope. The exact existing owner at
`0x0055EBFA` is 237 bytes, with its compiler handler and two unwind rows in
the same source. Export ordinal 1944 (`reverse/exports.csv:1945`) identifies
that address as
`?writeINI@CylindricalEmissionVelocityModuleTemplate@FXParticleSystem@@UBEXAAVFile@@I@Z`.
The latest inspected authoritative real link is run `42180682743`, measured
`306f01e6f65f29c07f9bf372666966d5363d6cb4` at 08:42 UTC. It predates this
repair and still has 308 unresolved names, zero duplicates, no image, 673
initializer bridges and 1,757 vtable bridges / 19,323 slots.

The private view was already virtual. Correct the placeholder identifier,
`File *` parameter and missing const qualifier in place to the exact export.
Adjust helper calls to take the reference's address. Preserve the source path,
layout, extent, compiler flags and one body per address. Repoint the existing
EH parent identities and tombstone the old parent and handler spellings.
There is no second body, alias, pin, stub, table or shared-header edit.

The ordinary planner `rename.py function --rva 0x0055EBFA --new <exact-export>
--basis canonical:export --evidence <ordinal> --dry-run` refuses the mangled
signature change beyond the identifier. `docs/naming.md`'s explicit
hand-signature exception applies: no nonvirtual-to-virtual respell is made.
No donor identity or original TU placement is inferred by this change.

## Checks and provider preservation

- `find_declared_unmatched.py <source>` before and after: all definitions
  already matched.
- Scheduler-wrapped `./build.sh <source>` before and after: 4/4 rows and
  2 string literals pass, zero skipped/unverified literals.
- `eh_verify.py <source>`: EXACT 1, zero not-exact, zero baseline entries.
- COFF before/after comparison: 237 identical body bytes and 18 relocations
  preserved after parent/EH name normalization. All 555 non-debug sections,
  their bytes, characteristics and normalized relocation targets are equal.
  All 551 normalized external definitions remain; 15 undefined symbols are
  unchanged. The required export changes from zero to one definition, and the
  old parent spelling has zero occurrences in the new object. Linker
  directives are included in the section comparison.
- Old-name source search finds only its owner before editing. Published-index
  scan reports only the owner for the old parent and handler and no
  alternatename users (historical index scope).
- `check_csv.py`: OK, 99,515 function rows / 9,320 symbol rows / 2,272 data rows.

Untracked before/after source and object snapshots, comparison JSON and EH
result are in `build/pass3-c01-seat1-cylindrical/`. The immutable published
index was copied from this chat's coordinator after its validated download;
no objects or receipts were copied. SHA256:
`f557b95982b27920d4c545f171220ee8fc5d897df7cc028b05126f8d0e7c1914`.

## Remaining verification

`link_check.py --prepare-current <source>` completed: one explicit safe
provider has a strict reusable receipt; 4/4 rows and two literals reverified.
The census, index and status were unchanged; closure was not checked by
preparation. Ordinary `link_check.py <source>` reports 1/1 LINKS,
247 -> 247 authored bytes against the published index at `47fd56b879`
(2026-11-06 05:39 UTC), with zero TUs recompiled (one current strict receipt).
This is a bounded preview, not a new real-link measurement.
The publication checkout must run the combined batch audit. Provider identity
and a bounded preview do not establish affected-consumer closure or a linked
image. Previous LINK-583 batches lacked a current consumer receipt for
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` and the published
index predates their outgoing base; those limits remain until measured anew.
Await the scheduled authoritative real link to confirm this export disappears.
No new link, startup/menu, skirmish, save/load or CRC measurement ran here.
