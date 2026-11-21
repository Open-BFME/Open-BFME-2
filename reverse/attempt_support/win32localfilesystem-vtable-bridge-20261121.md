# Win32LocalFileSystem table 0x0087A9A8 bridge

The real link bridges `??_7Rva00604A5F@@6B@`. Retail's table at
`0x0087A9A8` has 16 slots. The source COMDAT has one, from a placeholder
class `Rva00604A5F` in `Win32LocalFileSystem.cpp`, which declares only
a ctor and a virtual dtor.

## Retail facts

- The ctor at `0x00604A5F` (9 bytes) is `mov eax,ecx; mov [eax],0xC7A9A8; ret`.
  The inlined base ctor's store of `0xC7A974` is dead-store eliminated.
- The dtor at `0x00604A68` (7 bytes) is `mov [ecx],0xC7A974; ret`. It is the
  derived dtor with the base's inline-empty dtor folded in.
- `??_G` at `0x00604A6F` is slot 0 of `0x0087A9A8`.
- The base table at `0x0087A974` has 13 slots: `??_G` at `0x00604A42`,
  then 12 `_purecall` slots.
- The base ctor at `0x006047EA` (9 bytes) stores `0xC7A974`.
- Slots of `0x0087A9A8`:
  - 1, 13, 14: `0x000B3FD0` (shared 1-byte `ret`).
  - 2: `openFile`.
  - 3: `M7F3`.
  - 4: `Virt10`.
  - 5: `M831`.
  - 6: narrow `getFileListInDirectory`.
  - 7: UnicodeString `getFileListInDirectory`.
  - 8: `rva00604A8B`.
  - 9: `0x00604983`, still the free `__stdcall Rva00604983Get`.
  - 10: `M948`.
  - 11: `0x00604A1E` (createDirectory).
  - 12: `rva006049D8`.
  - 15: wide `getFileListInDirectory`.

## Done

`0x00604A1E` was split out of `VslotSmallBodiesT.cpp` into this approved
TU (`tu_skeleton.py --split`). It is still spelled
`Rva00604A1E::rva00604A1E`.

## What blocks the retirement

1. **The ctor's identity.** `??0Rva00604A5F@@QAE@XZ` must become
   `Win32LocalFileSystem`'s ctor before `rename.py function --to-class` can
   move slots: the class has no ctor or dtor row that installs the table.
   Neither respell route admits it:
   - `--identity` (code identity) needs a wrong binding beforehand, and
     this 9-byte store has no calls.
   - `--basis retail` needs a reviewed `tools/retail_identity.py` family
     (tooling seat, `Verifier-Change`).
2. **The deleting dtors.** `0x00604A42` (`??_GRva00604A42`,
   `InlineDtorDeletingDtors1.cpp`) and `0x00604A6F` (`??_GRva00604A68`,
   `VslotSmallBodiesAR.cpp`) refuse `--split` ("no definition spells its
   name"). They can move with `tu_skeleton.py --emit-move` once this TU's
   classes emit them byte-exact.
3. **The dtor at `0x00604A68`.** It is rowed as
   `?apply@Rva000604A68DwordImmSetter@@QAEXXZ` in
   `Disp0DwordImmSettersAddr.cpp`. `--split` refuses it on the link guard:
   "moved selected COMDAT lacks matching private/weak-free context".
4. **Slot 9.** It must become a thiscall member. The base declares `int
   Virt24`, but the body returns bool.
5. **Slots 1, 13, 14.** They need empty virtuals that fold to `0x000B3FD0`
   (`fold-proof=`).

Order after a retail-identity family lands:

1. Respell the ctor, dtor and both `??_G` rows to `Win32LocalFileSystem` /
   `LocalFileSystem`.
2. Emit-move the `??_G` rows.
3. Run `--to-class` with `--also` for the placeholder slots.
4. Rename the data ledger's table names at `0x0087A974` and `0x0087A9A8`.
