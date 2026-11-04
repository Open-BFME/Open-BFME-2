# OilSpillUpdate consolidation and header acceptance, 2026-11-04

Inspected revision: `78e2dc7b06797e2a9e67777907a82a9c6c3f10cf`.
Scope: `Code/GameEngine/Source/GameLogic/Object/Update/OilSpillUpdate.cpp`
and its four constructor/destructor donors. Claims were taken by the picker.

## Retained result

`header_adopt_lane.py accept --class UpdateModule` passes for the existing
destination source and retires its one stale `reverse/header_queue.tsv` row.
Acceptance was repeated after restoring both trial sources to their original
bytes; it still passes. No source, ledger ownership, pin or hatch changes remain.

`./build.sh` on the destination and `OilSpillUpdateModuleDataDtor.cpp` verifies
9/9 rows. Both pass `find_declared_unmatched.py`. Ordinary `link_check.py`
reports both LINKS: 576 and 84 census-counted bytes, respectively, unchanged.
The index is dated 2026-11-04 02:25 at `5a13f2cd61`; this prediction is not a
new census or a real-link measurement. `check_csv.py` passes.

## Consolidation trial, restored

The supported planner (`name_lane.py consolidate --under` the Update directory)
reports private views and unledgered-definition review prerequisites. The current
`tu_skeleton.py --merge ... --dry-run` accepts no donors. `tu_views.py` confirms:

- The module-data constructor uses integers where the destination and destructor
  use `AsciiString` members at +0x10 and +0x14.
- The behavior constructor/destructor use three private FireWeapon base views;
  the destination uses canonical `UpdateModule` inheritance instead.
- No one OilSpillUpdate view declares all virtual slots.

A bounded module-data destructor trial replaced its private FireWeapon module-data
base with the canonical header, used the destination's public fields and FXList
pointer type, and declared the virtual destructor in the destination. All 9
combined code/EH rows still matched; `eh_verify.py` reported EXACT for the
destructor. Header acceptance nevertheless refused a predicted link loss.

The new 124-byte `??_7OilSpillUpdateModuleData@@6B@` table has 31 slots, versus
the old short compiler table. A read-only COFF/RetailTruth probe at native RVA
0x0084C2F8 found the sole unresolved table proof at slot 14: the declaration
`?slot14@ModuleData@@UBE?AVAsciiString@@H@Z` has no ledger address or object-local
definition. Retail's pointer there targets RVA 0x000B69A1. The other 30 slots
resolve through an existing named address or recursively verified definitions.
The table's overall verdict is **unknown**, not a proof of a recovered table.

RVA 0x000B69A1 is already covered by the 28-byte row
`?rva000B69A1@Rva000B69A1@@QAE?AVAsciiString@@H@Z` in
`Code/GameEngine/Source/Common/Rva000B69A1.cpp`. It returns the shared empty
string. This is existing-placeholder identity work, not missing code.

`rename.py function --rva 0x000B69A1 --to-class ModuleData --new
'?slot14@ModuleData@@UBE?AVAsciiString@@H@Z' --prepared ... --dry-run` refuses:
no ModuleData constructor/destructor/deleting-destructor row installs a native
table holding that address. Derived-table occurrences alone do not satisfy this
identity admission. No tool override or alternate pin was attempted.

## Remaining work

Establish the slot-14 owner's class identity through admissible evidence before
retrying canonical module-data adoption. Then reconcile the constructor's string
members and behavior base/virtual layouts in independently verified commits,
and retry the supported merger. All trial source edits were restored; the four
donors remain separate. Existing alternatename pragmas and hatch rows remain.
No source-file reduction, recovered bytes or linking gain is claimed.
