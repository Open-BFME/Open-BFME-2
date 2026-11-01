# Adopt canonical Vector4 rows in GPU particle transforms

Base `34de65d43014062ee061d499918c20d3843a6bfd`. Source `Code/GameEngine/Source/GameClient/System/FXParticleSystem/GpuDrawModuleDoParticles.cpp`; scope claimed before editing.

Use the registered Vector4 storage. Preserve component-wise matrix copying locally and use a TU-local derived row construction helper where the old private Vector4 offered a four-float constructor. Replace constant row indexing with the named components, retaining transpose grouping, identity-transform writes and all rendering, reference-count and shader cleanup behavior. No GPU workload is launched by this verification.

The normal byte gate preserves 4 matched row(s), with existing
extents 779, 10, 8, 8 bytes. Actual COFF comparison
preserves 19 external code bodies and relocation lists.
Added external code definitions: none. Removed definitions:
none.

All 24 non-debug sections preserve their bytes and relocation target positions. Defined compiler-local $T/$L labels are resolved by section/value; external names are never normalized.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, pin, alias, data row, source path or baseline changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/GameClient/System/FXParticleSystem/GpuDrawModuleDoParticles.cpp: LINKS  LINKED 787 -> 787 bytes (census 2026-10-31 22:52 at e78b61f1b2; file's own bytes 787)
link_check: 1 of 1 link cleanly; LINKED 787 -> 787 bytes (2.9s)
```

Controls: ignored `build/six-each-no-qwen-20261101-0015/b2-07-*` and matching diagnostic package. No Qwen or other local inference; shared build cap ten, no Unreal process changed.
