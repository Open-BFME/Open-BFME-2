# Adopt canonical Vector4 storage in mesh color loading

Base `5315895240076e1a948935c2dfa126d2bfb61911`. Source `Code/Libraries/Source/WWVegas/WW3D2/MeshModelReadDcg.cpp`; scope claimed before editing.

Use the registered Vector4 storage for mesh colors. An anonymous TU-local UnpackedColor derives its storage from Vector4 and retains only the nontrivial copy semantics needed by the return-value conversion. Measured private probes: ordinary trivial return computed dead packed alpha and expanded the body; an out-parameter stored components too early; the nontrivial return view preserves all 562 bytes and every relocation. The two helper constructors retain the original import-inline convention, without native identities. The unsigned unpack is a local helper, so the old unused imported Convert_Color(unsigned) declaration and its present-unmatched marker are removed rather than adding a hatch. Preserve the two remaining conversion markers, the x87 assembly, packed components, fresh alpha and all native side effects.

The normal byte gate preserves 1 matched row(s), with existing
extents 562 bytes. Actual COFF comparison
preserves 1 external code bodies and relocation lists.
Added external code definitions: ??0Vector4@@QAE@XZ. Removed definitions:
none.

The additional canonical empty Vector4 constructor is exactly `mov eax,ecx; ret` with no relocations and only debug incoming edges. It is fully inlined in retained runtime code; no new native row or authored-byte gain is claimed. Full non-debug section equality is not claimed for this unit.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, pin, alias, data row, source path or baseline changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/Libraries/Source/WWVegas/WW3D2/MeshModelReadDcg.cpp: LINKS  LINKED 559 -> 559 bytes (census 2026-10-31 22:52 at e78b61f1b2; file's own bytes 559)
link_check: 1 of 1 link cleanly; LINKED 559 -> 559 bytes (2.8s)
```

Controls: ignored `build/six-each-no-qwen-20261101-0015/b2-05-*` and matching diagnostic package. No Qwen or other local inference; shared build cap ten, no Unreal process changed.
