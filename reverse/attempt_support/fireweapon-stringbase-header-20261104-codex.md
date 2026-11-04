# FireWeaponUpdate StringBase donor prerequisite (2026-11-04)

Base: `c685a827a7`. Preview index: `a62ac1c10b`, census 2026-11-04 07:28.
Scope: `Code/Libraries/Source/WWVegas/WWLib/string_base_clear.cpp`.

The current FireWeaponUpdate merge dry run accepts no donor. The cleanup
wrapper donor redeclares StringBase after the destination has included the
shared header, producing C2953/C2955. Replace that private template and its
already-header-defined bodies with the existing frozen shared header. Keep
all ten explicit instantiations and the leak-hook body. No shared header,
ledger row, pin, alias or register changes.

Verification:

- `./build.sh Code/Libraries/Source/WWVegas/WWLib/string_base_clear.cpp`:
  10/10 matched; string, float and import references pass.
- `find_declared_unmatched.py` before/after: all defined functions matched.
- `class_gate.py` passes.
- Ordinary `link_check.py` before/after: LINKS, 18 -> 18 unique authored bytes.
  This is a preview against the named index, not a new census measurement.

The module-data constructor's explicit vtable declaration still conflicts
with the destination's virtual class. The replacement method donor has a
flat FireWeaponUpdate view with the owner under the real UpdateModule bases;
its method is absent from the destination declaration. Weapon-header work
is held by a peer, so no Weapon definition or provider is changed here.
The mixed donors remain out of scope. Retry the guarded merge after this
prerequisite, retaining only its independently verified composition.
