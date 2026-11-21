# 0x007CF9E0 family: BfmeShadowBufferOwnerBase slots 1-2 (handoff, 2026-11-21)

Target facts (retail tables):

| table | our class | slot 0 | slot 1 | slot 2 |
|---|---|---|---|---|
| 0x7CEFA0 | BfmeShadowBufferOwnerBase / Rva007B12F0Base / Rva007B1380 | 0xEFAD2 ??_G | 0xB3FD0 empty | __purecall |
| 0x7CF9E0 | Rva007AFF00Owner | 0x10BA45 ??_G | 0xB3FD0 | 0x109DA6 |
| 0x7CF9F4 | Rva001095B2 | 0x10B9C9 ??_G | 0xB3FD0 | 0x10BB04 |
| 0x7CFA00 | Rva00109610 | 0x10BA83 ??_G | 0xB3FD0 | 0x109643 |
| 0x7CF964 | W3DVolumetricShadowV2 | 0x107D6E ??_G | 0xB3FD0 | 0x1074C8 |
| 0x7CEFC8 | W3DVolumetricShadow | 0xF2B81 ??_G | 0xF42F7 | 0xF168B (+slot 3 0xF1B73) |

Slot-2 bodies: 0x109DA6 = `push ecx; mov ecx,[0xDEC2D8]; call 0x5091A8; ret`;
0x10BB04 same shape calling 0x50B9E5; 0x109643 = `jmp 0x508951`. All are rowed
opaquely (`?rva00109DA6@Rva00109DA6Host@@QAEXXZ`, `?rva0010BB04@Rva0010BB04Host@@QAEXXZ`
in VslotMiscForwarders.cpp; `?rva00109643@Rva00109643@@QAEXXZ` in VslotSmallBodiesAJ.cpp).
tu_map: 0x10BB04 and 0x109643 approved for W3DProjectedShadow.cpp; 0x109DA6 only proposed
(BfmeSub928F.cpp).

Inference: `BfmeShadowPrefix.h` models only slot 0. Adding `virtual void slot1() {}`
(ICF alias at 0xB3FD0) and a pure slot 2 would fix the shared base and lets every derived
table above override slot 2.

Blockers:
- `rename.py function --to-class Rva00109610` refuses: the class has no canonical header in
  reverse/canonical_classes.csv; slot-2 names are voted on registered classes. Same for
  Rva007AFF00Owner / Rva001095B2. Registering them is header-lane work (W3DProjectedShadow.cpp
  declares Rva000F0F2B and Rva007B1380 with bases differing from W3DVolumetricShadowCtor.cpp
  and Rva007B1380Ctor.cpp).
- Donor ZH `Shadow` has release() at slot 0 and no dtor; no evidence-backed slot names.
Next: register the shadow-owner family in one header (BfmeShadowPrefix.h), then rename
the slot-2 bodies with --to-class and add the base slots in one change.
