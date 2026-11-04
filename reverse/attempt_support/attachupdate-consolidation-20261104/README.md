# AttachUpdate transfer consolidation

`tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/Object/Update/AttachUpdate.cpp`
absorbed `AttachUpdateXfer.cpp`: one fewer source file, ten matched code rows
retained. The transferred row is `AttachUpdate::xfer`, RVA 0x004918AC, 102 bytes.
The approved TU assignment already existed; the merge tool changed only its
source column in `reverse/tu_map.csv`, without regenerating approvals.

The prerequisite commit declares the existing slot-3 override in the destination
class and aligns the donor's ObjectID type and two member names with the seed's
view. It changes no member offsets. Before composition both units passed byte
verification and the link preview (687 + 102 = 789 authored bytes).

## Verification

- [Byte verification](byte-verification.txt): 10/10 rows, one string reference;
  four compiler labels checked through their parent's exact EH placement.
- `find_declared_unmatched.py`: all defined functions already matched.
- `check_csv.py`: 99,433 function rows, 9,341 symbols, 2,269 data rows; clean.
- [Link preview](link-preview.txt): destination LINKS, 789 authored bytes.
  Its apparent increase from 687 is the moved donor, not new census coverage.
  The measured census remains 2026-11-03 20:03 at 8661f15284.
- [Merge report](merge-plan.txt): the accepted pair loses no matched rows;
  census-linked guard includes all six candidate units.
- No data, code-identity, gate, hatch, pin-consistency or body-owner debt keys
  name these six source paths. The existing Rva000421C8 and ThingTemplate
  destination header entries and UpdateModule constructor entry remain.
  The merge tool refreshed header and Microsoft-header queues without changes.

## Remaining prerequisites

Four donors remain separate, with failed compositions discarded by the merge
tool. No nonmatching reconstruction was left in Code/.

- `AttachUpdateModuleDataCtor.cpp`: the seed's private `_STL::_Base_bitset`
  template conflicts with STLport's template parameter declaration.
- `AttachUpdateCtor.cpp`: destination class lacks the constructor declaration;
  the donor also retains its queued UpdateModule view reconciliation.
- `AttachUpdateModuleDataDtor.cpp`: destination ModuleData view lacks the
  destructor declaration and must retain the donor's member lifetime layout.
- `Rva00491C84Calc.cpp`: Geometry requires a different Snapshot slot mode;
  Object and AttachUpdate private views also need reconciliation.

These compile prerequisites do not establish new link failures. The relevant
canonical-module caller-adoption and link-168 obstacle entries were searched;
their next steps did not change in this pass.

## Outgoing path-consumer audit

Audited origin/master a8dce892474a9409ad78bb32b9255c4d3be00179 against outgoing
commits through 3cc1254f1dc9f462ee0bd8507a37a395ae65e0be plus this staged merge.
The pending path removals are this donor and
`GameClient/GUI/HeaderTemplateManagerRva00201B05.cpp` (absorbed by
`HeaderTemplate.cpp`; its verification is in the sibling
`headertemplate-consolidation-20261103` evidence directory).

A combined search of tools, hooks, workflows, Code, docs and reverse found no
active build/configuration/include consumers of either removed basename.
Remaining mentions are TU provenance comments, historical attempt evidence and
`reverse/link_status.csv` census records. Preserve those records. Active row
ownership is repointed by the merge tool. Header queues retain only surviving
owners, and no donor-specific flag override or fold proof needs moving here.
The matching 789-byte link previews before and after composition provide the
local binding check; pre-push link-batch admission remains required.

## Second pass (62b71edda5)

Two view reconciles (0c5bc58f74, bba50f553d) let `AttachUpdateModuleDataDtor.cpp`
and `Rva00491C84Calc.cpp` merge: the seed adopts Geometry.h, an Object view with
`m_geometryInfo` (+0xA8) and the +0x250 interface, and a novtable
`AttachUpdateModuleData : Snapshot` with a declared virtual dtor and an
`Rva003623E5Member` ObjectFilter (+0x08). `./build.sh`: 14/14 rows in one file.
No debt register, tool, hook, workflow or doc names either removed path; only
`reverse/link_status.csv` census records and TU provenance comments do.

Still separate:

- `AttachUpdateModuleDataCtor.cpp`: besides the `_Base_bitset` clash, retail
  ctor 0x491968 stores only its own vptr and dtor 0x491AA0 stores none at entry.
  In probes only a non-novtable class with an implicit dtor gives both, which
  emits vtable/`??_G` COMDATs whose rows would move with it.
- `AttachUpdateCtor.cpp`: a real ctor in the seed emits AttachUpdate's own
  vtables, while retail's +0x0C slot is the 80-class folded 0x00BEFF90 table and
  slot 0 is the hand `vtbl_00C4DB20` data row: vtable identity work first.
