# Adopt canonical Vector4 storage in horde rider release

Base `12902e9e1b47ba404b637f2e5334820e7c237a9b`. Source `Code/GameEngine/Source/GameLogic/Object/Contain/HordeContain/HordeTransportContainRva00477BA2.cpp`; scope claimed before editing.

Replace the private sixteen-byte Vector4 with the existing registered header and use its X field for the three matrix-column loads. Target row offsets and the independently established bone-matrix layout agree. Native parent and both compiler EH rows remain exact despite local label renumbering, with an EXACT EH graph. The first compile exposed a second inlined column-access expression still spelling x; it was corrected consistently before acceptance. The default TU-evidence run was inspected first: its WorldBuilder filename lead and existing comments do not supply a current approved native anchor for the 52-row run. No TU map or guessed identity was asserted; those claims were released. External ROTWK crash follow-ups are documented separately and not counted as an implemented crash fix.

The normal byte gate preserves 3 matched row(s), with existing
extents 447, 10, 8 bytes. Actual COFF comparison
preserves 38 external code bodies and relocation lists.
Added external code definitions: zero. Removed definitions:
none.

All 44 non-debug sections preserve their bytes and relocation target positions. Defined compiler-local $T/$L labels are resolved by section/value; external names are never normalized.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, pin, alias, data row, source path or baseline changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/GameLogic/Object/Contain/HordeContain/HordeTransportContainRva00477BA2.cpp: LINKS  LINKED 457 -> 457 bytes (census 2026-10-31 22:52 at e78b61f1b2; file's own bytes 457)
link_check: 1 of 1 link cleanly; LINKED 457 -> 457 bytes (2.9s)
```

Controls: ignored `build/six-each-no-qwen-20261101-0015/b2-01-*` and matching diagnostic package. No Qwen or other local inference; shared build cap ten, no Unreal process changed.
