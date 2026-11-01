# Use canonical Matrix3D storage in shadow mesh bounds

Base `3c29366baf9dd5a9f47171a6118ad25c52acc9af`. Source `Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadowRenderMeshVolumeBounds.cpp`; scope claimed before editing.

Adopt the existing registered storage and retain the witnessed target interfaces, field offsets, arithmetic/copy grouping and provider bindings. No new native identity or behavior is inferred.

The normal byte gate preserves 1 matched row(s), with existing
extents 1241 bytes. Actual COFF comparison
preserves 9 external code bodies and relocation lists.
Added external code definitions: none. Removed definitions:
?Get_Translation@Matrix3D@@QBEXPAVVector3@@@Z.

Removed definitions have incoming edges only from debug sections or other removed definitions; no retained runtime code or data points into the removed component. Retained runtime calls do not change.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, native-address pin, alias, data row, source path or baseline changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadowRenderMeshVolumeBounds.cpp: LINKS  LINKED 1,239 -> 1,239 bytes (census 2026-11-01 20:19 at 0156fc269e; file's own bytes 1,239)
link_check: 1 of 1 link cleanly; LINKED 1,239 -> 1,239 bytes (3.8s)
```

Controls: ignored `build/six-each-half-resources-20261101-2150/b2-06-*` and matching diagnostic package. Local inference not needed for this scope; build cap fourteen; memory budget47GiB, no Unreal process changed.
