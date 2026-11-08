### LINK-015: naming `VectorClass<Vector3>`'s deleting destructor proved the consumers' inlined copies wrong

**Status: Census-confirmed for the four repaired units; the two teardown units' repair landed 2026-10-29, awaiting census. Updated: 2026-10-29; inspected revision: 8e3c23e9b9.**

- **Evidence / scope:** 4e0bfa8260 named retail 0x000F1CF7 as
  `??_G?$VectorClass@VVector3@@@@UAEPAXI@Z` (34 B: vptr store, call to the kept
  `Clear` 0x000F0CD4, `pop ecx` after `operator delete`) and rowed it in
  `vector_class_vector3_ctor.cpp`. Once it had a retail address, the seven other
  copies were proven wrong: they inline `Clear` (/O2), and the /G7 ones clean up with
  `add esp, 4`. The first in link order, `collect.cpp`'s, was the one kept, so the
  census at ef9c691284 lost `pointgr.cpp`, `PointGroupClassRva0017A890.cpp`,
  `DX8SkinClearVisibleList.cpp`, `Rva007B7280Siblings.cpp` and `Rva007B73C0.cpp`,
  all linked at d2636bb381 (`reverse/link_status.csv` history). The owner's copy is
  only `unknown`, never `retail`: its DIR32 to `??_7?$VectorClass@VVector3@@@@6B@`
  (0x007CEFAC) has no data row, so no proven copy lets the wrong ones stand
  (retail-truth-3).
- **Completed:** `collect.cpp`, `mesh.cpp`, `DX8SkinClearVisibleList.cpp`,
  `PointGroupClassRva0017A890.cpp` and `pointgr.cpp` declare
  `~VectorClass<Vector3>` decl-only, so cl synthesizes neither `??_G` nor the
  `VectorClass<Vector3>` vtable there. Declaring `Clear` decl-only instead is not
  enough: the /G7 units still differ (`add esp, 4`), and `pointgr.cpp`'s
  `Rva00912CF0` inlines `Clear` as retail does. `pointgr.cpp` explicitly
  instantiates the virtuals the vtables used to bring: its rowed `ID(T const *)`
  (0x001298B0, /G7, retail-proven, now the first copy) and `ID(T const &)` and
  `operator==`, which the other units only declare. `vector_class_vector3_ctor.cpp`
  declares `ID(T const *)` decl-only: its non-/G7 copy (wrong) would otherwise be
  the first. `./build.sh`: 90/90 rows exact across the six sources.
  `tools/link_check.py` against the 763dc8759f index with all nine current objects
  (including `FXShaderRendererSkin.cpp`): `PointGroupClassRva0017A890.cpp`
  0 -> 11,964 B, `pointgr.cpp` 0 -> 10,565 B, `DX8SkinClearVisibleList.cpp`
  0 -> 1,613 B, `vector_class_vector3_ctor.cpp` 0 -> 194 B (+24,336 B);
  `FXShaderRendererSkin.cpp` keeps 937 B; `collect.cpp` and `mesh.cpp` keep only
  their earlier, unrelated blockers.
- **Remaining / next check:** `Rva007B7280Siblings.cpp` (353 B) and
  `Rva007B73C0.cpp` (59 B). Retail's teardowns inline both the destructor and
  `Clear`, so these /O2 units must keep both inlinable, and cl synthesizes their
  own inlined `??_G`, which loses while no copy is proven. Either a verified home
  for the 0x007CEFAC vtable that proves the owner's copy retail (retail-truth-3
  then lets the wrong copies stand), or consolidating the teardowns back into
  their retail TU, `pointgr.cpp`, would clear them. No source trial; no hatch
  (`#pragma optimize`) considered.
- **Clearance:** preview scope (the units above) on current objects.
- **Census confirmation:** the census at d1f046749a (2026-10-26 13:18) links
  `pointgr.cpp`, `PointGroupClassRva0017A890.cpp`, `DX8SkinClearVisibleList.cpp` and
  `vector_class_vector3_ctor.cpp`; `Rva007B7280Siblings.cpp` and `Rva007B73C0.cpp` still
  lose one COMDAT each, as expected.

**Destructor specialization trial (2026-10-26, inspected `896af216804e`):** a TU-local `dllimport` plus `forceinline` specialization of the existing Vector3 destructor, retaining the header's qualified `Clear()` operation, does not suppress the losing deleting destructor and changes both `rva007B7280` and `rva007B7400`. The byte gate fails 2/6; the trial is fully reversed. The restored source passes 6/6 and retains its original single blocker with the current owner and sibling objects. Raw outputs: `build/link-worker-20261026-w2/vector-inline-preview.log`, `vector-inline-build.log`, `vector-restored-preview.log` and `vector-restored-build.log`. Do not repeat this specialization. The native table ownership or approved TU consolidation prerequisite above remains; census confirmation is pending.

- **Teardown and table audit (2026-10-26, inspected `896af21680`, index `d1f046749a`):** `build/link-report.md` and `build/link-worker-20261026/` records two reverted `Rva007B73C0.cpp` trials. An extern-template destructor replaces the 59-byte teardown with an unresolved destructor jump; an inline-only imported specialization also changes the teardown and leaves the losing deleting destructor. Final byte verification restores the original 59-byte body and the original single COMDAT finding. The proposed vtable-ownership route has an additional prerequisite: the six native table slots at `0x007CEFAC` point to RVAs `0x000F1CF7`, `0x000F1C16`, `0x000F0BF1`, `0x000F0CD4`, `0x000F0DC5`, `0x000F0E20`. The current Vector3 table instead names its pointer-ID owner at `0x001298B0`, while native slot 5 is the 27-byte TCB-class pointer-ID row at `0x000F0E20`. A data row cannot simply assert that these bindings agree. Next check: reconcile the native class/fold identities and every table slot before admitting a full table owner. The constructor and resize providers still preview LINKS; the two teardown units remain blocked. Census confirmation remains pending.

**Assigned collection recheck (2026-10-27, inspected `97c23353111e60304b56434c02d20bee3465d83f`, index `5ce093a71a`):** current `collect.cpp` remains U14/L4 and all six rows remain exact, including the Clone unwind row and the ProxyClass-vector assignment. Its remaining losing copies are RenderObjClass::Is_Visible, Set_Collision_Type and both Get_Bone_Transform overloads; the unresolved ProxyClass-vector and persistence interfaces remain separate from the earlier Vector3 deleting-destructor repair. The current camera, height-map, vector and native row providers are included in the paired preview. Reconcile the shared RenderObjClass and ProxyClass interfaces before removing collection implementations that emit the retained rows. No source edit, new fold admission or additional clearance is claimed; census confirmation remains pending.

**Collection recheck (2026-10-30, base `c647a75e55`, index `12b9e7a7c0`,
2026-10-30 10:11 UTC):** the current five-row unit retains U14/L4 and
LINKED 0 -> 0 (148 authored bytes). The same RenderObjClass and ProxyClass
prerequisites above remain. No source trial or clearance is claimed; the
claim was released and the pass moved to independent stale header debt.
[Scope and verification](../../reverse/attempt_support/browser-shader-stale-msheaders-20261030-codexb4.md).

**Inline-depth trial (2026-10-27, inspected `87e6100d33`, index `bf3dd31211`):** a trailing `#pragma inline_depth` in `Rva007B7280Siblings.cpp` (not a counted hatch) applies to the whole unit, teardowns included, not only to the compiler-generated `??_G` emitted at its end. `inline_depth(1)` stops the teardowns inlining the destructor (`./build.sh` 0/6); `inline_depth(2)` keeps 6/6 but the `??_G` still inlines `Clear` (same `wrong` digest `ac2be0dc8c7c`). Reverted; do not repeat. The vtable-owner or TU prerequisite above stands (0x007B7280/0x007B7400 have no approved TU in `reverse/tu_map.csv`).

**Flag and auto_inline trials (2026-10-27, inspected `06e31393de`):** retail's 34-byte `??_G?$VectorClass@VVector3@@@@UAEPAXI@Z` at 0x000F1CF7 is the /O1 shape (vptr store, out-of-line `Clear`, `pop ecx` after `operator delete`), so any /O2 unit that inlines the destructor emits a losing copy, as retail's own /O2 consumers must have. Building `Rva007B7280Siblings.cpp` with `/G7 /O1` makes its `??_G` that 34-byte shape but fails the teardown bodies (`./build.sh` FAIL); a trailing `#pragma auto_inline(off)` makes the `??_G` call `??1` out of line (not retail either) and also fails them. Both reverted; do not repeat. The unit links only through the vtable-owner/TU prerequisite above or a census keep-rule that tolerates a loser retail itself carried.

**Vtable-identity repair, verified but not landed (2026-10-27, seat halilkkaya-lk2, inspected `d16a31e4dc`, index `73061d9452`):**
[The handoff and patch](../../reverse/attempt_support/link015-vector3-vtable-identity-20261027/readme.md)
resolve the table-slot prerequisite above. Retail's 0x00BCEFAC is
VectorClass<Vector3>'s table (the teardowns and the 0x000F0D2F constructor
store it), and its slots 1, 4 and 5 are 0x000F1C16, 0x000F0DC5 and 0x000F0E20:
the owner unit's own flags compile VectorClass<Vector3>::operator==,
ID(T const &) and ID(T const *) to exactly those bodies (masked compare EXACT;
the TCBClass rows there are their ICF twin). The 0x001298B0 row that spells
`?ID@?$VectorClass@VVector3@@@@UAEHPBVVector3@@@Z` is
VectorClass<TextureStatisticsStruct>::ID(T const *): only slot 5 of the two
TextureStatistics tables 0x00BD1274/0x00BD14EC reaches it, it lies in the
statistics.cpp block, and that misnamed row is what makes RetailTruth judge
the owner's table wrong at slot 5, so the owner's `??_G` stays `unknown`.
With the owner emitting the three virtuals, pointgr/collect/DX8Skin/teardowns
declaring them decl-only, and the row renamed into TextureStatisticsVectorID.cpp
(two `/alternatename` lines dropped there), `./build.sh` passes 91/91 across
the seven sources and `link_check.py` over 19 units links both teardowns
(0 -> 353 B, 0 -> 59 B; total 30,747 -> 31,159 B) with no peer regression.
Not landed: pointgr.cpp is file-locked by another seat's RVA claims, and moving
a matched row to a new name and source has no admitted tool path for this seat.
Next check: once pointgr.cpp is free, apply the patch with the row move and
rerun the 19-unit preview listed in the handoff.

**Vtable-identity repair landed (2026-10-29, seat claudeb2, base `8e3c23e9b9`, census index `d92e7e6635`):**
the handoff patch applied with one change: the 0x001298B0 row (renamed by hand to
`?ID@?$VectorClass@UTextureStatisticsStruct@@@@UAEHPBUTextureStatisticsStruct@@@Z`,
tombstoned in `reverse/deleted_rows.csv`, since `rename.py function` cannot change
template arguments) moved into its approved TU `statistics.cpp`, which now defines
and instantiates it; `TextureStatisticsVectorID.cpp` keeps the definition only so
the DynamicVectorClass forwarder inlines it. `TextureStatisticsVector.cpp` also
dropped its two `/alternatename` lines onto the Vector3 name (alternatename -4 in
all). `./build.sh` on the nine touched sources: 137/137. `link_check.py` over 20
units (the handoff's 19 plus `statistics.cpp`): 18 link, `collect.cpp` and
`tcbspline.cpp` keep only their earlier unrelated blockers; `Rva007B73C0.cpp`
0 -> 59 B, `Rva007B7280Siblings.cpp` 0 -> 353 B, `statistics.cpp` 986 -> 1,019 B,
`pointgr.cpp` 10,565 -> 10,532 B (the row moved); total 30,747 -> 31,179 B.
Census confirmation pending.

**2026-11-08 global-teardown bridge recheck:** all six live teardown rows in
Rva007B7280Siblings.cpp pass; ordinary preview remains LINKS/353 against
d171e84869. Its /O2 deleting copy is still71B versus the rowed constructor
owner's34B. A whole-class extern-template declaration removes that copy and
the table but fails the two Vector3 teardown bodies (4/6 exact), so no source
edit is retained. Current dest queries still give only neighbour heuristics
for 0x007B7280/0x007B7400, no approved TU for a merge. The bridge/provider and
Resize/EH boundary remain open; there is no new census or image clearance.
[Private trial and remaining prerequisites](../../reverse/attempt_support/vector-global-provider-20261108/README.md).
