# Wave-owner virtual-base offsets, 2026-11-08

The default picker served Rva0030CAA9OwnerCtor.cpp for a no-retail-slots
refusal at RVA 0x008089C8. Both owner virtual-base tables are exact offset
data: the Rva00330C50 table at 0x008089C8 contains (-4, 116), and the
Rva0053805DBase table at 0x008089D0 contains (-24, 144). Each is an independent
eight-byte compiler section with no relocations. `proof.json` records the
current object hash, exact native/compiled bytes and the selector result.

All 15 source rows, one parent EH graph, its literal and six float references
pass normal verification; the source is unfrozen. Current-object preview is
LINKS/409 authored bytes against index eba83a23be (2026-11-08 14:08).
There is no source, data-ledger or generated-queue edit and no progress claim.

This is the same false reject as the earlier Army-icon offset table: data_ledger
intentionally uses kind=vtable for ??_8 tables, but the positive-slot bridge
selector admits them. The file claim for tools/vtable_bridge.py was refused
because another worker holds it; no tool or test was edited. Exclude only
positively identified ??_8-only rows, preserving mixed/unknown names and real
??_7 tables, with the negative controls described in the
[earlier handoff](../army-icon-vbtable-selector-20261108/README.md).

The same source has two actual function tables requiring bridges. Their
complete class, native slot targets and kept-provider checks remain separate
work. Correct virtual-base offsets and a scoped preview do not clear those
tables or prove the game runs.
