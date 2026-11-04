# Horde module-data parser consolidation, 2026-11-04

Scope: move the existing 21-byte `W3DHordeModelDrawModuleData::buildFieldParse`
row at RVA `0x000793E5` from
`Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DHordeModelDrawModuleDataParse.cpp`
into its approved destination,
`Code/GameEngine/Source/Common/W3DHordeModelDrawManager.cpp`.
One source file removed; no new matched bytes or census gain claimed.

## Evidence and prerequisite

Started at `ce1ba6563c`; the declaration prerequisite was published as
`57efd77e93` after fleet rebasing. The destination's existing class view omitted
the static method declaration, so the first composition rejected the parser
with C2039. Adding the forward declaration and static method signature kept
70/70 function checks and both data rows passing, without changing layout.

The naming consolidation planner was regenerated after that edit and
`name_lane.py consolidate --check build/consolidation` passed before applying
the merge. The map's approved destination is provisional; the naming hint
`GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DHordeModelDraw.cpp`
is not claimed as independently proven retail placement. No donor-source
inference or new naming approval was needed for this existing row.

`tu_skeleton.py --merge` accepted only the destination and parser donor, using
the verified cached trial plan. It retained the destination's compiler flags,
the canonical FieldParse include, and the parser's existing calls to
`MultiIniFieldParse::add` and `W3DModelDrawModuleData::buildFieldParse`.

## Verification and ownership audit

- `./build.sh Code/GameEngine/Source/Common/W3DHordeModelDrawManager.cpp`:
  71/71 function checks, two byte-verified data rows. Three parent-generated EH
  funclets remain exact despite label renumbering (`0x0075F0A4`, `0x0075F0AC`,
  `0x0075F04C`).
- `find_declared_unmatched.py`: all defined functions already matched.
- `check_csv.py`: passes, 99,434 functions, 9,338 symbols, 2,269 data rows.
- TU ownership passes. Data identity: zero shadow findings; converged checking
  covers 11 addresses, zero second names and zero unjudged rows.
- Code identity remains in shadow with the same six pre-existing destination
  findings: the `Rva000799D0` list-clear binding and duplicate definitions for
  `rva00078AC6`, `rva00078ADB`, `rva00078AE3`, and the two byte-slot setters.
  These are unresolved work, not retirements.
- The merge engine's link guard accepted this composition while protecting
  the 13 census-linked touched units and outside provider/selected-COMDAT
  contracts. Index: `5a13f2cd61`, dated 2026-11-04 02:25 UTC, census
  `171fb36062` at 00:49; index SHA-256
  `94e7aaf6e76aaa510f4953b9b786d4fd7e9211ed8b9e994af34661123b1a1a4e`.
  This is a guarded preview, not a new real link or census measurement.
- The engine repointed the one functions row, the map's one source column,
  and both FieldParse/MultiIniFieldParse header-queue keys. Header debt is
  transferred with its existing verdicts; nothing is retired. No donor key
  exists in the code/data identity baselines. Microsoft-header audit refreshed
  the destination and found zero local Microsoft declarations; queue unchanged.
- All destination hatches, including both link-wide alternatename pragmas,
  remain. The merge tool's unrelated global hatch-baseline refresh was excluded;
  no hatch baseline change is part of this batch.

Path audit covers the published declaration prerequisite plus this sole source
removal. A repository search of the removed path/basename found no active tool,
hook, workflow, include or build/configuration consumer. Intentional old mentions
remain in the provenance comment, historical `reverse/link_status.csv`, and the
2026-10-29 FieldParse-table obstacle's historical measurements. Active ledgers,
header keys and the TU map now resolve to the destination. No fold proof or
data owner needed repointing. The committed map was not regenerated.

## Remaining consolidation obstacles

The other eleven donors were excluded. Most still have incompatible private
class/container views or duplicate explicit template machinery. Their source
files and rows remain untouched.

The optional `GameLogic/Object/Rva000796CBPairInit.cpp` donor was rejected by
the link guard: the merged object would break another unit's copy of
`?allocate@?$allocator@PBVLocomotorTemplate@@@_STL@@QBEPAPBVLocomotorTemplate@@IPBX@Z`.
Before retrying that donor, inspect its selected allocator implementation and
the destination's emitted copy together; byte preservation alone is insufficient.
No repair of that provider contract or global LINK-133 clearance is claimed.
