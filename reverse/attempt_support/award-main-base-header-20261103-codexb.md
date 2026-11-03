# AwardSystemManager canonical base prerequisite

Inspected revision: `500947226baefac7d746459d4bbecf8373bc9d82`.
Scope: `Code/GameEngine/Source/Common/AwardSystemManager.cpp`.

The main unit included the BFME2 subsystem shim, while its ThingStat parser
already included the canonical SubsystemInterface header. Composing them
redefined SubsystemInterface. The main unit now selects the same canonical
header, with `BFME_SUBSYSTEM_SLOTS` enabling the existing fourteen-slot surface
at the original include position. No shared header, class layout, function body,
ledger row, alias, pin or compiler flag changes.

## Verification

- `./build.sh Code/GameEngine/Source/Common/AwardSystemManager.cpp`: exit 0;
  66/66 function rows, 12 data rows, 13 literals and two empty-string references
  verify. Five complete emitted STLport constructor folds also verify.
- `python3 tools/header_adopt_lane.py accept --class SubsystemInterface
  --header Code/Libraries/Source/subsystem/SubsystemInterface.h
  Code/GameEngine/Source/Common/AwardSystemManager.cpp`: exit 0, PASS;
  no queue row retired.
- `python3 tools/find_declared_unmatched.py
  Code/GameEngine/Source/Common/AwardSystemManager.cpp`: all defined functions
  are already matched.
- `python3 tools/link_check.py --prepare-current
  Code/GameEngine/Source/Common/AwardSystemManager.cpp`: exit 0; strict reusable
  provider receipt and the normal byte gates pass. Census/index/status unchanged.
- `python3 tools/eh_verify.py
  Code/GameEngine/Source/Common/AwardSystemManager.cpp`: nine EH graphs EXACT,
  zero missing objects or baseline findings.
- `python3 tools/link_check.py
  Code/GameEngine/Source/Common/AwardSystemManager.cpp`: exit 0; LINKS,
  3,045 -> 3,045 authored bytes. Preview uses census index
  `8661f15284`, dated 2026-11-03 20:03. This is a bounded prediction,
  not a new census or real-link measurement.

## Remaining composition prerequisites

Before this edit, the supported merge dry run accepted zero of fifteen donors;
it retained all original files. Its parser diagnostic included the duplicate
base above and the incompatible Rva0040AF1D views. The view planner confirms
that the parser models Rva0040AF1D as deriving from a 0x68-byte Rva0040AFF3,
whereas the main unit directly owns its data beginning at offset zero. The
mechanical reconciler refuses that conflict. AwardSystemManager itself has a
compatible two-file view plan.

Other retained donors still need their recorded StringBase/STL declaration,
allocator-specialization, POD/polymorphic-view or byte/codegen prerequisites.
This change clears only the duplicate-base include prerequisite; no further
merge was applied or claimed. Next reconcile the statistic constructor and
destructor ownership using their retail bodies and EH graphs, then rerun the
supported composition check. SOURCE FILES and census LINKED are unchanged.
