# AttributeModifierAuraUpdateModuleData consumer adoption

Inspected base: `0724c901648b5adec4dce7288eb4386718729f95`.
Scope: the six units served by `next_work.py --claim` for this class.

## Applied

`AttributeModifierAuraUpdate.cpp` includes the existing canonical header and
passes the address of its four-byte `m_objectFilter` member to the existing
partition-filter constructor. The old declaration incorrectly represented the
whole +0x24..+0x13B region as one filter array; this caller only passes +0x24.

`UpgradeMuxSlotOverrides.cpp` includes that header and views the existing
`m_28` member as its local UpgradeMuxData interface when copying the two masks
and calling performUpgradeFX. This preserves the +0x28 member address without
binding another global or changing the shared member contract.

The field offsets and member extents are target facts already documented in
the canonical header. These changes recover no new original field names and
make no claim that the remaining opaque vector storage is a recovered type.

## Verification

- Before and after editing, `find_declared_unmatched.py` reports all defined
  functions matched in both units.
- `./build.sh` over both units: 32/32 rows match; string, float and import
  reference checks pass. Ten renumbered funclet labels verify against their
  parent EH data.
- `header_adopt_lane.py accept --class AttributeModifierAuraUpdateModuleData`
  over both units passes and retires exactly their two header-queue rows.
- Current-object `link_check.py`: both units LINKS; AttributeModifierAuraUpdate
  retains 1,566 B and UpgradeMuxSlotOverrides retains 294 B, total 1,860 ->
  1,860 B. Published census index: 2026-11-05 05:17, `c95fcfcfcd`.
  This is a preview, not a new census or a headline link gain.
- No shared header, destructor provider, alias, pin, source path or ledger
  symbol changes.

## Remaining cohort

The initial automatic adoption tested all six units, retained none, and
restored its trials. The four unedited units retain their queue rows:

- `FamilyDeletingDtors_muse-0ecc.cpp`: C2511 for its synthetic
  `AttributeModifierAuraUpdateModuleData(EmitVtableTag *)` definition, which
  the canonical class does not declare. A replacement mechanism must preserve
  the deleting-dtor row and audit all table consumers (LINK-177), rather than
  add a synthetic constructor to the canonical header.
- `ModuleFactoryInit.cpp`: C2011, ModuleData redefinition through its existing
  ModuleFactory include chain. Reconcile that base-header chain before
  adopting this derived header.
- `AttributeModifierAuraUpdateModuleDataCtor.cpp`: layout discovery compiling
  the canonical header in this unit fails with C1001. The unit has a private
  StringBase-based AsciiString typedef and an UpdateBase teardown; investigate
  those dependencies before attempting the actual constructor swap. C1001
  alone does not establish that the canonical constructor body cannot match.
- `AttributeModifierAuraUpdateModuleDataDtor.cpp`: its typed
  `_STL::vector<AsciiString>` at +0x0C cannot map to canonical `uchar[12]`.
  Reconcile typed member ownership and the exact filter/vector/string/base
  teardown before adoption. The automatic trial does not prove a link loss.

The two consumer failures were resolved manually: the oversized filter array
and the narrower local UpgradeMuxData view do not require changing the
canonical class layout. The four remaining automatic failures are prerequisites
for future work, not newly discovered missing bodies or byte regressions.
