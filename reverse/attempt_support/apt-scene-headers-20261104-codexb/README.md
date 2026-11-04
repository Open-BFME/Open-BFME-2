# Apt view scene-header prerequisites, 2026-11-04

Inspected base: `9b69c33f2d`. Scope:
`Code/GameEngine/Source/Common/W3DAptComponentView3D.cpp`.

The selected native consolidation dry run accepted neither remaining donor.
Setup failed on the scene base declaration order; the rendering donor failed
on the CameraClass/RenderInfoClass declaration order. The supported
`name_lane.py consolidate --under Code/GameEngine/Source/Common/` planner was
reviewed, including its device-side original-path hint and routing/compiler
blockers. That hint does not approve a destination or prove a BFME 2 path.
No source paths or function rows move in this repair.

Replaced the private Vector3, SimpleSceneClass, GenericMultiListClass (and
its partial MultiListNodeClass), and RefCountClass declarations with their
existing canonical headers. The canonical scene header supplies the real
base/list declarations needed by the setup donor. Direct includes also name
the leaf types the TU itself uses. No shared header or function body changes.

Verification:

- `./build.sh` passes 27/27 matched rows both at the original source and
  after adoption. The header acceptance tools also run the byte gate.
- `header_adopt_lane.py accept --class CLASS SOURCE` passes separately for
  Vector3, RefCountClass, GenericMultiListClass and SimpleSceneClass, retiring
  exactly four rows from `reverse/header_queue.tsv`. No other debt is retired.
- [Object comparison](object-comparison.json): all 66 external code definitions
  retain identical complete bodies and relocations; none added or removed.
  The baseline was rebuilt through the ordinary build at the original path,
  rather than inferred from the checkout's older cached object.
- `eh_verify.py`: all four EH-bearing rows EXACT, none without an object.
- `link_check.py`: LINKS, 1,674 -> 1,674 bytes, using the fetched census index
  dated 2026-11-04 17:56 at `8c757ea0db`. This preview is not a new census.
- `find_declared_unmatched.py` passes; the existing note about one unclaimed
  definition and its existing marker are unchanged.
- `check_csv.py`, `data_check.py --converged`, `class_gate.py`,
  `check_case_collisions.py` and `git diff --check` pass.

Remaining: this is a verified prerequisite repair, not a completed merge.
Retry native composition with the canonical scene/list declarations now in
place; reconcile the CameraClass/LightClass views and the incompatible
Rva00740555, Rva007401F6 and W3DAptComponentView3D declarations where still
rejected. The native mixed donor stays untouched. No increase in matched or
census-linked coverage, and no source-file reduction, is claimed.
