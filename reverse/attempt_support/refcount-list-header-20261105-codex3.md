# RefCountClass list consumer header adoption

Inspected revision: 23bbb5c0c1, 2026-11-05.

`RefMultiListRenderObjRemove.cpp` now includes `RefCountData.h` instead of
declaring a private one-slot RefCountClass. Its only template instantiations
are for the local RenderObjClass, which inherits RefCountClass directly.
The two decrement expressions now use the canonical `NumRefs` field;
both old and canonical fields occupy +4 and both deletion calls use slot 0.
No RenderObjClass declaration, shared header, pin or alias was edited.

The automatic field mapper refused to infer the member through template T.
The explicit-instantiation and base-class declarations establish that binding
for both expressions. After this source change, `./build.sh` passes both
retail rows (RVA 0x0006EF4E, 47 bytes; RVA 0x0006EF8C, 33 bytes), and
`find_declared_unmatched.py` reports no unowned body.

`BfmePod248.cpp` already included RefCountData.h before this pass and needed
no source edit. Its RefCountClass queue row was stale.

`header_adopt_lane.py accept --class RefCountClass` passed separately for
both units and retired their two queue rows. Acceptance includes fresh-object
byte verification and a link preview that preserves census-linked bytes.
This is debt retirement, not a new census measurement or runtime result.
Neither source has data-, identity- or hatch-baseline keys to transfer.

The automatic MeshClassRender trial still fails its Render row. The
MeshClassRenderWithFXMaterial trial still needs the private Dec_Ref API.
Both source files were restored by the adoption tool. Previously documented
provider/teardown prerequisites in LINK-241 were read, not retried without
new evidence. Their queue rows remain for their owning repairs.

All nine claimed source files passed the pre-edit declared-unmatched check.
No source paths moved, and no protected baseline was changed.
