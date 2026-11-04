# CaveSystem consolidation, 2026-11-04

Inspected base: `a758171e5acea42a541b44297982e2d6c1e25734`.
Scope: `Code/GameEngine/Source/GameLogic/System/CaveSystem.cpp` absorbs
`Code/GameEngine/Source/Common/System/CaveSystem.cpp` and
`Code/GameEngine/Source/Common/System/Rva00427611Dtor.cpp` through
`tools/tu_skeleton.py --merge`. Two source files removed; all 16 rows retained.
The mixed `ModuleNameGetters.cpp` remains outside this change.

## Evidence and implementation

The supported consolidation planner was run for GameLogic/System; its retail
path and donor hints are leads, not placement proof. The merge engine rebuilt
its TU inputs, used approved placements, and repointed seven function rows,
seven source cells in tu_map (no map regeneration committed), and one naming
provenance source. The displaced deleting-destructor COMDATs follow their
approved parent through the merge engine's homeless-row rules.

The previous attempt in re_attempts.log accepted no donors: /EHsc lost the
destructor bytes, while the constructor alone changed a secondary vtable copy.
Changing the destination to /EHs preserves its original nine rows. Composing
both donors then passes the byte and link guards, including outside consumers.
The final class uses the existing SubsystemInterface and capitalized Snapshot
headers and its tracker vector. Unused donor-only BFME2NativeNetwork,
Rva00427611Buffer, BfmeE16 declarations and stale comments were removed.
No pins, aliases, shared headers, baseline keys or debt retirements were added.

## Verification

- `./build.sh Code/GameEngine/Source/GameLogic/System/CaveSystem.cpp`:
  16/16 rows match, including four renumbered funclets and two complete emitted
  STLport constructors checked against their retail owners and resolved callees.
  String, float and import reference checks pass.
- `find_declared_unmatched.py`: all defined functions already matched; the
  existing destructor-emission anchor retains its absent-from-retail marker.
- `eh_verify.py`: all three EH graphs EXACT, none baselined or missing.
- `link_check.py`: LINKS, 619 owned bytes in the composed unit; index census
  2026-11-04 17:56 at `8c757ea0db`. This is a local prediction, not a census gain.
- `check_csv.py`, case check and TU ownership check pass.
- `data_check.py`: zero shadow findings; converged check judges all rows and
  reports zero second names at 11 converged addresses.
- `code_identity_gate.py --staged` remains shadow: pointer-vector base ctor
  binding at 0x00211E58 and divergent `_Construct<unsigned int>` are reported.
  The byte verifier proves the emitted constructor folds; the link guard and
  local preview accept this object. This merge claims no identity-debt closure.

## Consolidation and tooling audit

The combined deleted paths, basenames and containing directories were searched
in tools, hooks, workflows, source/header includes, build configuration, doxygen,
documentation and path-keyed reverse registers before publication. No active
consumer needs adjustment. Remaining old-path references are the source's
historical donor comments, naming history's old/new fields and the historical
census link_status rows; their meaning is retained. The build machinery derives
source/object paths from current ledger owners.

Neither donor nor destination has keys in code_identity_baseline,
data_check_baseline, gate_baseline, hatch_baseline, flag_overrides or the header
queues. The merge refreshed header transfers and the Microsoft-header queue;
a fresh scoped ms_header_audit scan finds no local Microsoft declarations and
leaves the queue unchanged. Active function and TU-map sources resolve to the
surviving tracked TU. The pre-push batch audit remains the publication check for
provider selection and affected outside consumers. No full link, smoke run,
nightly measurement or census was performed.
