# Adopt canonical Vector4 in W3DModelDrawParticleBones

Base `92f12c3fc4e42305d6c26c1da9290c17cc5d20cd`. Source `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawParticleBones.cpp`; scope claimed before editing.

Use the existing registered Vector4 header and retain native storage offsets, code and provider bindings. Source-specific local helpers preserve the original inline copy/read shape where needed.

The normal byte gate preserves 9 matched row(s), with existing
extents 2175, 10, 5, 8, 11, 11, 5, 8, 8 bytes. Actual COFF comparison
preserves 66 external code bodies and relocation lists.
Added external code definitions: none. Removed definitions:
none.

All 78 non-debug sections preserve their bytes and relocation target positions. Defined compiler-local $T/$L labels are resolved by section/value; external names are never normalized.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, native-address pin, alias, data row, source path or baseline changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawParticleBones.cpp: LINKS  LINKED 2,190 -> 2,190 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 2,190)
link_check: 1 of 1 link cleanly; LINKED 2,190 -> 2,190 bytes (3.1s)
```

Controls: ignored `build/up-to-eighteen-each-20261102-2226/b2-11-*` and matching diagnostic package. Local inference not needed for this scope; build pool14 per repository, aggregate28 logical CPUs available; no local model needed.
