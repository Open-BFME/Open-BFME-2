# LINK-101: W3DVideoBuffer and VideoBuffer vtable slot maps (2026-11-03, seat claudeb2, base fbdb82140a)

Target facts (retail image, read with eh_verify.Image; owners from reverse/functions.csv at this base):

W3DVideoBuffer vftable 0x007C64D8 is 13 slots (52 B, data_ledger names it both
`??_7BfmeOwnerCC@@6B@` and `??_7W3DVideoBuffer@@6B@`). Only the constructor
(store at 0x000726E2) and the destructor 0x0007280A (store at 0x0007281D)
reference it; 0x007C650C right after it is RefCountClass's table (12 code refs).

| slot | body | current row (source) |
|---|---|---|
| 0 | 0x00072723 | ?bfmeSwapBits@Gen_0073A2E0@@QAEXXZ (Common/Bfme5FiftySeven.cpp) |
| 1 | 0x00072866 | ??_GBfmeOwnerCC@@UAEPAXI@Z (Common/BfmeOwnerCC.cpp; dtor 0x0007280A there too) |
| 2 | 0x00072760 | ?allocate@W3DVideoBuffer@@UAE_NII_N@Z (W3DVideoBufferAllocate.cpp) |
| 3 | 0x00072583 | ?rva00072583@W3DVideoBuffer@@QAEXXZ (W3DVideoBufferCtorBfme.cpp) |
| 4 | 0x00072559 | ?rva00072559@Rva00072559@@QAEXXZ (Common/VslotSmallBodiesB.cpp, mixed file) |
| 5 | 0x000723FB | ?Rva000723FB@W3DVideoBuffer@@UAEXXZ (W3DVideoBufferCtorBfme.cpp) |
| 6 | 0x00072566 | ?rva00072566@Rva00072566@@UAE_NXZ (Common/Rva000724C7Check.cpp) |
| 7 | 0x00072756 | ?get@Rva00072756MaskedChaseField@@QBEHXZ (Common/Disp8MaskedChaseDwordGetters.cpp) |
| 8 | 0x0047A699 | ?IsCRC@Xfer@@UBE_NXZ (ICF fold; System/Xfer.cpp) |
| 9 | 0x00072740 | ?rva00072740@Rva00072740@@QAEPAHXZ (W3DVideoBuffer.cpp) |
| 10 | 0x0007274B | ?rva0007274B@Rva00072740@@QAEPAHXZ (W3DVideoBuffer.cpp) |
| 11 | 0x00072472 | ?Rva00072472@W3DVideoBuffer@@UAEXXZ (W3DVideoBufferCtorBfme.cpp) |
| 12 | 0x00072480 | ?Rva00072480@W3DVideoBuffer@@UAEXXZ (W3DVideoBufferRva00072480.cpp) |

VideoBuffer base vftable 0x007C64B0 (stored by the dtor at 0x00072858) is 10
slots: slot 0 `__purecall`, slot 1 the scalar deleting dtor 0x000723C7
(`??_GRva000723C7@@UAEPAXI@Z`, Common/InlineDtorDeletingDtorsC01.cpp), slots
2..9 `__purecall`. So BFME's VideoBuffer has a pure virtual ahead of the
destructor and ten virtuals in all (Zero Hour's has six, destructor first);
W3DVideoBuffer overrides all ten and adds slots 10..12.

Structural inference (not a donor fact): every slot already has an exact row,
so no body is missing; what is missing is one class. W3DVideoBufferCtorBfme.cpp's
eight-virtual view emits a vtable naming the Zero Hour ~W3DVideoBuffer,
two-argument allocate, free, lock, unlock and valid, which only the unrowed
Zero Hour bodies in W3DVideoBuffer.cpp define; those in turn need the Zero
Hour TextureClass/SurfaceClass/VideoBuffer(Type) names the real link reports
missing.

`tu_skeleton.py --merge W3DVideoBuffer.cpp --dry-run` at this base (27 approved
rows): no donor merges. Four lose rows under the carried flag override
(Rva00739C70Cleanup_1..., W3DVideoBufferAllocate, W3DVideoBufferCtorBfme,
W3DVideoStateAllocate), six have no baseline match, two lose census linking to
the seed's Zero Hour unresolved names, and VslotSmallBodiesB.cpp is mixed (14
rows). All twelve donors are census-linked.

## Fold attempt (same session)

`rename.py class --fold BfmeOwnerCC --into W3DVideoBuffer --dry-run` refuses:
"Code/GameEngine/Source/Common/BfmeOwnerCC.cpp would declare class
W3DVideoBuffer twice". That unit's W3DVideoBuffer view is one method,
`rva00072583()`, which the destructor 0x0007280A calls (retail call target
0x00072583). Before the fold the destructor's class must differ from the
callee's, so the unit cannot be reconciled first; the fold needs to merge a
member-only NEW view into OLD's class body or take `--prepared` sources like
`function --to-class`. Recorded as a false reject in reverse/re_attempts.log.
Slot moves with `function --to-class` (slots 0, 4, 6, 7, 9, 10) do not depend
on the fold but need W3DVideoBufferCtorBfme.cpp's view rewritten to the
13-slot order in the same batch, and slot 1 stays unresolved until the fold.
