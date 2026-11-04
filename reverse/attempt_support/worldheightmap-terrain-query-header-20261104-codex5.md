# WorldHeightMap terrain query header adoption, 2026-11-04

Inspected revision: `03e6e65d50fe71aae0e47151739baf647b805557`.
Claim owner: `yasinschroeder-codex5`. The picker selected the existing
WorldHeightMap header-adoption queue. This batch replaces three private map
declarations with the existing canonical header and retires three queue rows
only through `header_adopt_lane.py accept`. No shared header, ledger identity,
extent, pin, alternate name or compiler flag changes.

## Target facts and implementation

The canonical header documents retail allocation `0x120F0`, RefCountClass's
eight-byte prefix, and map width/height/border/data at +8/+0xC/+0x10/+0x24.
The existing query bodies already use these offsets; no donor layout is inferred.
The canonical header supplies RefCountClass; a local `REFCOUNT_H` guard prevents
the legacy render-header chain from defining that class again.

Cell queries select the const accessor overloads to retain their existing
external COMDAT identities. Direct border reads preserve the old inlined
dllimport accessor without emitting a new accessor provider. The initial
mechanical candidate matched all seven rows but added a border accessor and
selected non-const overloads; it was rejected by the complete-object comparison.
The final candidate retains all providers and complete runtime contents.

## Verification

`tu_skeleton.Verifier` compiled originals and candidates in scratch objects
under their normal effective flags; no shared match cache was compiled by hand.
`class_cleanup.same_runtime` passes for all three complete non-debug COFF
graphs: bytes, relocations, external definitions, weak aliases and COMDAT policy.
Scratch pairs:

- `BaseHeightMapCellQueries.cpp`: 7 matched rows; `1db9e6cf37648dcf.obj` -> `32ff10c2f338700e.obj`.
- `BaseHeightMapEstimateMaxHeightAlongLine.cpp`: 1 matched rows; `d8a5e82422711dcb.obj` -> `e669938e319358a7.obj`.
- `BaseHeightMapIsClearLineOfSight.cpp`: 1 matched rows; `fca3d15a157df468.obj` -> `31b6c747c9dc8283.obj`.

`./build.sh` passes all nine rows. `find_declared_unmatched.py` passes.
The owning header-adoption acceptance passes and retires three queue rows.
`link_check.py` against census `2f0cb97f52` (2026-11-04 16:16 UTC) predicts:

- Cell queries: LINKS, 939 -> 939 census-linked bytes.
- Maximum along line: LINKS, 591 -> 591 bytes.
- Clear line of sight: LINKS, 916 -> 916 bytes.

Total: 2,446 -> 2,446 bytes. This is a current-input prediction, not a new
census or a real-link gain. Source names and local/parameter names already
describe their query roles; no naming changes were needed.

## Remaining scope

Other queued WorldHeightMap consumers and constructor/parser views remain.
No TU merge was attempted. Existing WorldHeightMap consolidation flags and
aggregate-view prerequisites remain as documented in the earlier handoff.
The local RefCountClass include guard is now verified for these three consumers;
other adoptions still need independent byte, complete-object and link checks.
