# RenderVolume canonical geometry adoption, 2026-11-04

Inspected revision: `d61f064279`. Source: `Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadowRenderVolume.cpp`, retail RVA `0x000F49D0`, 231 bytes.

Replace the private padded W3DShadowGeometry and W3DShadowGeometryMesh declarations with their existing canonical headers. Read the canonical mesh skin flag `m_30` at the same retail offset +0x30. No shared-header, ledger, compiler-profile, alias, pin or source-path changes.

Verification:

- Normal `./build.sh` before and after: 1/1 matched, all 231 bytes exact; no unresolved string/float/import reference checks. See the two build logs.
- `find_declared_unmatched.py`: all defined functions already matched.
- `header_adopt_lane.py accept` individually passes W3DShadowGeometry, W3DShadowGeometryMesh and Drawable, retiring three queue rows through their owner. Drawable.h was already included and no private Drawable body remained; its queue row was stale.
- [Object facts](object-facts.json): all body digests and sizes, exclusive definitions, undefined references and weak externals are unchanged. The sole COMDAT name change is getMesh's return type from the private `struct` mesh tag (PAU) to the canonical `class` tag (PAV); its 14-byte body is identical. The RenderVolume body's digest is unchanged.
- `link_check.py`: LINKS, preview retains LINKED 231 -> 231 bytes against census index `f6d845ecd4`, 2026-11-04 13:15. This is preview evidence, not a new census or headline link gain.
- `check_csv.py` and `git diff --check` pass.

Remaining prerequisites:

- RenderObjClass's private view remains. The supported adoption trial stops at rendobj.h's unresolved `always.h`; its include environment must be reconciled before assessing the native vtable/profile requirements. The failed trial is restored; its queue row remains.
- The other six W3DShadowGeometry consumers in the picker batch remain queued. The supported automatic trial refuses duplicate StringBase declarations, incompatible name-storage/mesh-record views, ambiguous nested field renames and include/layout problems, as detailed in `w3dshadowgeometry-adopt.txt`. No failed source trial was retained.

The initial HostClass005C8E0A consolidation selection wrote nothing because another worker held folded RVA 0x0007FAB3, as already documented in the earlier hostclass handoff. Its four proposed units still preview LINKS 557/557 bytes. Its file claims were released. Geometry.cpp's readonly view survey confirms the existing canonical-header, overlapping GeometryShape and float/int BfmeElem60 prerequisites; no merge was retried and its scope claim was released.
