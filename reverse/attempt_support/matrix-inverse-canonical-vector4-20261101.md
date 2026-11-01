# Use canonical Vector4 storage in matrix inverse forwarding

Base `1c6e7e57115b02ae05bb0750aafb69754cb0da26`. Source `Code/Libraries/Source/WWVegas/WWMath/Rva007133F0MatrixInverse.cpp`; scope claimed before editing.

Replace the private struct row with the registered Vector4 class. Use direct matrix row/component access and local component copying instead of private Vector4 methods or class-key-sensitive matrix subscript helpers. The local Matrix3D/Matrix4 views retain the same storage and are not promoted to complete application classes. Keep the existing inverse provider declaration and imported Init shape. Preserve all 332 native bytes and the actual call relocation; no native provider/name migration or wider Matrix3D adoption is claimed. A TU-local force-inline empty Matrix4 constructor preserves the native body and emits only an empty constructor copy. The three new emitted definitions (two empty constructors and a 48-byte compiler array iterator) have no relocations and only debug incoming edges; removed subscript copies also have only debug incoming edges. A private imported-constructor experiment changed the body and is rejected. Private-object new-variant check passes.

The normal byte gate preserves 1 matched row(s), with existing
extents 332 bytes. Actual COFF comparison
preserves 1 external code bodies and relocation lists.
Added external code definitions: ??0Matrix4@@QAE@XZ, ??0Vector4@@QAE@XZ, ??_H@YGXPAXIHP6EPAX0@Z@Z. Removed definitions:
??AMatrix3D@@QAEAAUVector4@@H@Z, ??AMatrix4@@QAEAAUVector4@@H@Z, ??AVector4@@QAEAAMH@Z.

Removed definitions have only debug incoming edges in the original object; retained runtime calls do not change.

The additional emitted definition(s) have no relocations and only debug incoming edges; their exact bytes are checked independently in the local controls. An empty canonical Vector4 constructor is `mov eax,ecx; ret`; the compiler array-constructor iterator, when present, is the 48-byte MSVC helper in this profile. Neither adds a call to retained runtime code. No new native row or authored-byte gain is claimed. Full non-debug section equality is not claimed for this unit.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, pin, alias, data row, source path or baseline changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/Libraries/Source/WWVegas/WWMath/Rva007133F0MatrixInverse.cpp: LINKS  LINKED 332 -> 332 bytes (census 2026-11-01 09:19 at 0d24c60eef; file's own bytes 332)
link_check: 1 of 1 link cleanly; LINKED 332 -> 332 bytes (3.5s)
```

Controls: ignored `build/one-each-no-qwen-20261101-1231/b2-02-*` and matching diagnostic package. No Qwen or other local inference; shared build cap ten, no Unreal process changed.


Outgoing batch audit at immutable base 1c6e7e57115b02ae05bb0750aafb69754cb0da26 returns INCONCLUSIVE (exit2): index/compiler baseline differs and affected consumer 0CreateAHeroManager21FE49.cpp lacks a current receipt. The bounded own-source preview preserves LINKED332->332 at 0d24c60eef, with no new census gain or complete consumer/runtime claim. Private-object new-variant check passes. Complete consumer selection is UNKNOWN.
