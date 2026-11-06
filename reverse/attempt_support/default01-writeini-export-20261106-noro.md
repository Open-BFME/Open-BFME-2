# DefaultModuleTemplate<0> and <1> writers: category labels swapped

2026-11-06; base `134a4ae77bf`. Status: repair verified locally, awaiting the
automated real link.

## Target facts

- `reverse/exports.csv` ordinal 1936 puts `?writeINI@?$DefaultModuleTemplate@$00@FXParticleSystem@@UBEXAAVFile@@I@Z` at `0x0055B735`.
- Ordinal 1940 puts `?writeINI@?$DefaultModuleTemplate@$0A@@FXParticleSystem@@UBEXAAVFile@@I@Z` at `0x0055C263`.
- Ordinal 972 names vtable `0x0081BA70`, whose slot 3 holds `0x0055B735`, as
  `DefaultModuleTemplate<1>`.

## Defect

The row at `0x0055B735` carried the category 0 name with export_rva
`0x0055C263`, and its unit defined that name with the alpha body. So the link
resolved export 1940 to the wrong body and reported export 1936 missing. The
real color writer at `0x0055C263` stayed under the placeholder
`Rva0055C263`.

## Change

Both exports now have the body retail gives them. The alpha unit specializes
`DefaultModuleTemplate<1>`. The color unit specializes
`DefaultModuleTemplate<0>` with the exported const File-reference signature,
and its handler and two funclet rows follow the parent. No body or alias was
added, and the old names are tombstoned.

`rename.py function --new <mangled>` cannot express this: it refuses both
template spellings with "the new name is the old name". This is a hand rename
with export evidence, as in `8858a90aa54` and `96ddcc5a9d`. Unlike the
`<3>` writer's boundary case, neither row is non-virtual, so
`function --virtual` does not apply.

## Verification

- `./build.sh` on both units: **5/5** rows exact, 5 literals verified.
- `link_check.py --prepare-current`: 2 providers byte-verified.
- `link_check.py`: both LINKS, 745 -> 745 bytes against index `d707d2f53b`.
  This is a preview, not an export-link check.
- `rg Rva0055C263 Code` finds nothing, and no other source names either writer.

The funclet check reports `$L16723`/`$L16724` renumbered and verifies the
compiled labels at `0x00799858`/`0x00799863` from the parent's EH data.

No real-link or runtime result is claimed. `<2>` (`0x0055FB37`) and `<3>`
(`0x0055F368`) stay unresolved. Their rows are non-virtual placeholders, which
is the boundary recorded in `default3-writeini-tool-boundary-20261106-round2-seat1.md`.
