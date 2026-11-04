# Stance-button header adoption and constructor prerequisite

Inspected revision: `b6311900bd`, 2026-11-04; worker `yasinschroeder-codexb`.

## Landed scope

`Code/GameEngine/Source/GameClient/GUI/InGame/Tactical/InGameToggleStanceCommandButtonCtor.cpp`
now includes canonical `StancesBehavior.h` and `CommandButton.h`, removing both
private class bodies. The existing `Drawable.h` include already satisfies its
queued adoption. All three queue rows were retired only by
`header_adopt_lane.py accept --class StancesBehavior|CommandButton|Drawable`.

Target facts: the native constructor accesses listener storage at module +0x20
and CommandButton's three-word stance range at +0x234. These offsets are documented
by the canonical headers' constructor/listener evidence. The existing neutral
append view and vector<int> range view retain those accesses without inventing
the listener container's original identity. No shared header, alias or pin changes.

Verification before scoped naming:

- `./build.sh` on the GUI TU and restored StancesBehaviorCtor: 8/8 functions,
  1/1 explicit data row; string, float and import reference checks pass.
- The four GUI EH labels were renumbered by the includes and verified against
  the exact parent's EH graph by the normal builder.
- `find_declared_unmatched.py` on both modified trials: all definitions matched.
- Each of the three header acceptance commands passed for the GUI TU.
- `link_check.py` on current objects: GUI 523 -> 523 linked bytes;
  restored StancesBehaviorCtor 54 -> 54; total 577 -> 577. This is a preview,
  not a new census. Its census reference is 2026-11-04 17:56, `8c757ea0db`.

## Constructor trial: reverted, LINK-287

The automatic five-source StancesBehavior adoption still refuses:

- ModuleFactoryInit: private Module conflicts with canonical Module.
- StancesBehavior.cpp: m_30 field binding is not proven by the field-renaming tool.
- Object.cpp: its private UpdateModule's explicit m_vtable has no canonical field.
- The GUI's old observers member and the constructor's old m_member20 cannot map
  to the canonical secondary storage base.

A manual constructor-only trial kept the explicit 52-byte vtbl_00C424DC data row,
replaced the private UpdateModule/StancesBehavior declarations with the canonical
StancesBehavior.h, and reduced its body to:

```cpp
StancesBehavior::StancesBehavior(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData), m_stance(0)
{
}
```

The 54-byte constructor and explicit data row both byte-verified. Header acceptance
correctly refused the link preview: 54 -> 0 linked bytes, sole reported unresolved
`?GetSnapshotName@StancesBehavior@@MBEPBDXZ`. Target table slot 2 at VA 0x00C424DC
points at RVA 0x0045EFB6. That body already belongs to
`?Rva0045EFB6Get@@YAHXZ` in `Code/GameEngine/Source/Common/ConstIntGetters4.cpp`;
this is an existing placeholder identity prerequisite, not an unrowed regression.
The canonical header declares a virtual const char* getter; the current owner is
an int-returning free function. A vtable-slot match is structural evidence, not
canonical name proof under docs/naming.md. Reconcile the owner through the naming
workflow, then retry the constructor and check all class-table consumers.

The trial was restored from its original contents and rebuilt. Both constructor
queue rows remain. No header queue row was removed for a failing unit, no aliases
were added or removed, and no census gain is claimed.

## Scoped naming and final source

Native child `/root/stances_gui_names` proposed the complete constructor packet;
the parent reviewed every mapping and diff and acknowledged the exact proposal.
The supported inventory contained 12 bindings. It did not inventory the compact
StanceToButtonSlot helper despite the explicit selector; no completeness claim
or changes are made for that helper's unsupported bindings.

The normal scoped apply renamed `id` to `objectId`, `it` to `selectedDrawable`,
and `slot` to `stanceButtonSlot`, retaining nine bindings. The two `object`
declarations are in separate branch scopes and retained. Two additional proposals
were refused by the existing protected-vocabulary checks (`key` occurs in a WB
name and `end` in an evidence-tier STL method); they were retained, the false
reject recorded via re_log.py, and no check was modified or bypassed.

Scoped apply's final normal build: **7/7 GUI rows match**, all four EH labels
verified, string/float/import reference checks pass. No header or ledger address
identity changed during naming. The commit hooks recheck the retired header rows
and outgoing link consumers on these final inputs.
