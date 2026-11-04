# SynchronizeGroupOrder container reconciliation

Inspected revision: `a1ad5f0db7`, 2026-11-04. Scope: the constructor TU and
`SynchronizeGroupOrderDtor.cpp`, `SynchronizeGroupOrderSlot4.cpp`, and
`SynchronizeGroupOrderXfer.cpp` in `Code/GameEngine/Source/GameLogic/AI/`.

## Evidence and change

The existing `Include/GameLogic/Rva002EE9B7.h` records a 12-byte opaque
container, its folded constructor at RVA `0x000D3A71`, destructor at
`0x002F0B52`, and referenced-int erase at `0x0046EDEF`. The existing
SynchronizeGroupOrder constructor rows place that member at +0x18 and clear
the flag at +0x24. These target facts establish extent and operations; the
folded constructor does not establish an AsciiString payload.

Use that existing container view in all four sources. Remove the constructor
TU's AsciiString set declarations and the destructor view's obsolete extra
four-byte padding. Retain the existing set<int> view at the insertion and
transfer call sites; erase and empty use the opaque type's existing methods.
No function names, pins, rows, flags, headers or source paths changed.

`tools/class_layouts.py --class SynchronizeGroupOrder` reports the same member
layout in all four sources: `m_18` at +0x18, size 12; `m_24` at +0x24, size 1;
class size 0x28. The old destructor view's padding placed its flag at +0x28.

## Verification

- `./build.sh` over all four sources: **14/14 matched**, including both
  constructor/clone EH funclets; string, float and import checks pass.
- `tools/find_declared_unmatched.py` over all four sources: all defined
  functions already matched.
- `tools/link_check.py` over all four sources, census `5a13f2cd61`
  (2026-11-04 02:25): destructor **87 -> 87**, Slot4 **104 -> 104**, Xfer
  **68 -> 68** predicted linking bytes. Constructor TU remains **0 -> 0**:
  its `??_7SynchronizeGroupOrder@@6B@` differs from the first COMDAT copy.
  The same constructor/dtor results were checked before editing. These are
  local predictions, not new census or real-link measurements.
- No protected-register keys name these four sources. No debt retired and no
  files removed.

## Remaining consolidation prerequisite

The supported planner was run under `Code/GameEngine/Source/GameLogic/AI/`;
its current-input scan reported no missing inputs. Before and after this
change, `tu_skeleton.py --merge .../SynchronizeGroupOrder.cpp --dry-run`
accepts zero donors. Slot4 still rejects with C2600 for missing constructor
declarations; destructor and Xfer compositions still reject with C2259 for
abstract-class instantiation, and Xfer also reports C2509. No merge applied.

`tu_views.py --dry-run` now reaches the virtual contract conflict, "no one view
declares every virtual slot." The constructor has a minimal GroupOrder base;
the destructor and Xfer include the Snapshot-based fourteen-slot GroupOrder
header; Slot4 spells a four-slot private base. Xfer's `v01` and `v02`
declarations introduce slots 14/15 over that header rather than slots 1/2.
Next work must reconcile this inheritance and virtual-method contract,
including the constructor's vtable provider, while preserving the three
currently linking donors. Repeating only a field-layout union will not help.
