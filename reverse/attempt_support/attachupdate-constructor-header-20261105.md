# AttachUpdate constructor header reconciliation

Inspected `bb862d3abd`; scope: AttachUpdate.cpp and AttachUpdateCtor.cpp.
The supported consolidation planner surveyed Object/Update, and the current
TU plan approves both sources for AttachUpdate.cpp. Historical evidence:
[prior consolidation handoff](attachupdate-consolidation-20261104/README.md).

The ctor donor now includes canonical UpdateModule.h. Its derived declaration
matches the seed's methods and fields; `novtable` retains the existing three
native table references instead of emitting new derived COMDAT tables.
The old explicit primary/secondary pointer fields become writes to those same
subobjects at +0, +0x0C and +0x10. Native table identity and function signatures
are unchanged; the constructor's EH cleanup now references the canonical
virtual UpdateModule destructor, whose retail body is already rowed.

Checks before consolidation:

- `./build.sh` on both files: 16/16 code rows and the constructor's one data
  row byte-match; string and compiler-funclet checks pass.
- `find_declared_unmatched.py`: all defined functions are already matched.
- `header_adopt_lane.py accept --class UpdateModule AttachUpdateCtor.cpp`:
  PASS; retires exactly one header_queue row through its owning tool.
- Current-object `link_check.py`: both LINKS, retaining 1,018 + 99 = 1,117
  authored bytes against census c95fcfcfcd (2026-11-05 05:17). This is a preview,
  not a new census or a whole-game real-link claim.
- Constructor object defines only its ctor and existing `_vtbl_00C4DB20` data;
  no compiler vtable definition is emitted. It references
  `??1UpdateModule@@UAE@XZ` out of line.
- Merge dry run accepts the seed and ctor donor, retaining all 16 code rows.
  AttachUpdateModuleDataCtor.cpp still conflicts on `_STL::_Base_bitset` and
  has the constructor/destructor vptr constraint recorded in the earlier
  handoff. No trial edit was made to that donor.

Next: apply the supported merge, byte/link-check it and audit path consumers.
The two mixed donors and the generated ctor funclet remain outside this move.
No new pins, link aliases, debt keys or class copies were added.
