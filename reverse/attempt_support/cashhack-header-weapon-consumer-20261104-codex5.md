# CashHack module-data header adoption in the weapon constructor

Inspected revision: `5ee7be6eb545ea4a1eabd98e52701a857ddbd98d`.
Scope: `CashHackSpecialPowerModuleData`, its canonical header, and the seven
queued source files served by `next_work.py --claim`.

## Accepted consumer

`Code/GameEngine/Source/Common/Rva002CD169Ctor.cpp` now includes
`CashHackSpecialPowerModuleData.h` instead of declaring a private outer class
and nested `Upgrades`. Its reference-word teardown accesses the canonical
`m_amountToSteal` field at the same offset. This is an existing folded
two-word constructor call used by a weapon member; it does not establish that
the weapon member has CashHack semantics. The existing containment-view
comment and reference-counted cleanup remain.

Validation:

- `find_declared_unmatched.py` passes before and after the change.
- `./build.sh Code/GameEngine/Source/Common/Rva002CD169Ctor.cpp`: 15/15 rows
  match, including the constructor and compiler EH rows. String, float and
  import reference checks pass. Compiler-label renumbering is verified through
  the parent EH graphs.
- `header_adopt_lane.py accept --class CashHackSpecialPowerModuleData
  Code/GameEngine/Source/Common/Rva002CD169Ctor.cpp`: PASS; the owning tool
  retires exactly one header-queue row.
- Ordinary `link_check.py` preview: LINKS, 879 -> 879 census-linked bytes;
  index census `2026-11-04 16:16`, revision `2f0cb97f52`.

The preview is a preservation check, not a new census or real-link measurement.
No ledger names, aliases, pins, header definitions or source paths change.

## Remaining queued consumers

The supported seven-file `header_adopt_lane.py adopt --apply` trial initially
accepted none; all failed trial edits were restored. The weapon consumer above
was then reconciled manually and accepted. The other six remain unchanged:

- `Common/Thing/ModuleFactoryInit.cpp`: including the canonical ancestry
  redefines the donor `ModuleData` class (C2011).
- `GameLogic/Object/SpecialPower/CashHackSpecialPower.cpp`: canonical ancestry
  conflicts with existing donor base declarations (C2011).
- `CashHackSpecialPowerModuleDataCtor.cpp` and
  `CashHackSpecialPowerModuleDataDtor.cpp`: their private vector member is
  `_STL::vector<CashHackUpgrades>`, while the canonical header deliberately
  retains twelve opaque bytes. Adoption cannot equate those member types.
- `CashHackUpgradesCopyCtor.cpp`: its four-byte zeroing member `m_amount`
  differs from the header's integer `m_amountToSteal`; the old member
  initializer is invalid after the swap (C2614).
- `SpecialPowerModuleDeletingDtors.cpp`: its artificial `EmitVtableTag *`
  constructor has no canonical declaration (C2511).

Next useful work: reconcile donor base declarations for the two donor-backed
consumers, recover a shared vector/member representation from target evidence,
and replace the artificial wrapper-emission constructor before retrying those
units. Existing CashHack TU merge prerequisites remain open; no merge or
clearance of those consumers is claimed here.
