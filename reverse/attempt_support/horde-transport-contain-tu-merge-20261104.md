# HordeTransportContain.cpp TU merge: donor reconciliation findings (2026-11-04)

Target: `tools/tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/Object/Contain/HordeContain/HordeTransportContain.cpp`
(5 donors, 44 rows). Dry run at 6c92744fde: accepted none.

## Donor verdicts (dry run, target facts from the compiler)

- `HordeTransportContainCtor.cpp`, `HordeTransportContainIface20.cpp`: C2504 `TransportContain` base class undefined
  once the donor-local copy is dropped; they model TransportContain/OpenContain as multiple-inheritance
  interface stacks (Iface00..Iface34, OIface00..OIface34), the seed as a single polymorphic chain.
- `HordeTransportContainIsValidContainerFor.cpp`: C2039 `isValidContainerFor` not a member of the seed's class.
- `HordeTransportContainRva00477BA2.cpp`: C2556 private `Matrix3D::Get_X_Vector` clashes with matrix3d.h.
- `HordeTransportContainNestedRiders.cpp`: C3861 `x3C` (primary slot 15) not in the seed's class.

`tu_views.py --dry-run` conflicts: `HordeTransportContain` (seed `__declspec(novtable)`, donors plain),
`TransportContain`/`OpenContain` (base clauses), `Object` (overlapping field views), `HordeTransportContainModuleData`
(class vs struct), `Rva0046247D::rva0046247D` (seed opaque, NestedRiders `__declspec(noinline)` visible body).

## NestedRiders (0x0047748E) needs the visible callee; the seed's 0x004779F9 needs it opaque

Structural inference from builds (each via `./build.sh`, then reverted):

- Donor with the `x3C` call through a slot view and the seed's opaque `Rva0046247D` declaration: flow exact,
  callee-saved registers rotated (loop iterator ebx instead of esi, contain edi instead of ebx).
- Seed with the visible `noinline` body (in-class, or out-of-class placed after 0x004779F9's body):
  0x004779F9 fails with the same kind of rotation plus a spilled outer iterator; redeployOccupants unaffected.
  So placement order does not isolate the callers (c2 sees the body module-wide).
- Opaque callee, 0x0047748E reshaped: copying the outer element with `memcpy` (as 0x004779F9 does) gives retail's
  esi iterator; `contain`/`object` stay swapped (edi/ebx vs retail ebx/edi) across 12 further shapes
  (declaration order, if-nesting, early continue, typed locals, slot-view local, drawable typing).
  Best body (outer memcpy, everything else as the donor):

```cpp
    for(IntList::iterator i=outer.objects->begin();i._M_node!=outer.objects->end()._M_node;++i) {
        void *outerObject;
        memcpy(&outerObject,&*i,4);
        RiderContain *contain=(RiderContain*)((Rva0047A040Base9E0*)((char*)this+0x11D))->rva00588B8A(outerObject);
        ...
            ((Rva0047748EHordeSlots*)this)->x3C(contain,object);
```

Next step: either find the remaining contain/object shape under the opaque callee, or reshape 0x004779F9 to match
with the visible body (retail may have had one view for the whole unit). The other four donors need one
reconciled TransportContain/OpenContain hierarchy first (header-lane work).
