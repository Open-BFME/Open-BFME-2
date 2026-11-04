# AIStructureStats constructor consolidation, 2026-11-04

Inspected base: `4a7617a4d4`; prerequisite repair: `f9c9236ffa` (runner
publication rebased the original `44caa18063`). Final path audit starts at
`origin/master` `9624d680c2` and includes all pending commits and this merge.

`tu_skeleton.py --merge Code/GameEngine/Source/Common/AIStructureStats.cpp`
absorbs `Code/GameEngine/Source/Common/Rva005965A5Ctor.cpp`: one fewer source
file, two rows moved, five matched rows in the resulting TU. Coverage stays
unchanged; no census or image-ownership improvement is claimed.

## Evidence and repair

The default picker claimed both files. The supported Common planner completed
before edits; its packets leave routing unresolved because the committed map
is stale and flag macro/include prerequisites. These are investigation hints,
not placement approval. The merge rebuilt the map in memory and approved the
constructor and deleting destructor for the existing provisional TU. Only their
source columns change in the committed map; no assignment is regenerated.

The initial dry run reproduced the prior C2375 `_errno` linkage failure from
mixing the seed's CRT declarations with the donor's STLport includes.
`tu_views.py --dry-run` also found incompatible vector element identities.
The donor used canonical BfmeE16, a 16-byte record, whereas the existing
destructor and Register reconstruction use four-byte ScienceType elements.
An empty-storage constructor folded at 0x00211E58 alone proves no element type.
The repair retains the existing ScienceType storage interpretation and both
address-derived class names; it claims no newly recovered application name.

The two files now share the same partial class/storage views. The constructor
uses the existing rowed ScienceType `_Vector_base` constructor. The empty
initializer only writes pointers and cannot allocate; `throw()` communicates
that property, preventing an extra ctor EH frame. An empty allocator ctor
matches STLport's non-value-initialized temporary. The existing derived
destructor still owns erase/free, so the partial storage view adds no implicit
cleanup. No shared header, alias, pin or hatch changes.

A full native STLport vector was tested and rejected because its POD destructor
removes the range-erase call; that nonmatching trial was replaced. The retained
repair passes all five source rows independently before merging. Its commit
hook reports zero new code-identity findings, zero data findings, one EXACT
EH parent, and passing literal/import checks. Both declaration checks pass.
The two pre-merge link previews report LINKS, 82 and 60 authored bytes.

## Merge verification

The dry run and applying merge accept both files with no rejected donor.
The merge's link guard preserves both previously census-linked scoped units.
The mixed Register/UnRegister donors remain intact and need their own split
work; no other file is moved.

- `./build.sh Code/GameEngine/Source/Common/AIStructureStats.cpp`: 5/5 exact,
  including constructor, deleting destructor, destructor and both EH rows;
  string, float and import checks pass. The funclet's compiler label changes
  from `$L382` to `$L806`; verification resolves it through the EXACT parent
  EH graph at retail RVA 0x0079D2DF.
- `find_declared_unmatched.py`: all defined functions already matched. The
  pre-existing anchor has its explicit absent-from-retail marker.
- `eh_verify.py`: one parent with EH data, EXACT; none missing or baselined.
- `link_check.py`: resulting TU LINKS against published index `8661f15284`
  (2026-11-03 20:03), 82 -> 142 authored bytes. The extra 60 bytes transfer
  from the deleted donor; this is a preview, not a global linking gain.
- `check_csv.py`: OK, 99,433 function rows, 9,342 symbols, 2,269 data rows.
- `data_check.py`: zero findings; converged enforcement: zero second names
  and zero unjudged rows for the 11 converged addresses. `class_gate.py` passes.

## Path, debt and consumer audit

The full pending batch has two absorbed paths: Rva00447B0EDtor.cpp into
LANGameInfo.cpp (already audited in its own handoff), and Rva005965A5Ctor.cpp
into AIStructureStats.cpp. A combined old-path and basename search covered
tools, hooks, workflows, game source/includes, shared shims, root build/config
files, reverse registers and docs. No active path consumer requires an update.
Remaining old-path mentions are provenance comments, historical attempts,
previous handoffs, naming diagnostics and historical census rows. No directory
moves, derived include assumptions or link-wide aliases are involved.

The donor has no keys in the gate, code-identity, data, hatch or compiler-flag
registers; no header-queue, Microsoft-header-queue or STLport-trial entry; and
no data-ledger row. The merge refreshes the Microsoft-header scan and checks
header transfers, with no queue changes needed. Both function rows and map
source columns are repointed; no debt is retired or tombstoned. No existing
linking-obstacle entry names this target, and no new unresolved obstacle was
encountered. The ordinary outgoing hook still checks provider/consumer bindings.
