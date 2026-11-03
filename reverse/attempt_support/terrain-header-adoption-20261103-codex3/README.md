# Terrain header adoption and shader prerequisite refusal

Inspected revision: `9ed9c099872815d869d5a39891711c1b59a11fb9`, 2026-11-03.

## Applied: snow renderer

`W3DSnowManagerRender.cpp` now includes the existing `BaseHeightMap.h` instead
of declaring a private BaseHeightMapRenderObjClass with only m_map at +0x37C0.
The header supplies the same field and its approved hierarchy. VertexMaterialClass
already includes the retail RefCountData.h, so the unit sets the donor refcount.h
include guard to prevent importing a second RefCountClass definition. Forward
references supply the three save/load types used by rendobj.h. No shared header,
function ledger, pin, alias, extent or compiler option changed.

The supported adopt tool passed. The owning acceptance command passed and retired
exactly the BaseHeightMapRenderObjClass / W3DSnowManagerRender.cpp header-queue
row. The ordinary build passes the 714-byte render body at RVA 0x0009470F,
one data row and two float references; see [snow-build.log](snow-build.log).
The frozen-file check passes. The per-unit preview reports LINKS and preserves
714 -> 714 census-linked bytes against census 2026-11-03 20:03 at 8661f15284;
see [snow-link.log](snow-link.log). This is one header-debt retirement, not new
matched coverage or a new census measurement. No runtime or whole-game link
verification is claimed.

## Blocked: shader field-name adoption

`W3DShaderManagerSetShroudTex.cpp`, setShroudTex at RVA 0x00076C14, remains
unchanged. Its original ordinary build passed all 11 rowed bodies. The initial
canonical-header layout probe lacked always.h. Adding the existing WW include
roots exposed missing PersistFactoryClass, ChunkSaveClass and ChunkLoadClass
forward references; [shader-header-probe.log](shader-header-probe.log) records
that intermediate compiler diagnostic. Adding those references let the layout
compile and exposed the unused +0x37E8 field's float/int disagreement. The
[failed prerequisite candidate](shader-failed-candidate.diff) reconciles that
unused storage and the map/shroud pointer types to the shared header; its
existing shroud operations explicitly retain their address-derived view.
This candidate was not applied or admitted as a byte-matched adoption.

The next supported adoption stopped with:

```
field renames: /work3/Open-BFME-2/reference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath/vector3.h: unresolved include osdep.h
```

The reference's vector3.h lines 76-78 place osdep.h inside `#ifdef _UNIX`.
The successful compiler layout probe does not take that branch; the field-rename
include inventory scans it anyway. Record this as a false reject, not a source
or compiler mismatch. No verifier was changed and no proof was bypassed. The
candidate was restored from the byte-for-byte original and its frozen-file check
passes. The header-queue row remains. Next useful work is a separate verifier
fix that proves active include resolution while retaining conditional-name
safety, with regression tests; then retry the recorded candidate through the
normal adoption and acceptance commands.
