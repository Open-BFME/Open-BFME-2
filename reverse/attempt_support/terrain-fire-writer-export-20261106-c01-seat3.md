# TerrainFire emission writer export reconciliation

Date: 2026-11-06. Inspected base: `64ff2f11655b25e69a47795e9c510d8c8702d303`.
Worker: `codex-fleet-20261106-c01-seat3`; shard `2/30`; claims namespace `refs/claims/`.

## Target facts and selection

The initial `next_work.py --claim --shard 2/30` served Box writer 0x0055D2E8.
Current source, ledger, commit `96ddcc5a9db` and LINK-583 establish that repair
already landed; both temporary claims were released. The supported ranked JSON
view has no repair items. Its next link item, EmissionInfoCopyCtors.cpp, charges
the missing Outward copy export to the existing Cylindrical owner at 0x003A7501.
That target requires folded-owner/TU reconciliation (current TU-map approval is
`-`), so this pass adds no duplicate body or alias there. The next viable ranked
link item is this existing TerrainFire writer.

Retail export ordinal 1961 identifies the exact
`?writeINI@TerrainFireEmissionModuleTemplate@FXParticleSystem@@UBEXAAVFile@@I@Z`
at 0x0055E6D4. The current ledger already owns its 313-byte body as a virtual
pointer-taking nonconst placeholder, plus three EH rows totalling 29 bytes.
This is placeholder identity cleanup, not a newly recovered or lost body.
The official real-link run 42180682743, measured commit
`306f01e6f65f29c07f9bf372666966d5363d6cb4` at 08:42 UTC, contains the missing
export in errors.tsv. Its scoreboard reports 308 unresolved, zero duplicates,
no image, 673 initializer bridges and 1,757 vtable bridges / 19,323 slots.
That run predates this repair and the preceding writer batches.

## Change and naming evidence

The existing virtual declaration/definition now use `writeINI(File &, unsigned)
const`. Calls pass the reference address to unchanged pointer-taking helpers.
Parent and EH-handler ledger names, two unwind parent notes and two rename
tombstones move together. No new body, code row, pin, alias, stub, table or
shared-header edit is added. `name_basis.csv` is unchanged.

`rename.py function --rva 0x0055E6D4 --new '<exact export>' --basis
canonical:export --evidence 'reverse/exports.csv ordinal 1961 exact exported
address and signature' --dry-run` correctly refuses a signature change beyond
the identifier. The documented manual-signature path in docs/naming.md applies;
this method was already virtual, so there is no hand nonvirtual-to-virtual
respell. The export is target identity evidence; source-shape comparisons to
other writers are structural support only.

A Code text scan finds the old identifier only in the defining source and a
sibling's descriptive evidence comment. No symbols-ledger pin uses the old
name. The published index's alternates contain no old-name edge.

## Verification

Compiler commands use the shared two-slot verification scheduler, the existing
VM wrappers on PATH, `BFME_VM_WINEPREFIX=/home/bfme/.wine-pdb`, `BUILD_POOL=1`
and this worker's claim owner/namespace. All four parent/EH RVAs and the source
scope were claimed before editing; no other source was changed.

- `find_declared_unmatched.py SOURCE`: all defined functions already matched,
  before and after.
- Baseline `./build.sh SOURCE`: 4/4 rows and 4 string literals pass.
- Post-change `link_check.py --prepare-current SOURCE`: 1 strict reusable provider
  receipt, 4/4 rows and 4 literals pass; census/index/status unchanged.
- `eh_verify.py SOURCE`: EXACT 1, not exact 0, baseline 0, missing object 0.
- COFF comparison: 313/313 parent bytes and all 24 normalized relocation edges
  identical. All 557 nondebug sections (raw bytes, flags and normalized
  relocations) are identical; this includes the unchanged linker directives.
  External definitions 553 -> 553 after the expected parent/handler-name
  normalization; undefined symbols 17 -> 17 with equal sets. Required export
  definitions 0 -> 1; old-parent symbol occurrences after 0. Read-only object
  parsing used tools/build.py helpers, never its compiler API. Scratch receipts:
  `build/c01-seat3-terrain-export/`.
- `link_check.py SOURCE`: 1/1 LINKS, 322 -> 322 authored bytes, index
  `47fd56b879` (2026-11-06 05:39 UTC); bounded preview only.
- `name_dependents.py --staged`: 1 conservative referring source among 18,026,
  `Rva0055EAADWrite.cpp`; its only text match is a descriptive old-identifier
  comment. With no current cached object the tool widens to that source; the
  normal hook must byte-verify it. This is not a proven call/alias dependency.
- `check_csv.py`: OK, 99,515 functions, 9,320 symbols and 2,272 data rows;
  counts unchanged. `git diff --check`: clean.

## Limits and remaining work

The coordinator will reverify integration, run the bounded outgoing batch audit,
and retain any actual affected-consumer gaps. Prior batches' audit remains
inconclusive on the older index and missing current CreateAHeroManager consumer
receipt; this provider-only check does not resolve that prerequisite. The next
scheduled real link must confirm this exported name disappears. No new
real-link count, image, startup/menu, skirmish, save/load or retail-CRC result is
claimed; no restricted nightly or smoke job was run.
