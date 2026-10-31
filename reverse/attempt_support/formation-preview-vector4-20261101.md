# Adopt canonical Vector4 rows in formation previews

Base `d8ae2a72ed9e81c33123b5c3543415e29feeb2d7`. Source `Code/GameEngine/Source/GameClient/InGameUIUpdateFormationPreview.cpp`; scope claimed before editing.

Use the registered Vector4 storage and its existing Set helper. Spell the twelve constant matrix components directly in the local Transform_Vector helper, preserving expression grouping and its alias-safe temporary branch. Keep all formation selection, hash, expiry, geometry, STL lifetime and EH behavior unchanged; other class adoptions remain separate.

The normal byte gate preserves 6 matched row(s), with existing
extents 2462, 10, 5, 5, 8, 8 bytes. Actual COFF comparison
preserves 38 external code bodies and relocation lists.
Added external code definitions: ??_H@YGXPAXIHP6EPAX0@Z@Z. Removed definitions:
none.

The additional emitted definition(s) have no relocations and only debug incoming edges; their exact bytes are checked independently in the local controls. An empty canonical Vector4 constructor is `mov eax,ecx; ret`; the compiler array-constructor iterator, when present, is the 34-byte MSVC helper. Neither adds a call to retained runtime code. No new native row or authored-byte gain is claimed. Full non-debug section equality is not claimed for this unit.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, pin, alias, data row, source path or baseline changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/GameClient/InGameUIUpdateFormationPreview.cpp: LINKS  LINKED 2,473 -> 2,473 bytes (census 2026-10-31 22:52 at e78b61f1b2; file's own bytes 2,473)
link_check: 1 of 1 link cleanly; LINKED 2,473 -> 2,473 bytes (2.8s)
```

Controls: ignored `build/six-each-no-qwen-20261101-0015/b2-06-*` and matching diagnostic package. No Qwen or other local inference; shared build cap ten, no Unreal process changed.
