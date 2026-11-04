# DeployStyleAIUpdate helper header adoption, 2026-11-04

Inspected source revision: `273908a47ad81afc5909cd9d76b0f65c7a944bf7`.
Scope: `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/`;
only `DeployStyleAIUpdateHelper.cpp` changed.

The consolidation picker selected `DeployStyleAIUpdate.cpp`. The supported
planner (`name_lane.py consolidate --under` this directory) completed, and the
initial `tu_skeleton.py --merge ... --dry-run` accepted no donors. Its helper
composition lacked a usable member type; Xfer lacked `AIUpdateInterface`; the
destructor composition failed byte verification. All four units were marked
census-linked by the merge guard.

## Completed prerequisite

The helper now includes the registered `DeployStyleAIUpdateClass.h` instead of
declaring private `Rva0026E9BDBase`, `Rva0026AFDAMember` and
`DeployStyleAIUpdate` layouts. Its three bodies use the existing canonical
fields: member offset 0, and DeployStyle offsets 0x4A9, 0x4B4, 0x4D5, 0x4D6.
No external donor identity or new field role is inferred from these offsets.
The file has no local or parameter bindings to name.

Verification:

- `./build.sh .../DeployStyleAIUpdateHelper.cpp`: 3/3 functions byte-match
  (0x0048E634: 15 bytes; 0x0048E6AB: 39; 0x0048E6D2: 38); literal, float
  constant and import checks pass.
- `find_declared_unmatched.py` before and after: all defined functions matched.
- `header_adopt_lane.py accept --class DeployStyleAIUpdate` on the helper:
  PASS; retired exactly its one header-queue row through the register owner.
- After `link_check.py --fetch-index`, the helper preview reports LINKS,
  LINKED 92 -> 92 bytes. Index/census: 2026-11-04 17:56 at `8c757ea0db`;
  its dependency cache was current. This is a unit preview, not a real-link or
  census headline change.
- `check_csv.py` passes. No helper keys found in the code-identity, data-check
  or MS-header debt registers; no source or ledger path changes, no alias
  removal, no shared-header edit and no other debt retirement.

## Remaining consolidation prerequisites

A second merge dry-run after adoption still accepts no donors (exit 2):

- Helper composition now reaches the seed's old field references, beginning
  with undeclared `m_flag4A8`. The seed must adopt the canonical layout and
  preserve its constructor bytes before composition can succeed.
- `DeployStyleAIUpdateXfer.cpp` composition still lacks `AIUpdateInterface`.
  Its AIUpdateInterface and DeployStyleAIUpdate header-queue rows remain.
- `DeployStyleAIUpdateDtor.cpp` composition still fails bytes. The prior
  attempt log records that sharing the member destructor changes the seed's
  constructor bytes; this pass did not identify a new codegen remedy.
- The remaining private-view reconciliation candidate is
  `Rva0026AFDAMember`. Canonical registered classes belong to the header lane.

Next: verify canonical-header adoption on the seed and transfer donor in
separate source repairs, investigate the constructor/destructor codegen
boundary, then rerun `tu_skeleton.py --merge ... --dry-run`. No files were
merged and no TU map or function ledger rows changed in this pass.
