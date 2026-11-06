# Line emission writer export identity

Inspected base: `d707d2f53bf`, 2026-11-06. Picker claim:
`0x0055CEAA` and `file:Code/GameEngine/Source/GameClient/Rva0055CEAAWrite.cpp`.

## Target facts

- `python3 tools/next_work.py --claim` served the existing 263-byte writer
  (292 bytes including its three EH rows), attributed one missing export.
- `reverse/exports.csv:1950` names `0x0055CEAA`
  `?writeINI@LineEmissionVolumeModuleTemplate@FXParticleSystem@@UBEXAAVFile@@I@Z`:
  `void writeINI(File &, unsigned int) const`.
- The ledger already owned that address as
  `?rva0055CEAA@LineEmissionVolumeModuleTemplate@FXParticleSystem@@UAEXPAVFile@@I@Z`,
  with its EH handler and two funclets in the same source. No new body was needed.
- Authoritative real-link run `42174078539`, measured commit `da59156dc4f2`,
  still lists this exact missing name in `errors.tsv:307` (`exit.exp`). Its
  scoreboard has 308 unresolved names, 0 duplicates, and no image written.
- No registered shared `LineEmissionVolumeModuleTemplate` header was found.
  The source already had a private view; this change edits that existing view.

## Repair

Reconcile the existing virtual member with the exact exported name, reference
parameter and const qualification. Preserve its operations, offsets, source path
and all four rows. Update the EH handler's name and both funclet parent notes;
tombstone the two superseded names. There are no new pins, aliases, bodies,
vtables or initializer tables.

`rename.py function --rva 0x0055CEAA --new '<exact export>' --basis canonical:export
--evidence reverse/exports.csv:1950 --dry-run` refused the signature change
beyond the identifier. The documented `docs/naming.md` hand-signature-rename path
therefore applies. No `name_basis.csv` record was added. Search of current Code
sources and symbol/data ledgers found no caller, pin, data relocation spelling or
`/alternatename` using the old name after the source update.

## Verification

The host initially lacked Wine. Final checks used the existing local x86 QEMU
compiler wrapper through the normal tools, with this worktree exported read-only;
the compiler, headers and gates were unchanged.

- `python3 tools/find_declared_unmatched.py Code/GameEngine/Source/GameClient/Rva0055CEAAWrite.cpp`:
  all defined functions already matched, before and after.
- `python3 tools/check_csv.py`: OK; 99,515 functions, 9,320 symbols, 2,272 data rows.
- `./build.sh Code/GameEngine/Source/GameClient/Rva0055CEAAWrite.cpp`:
  4/4 rows exact, 3/3 string literals, 0 unverified/skipped literals. EH proof
  verifies the two old label tokens against renumbered labels at the same retail
  funclet addresses; no label pin was introduced.
- Read-only COFF inspection with `build.read_object_symbols`: exact new parent
  external definitions 1; old parent occurrences 0; exact new EH definitions 1.
- `python3 tools/name_dependents.py --staged`: two old code/data target names
  removed; zero referencing units among 18,026 scanned. Text searches likewise
  find no old-name caller or `/alternatename` in current Code or symbol/data rows.
- `python3 tools/link_check.py Code/GameEngine/Source/GameClient/Rva0055CEAAWrite.cpp`:
  LINKS, 1/1 units, LINKED 272 -> 272 bytes, against index
  `47fd56b879` of 2026-11-06 05:39 UTC. The existing file already linked in
  the census; the repair supplies its missing exported identity.

This is scoped byte and current-object link proof. No new real-link image,
startup/menu/skirmish/save-load pass, or retail CRC comparison was run. The
308 real-link unresolved headline is historical and is not decremented by this
preview; await the next automated real link.
