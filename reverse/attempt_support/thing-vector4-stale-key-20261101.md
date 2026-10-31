# Make the Vector4 dependency explicit in the Thing constructor

Base `6e7a2b6c23317a37582b23bcec9f9dfa4791c23f`. Source `Code/GameEngine/Source/Common/Thing/ThingConstructor.cpp`; scope claimed before editing.

The Thing source already receives canonical Vector4 through Matrix3DData, but its owning Vector4 acceptance requires the explicit registered-header dependency. Add that direct include and retain the existing type/layout and complete matched scope. This makes the dependency explicit and permits the owning tool to retire its old queue key; no new native recovery is claimed. Other class adoptions stay separate.

The normal byte gate preserves 3 matched row(s), with existing
extents 13, 28, 187 bytes. Actual COFF comparison
preserves 15 external code bodies and relocation lists.
Added external code definitions: zero. Removed definitions:
none.

All 19 non-debug sections preserve their bytes and relocation target positions. Defined compiler-local $T/$L labels are resolved by section/value; external names are never normalized.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, pin, alias, data row, source path or baseline changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/Common/Thing/ThingConstructor.cpp: LINKS  LINKED 228 -> 228 bytes (census 2026-10-31 22:52 at e78b61f1b2; file's own bytes 228)
link_check: 1 of 1 link cleanly; LINKED 228 -> 228 bytes (2.8s)
```

Controls: ignored `build/six-each-no-qwen-20261101-0015/b2-03-*` and matching diagnostic package. No Qwen or other local inference; shared build cap ten, no Unreal process changed.
