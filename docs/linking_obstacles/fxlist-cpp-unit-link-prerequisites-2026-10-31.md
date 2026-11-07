### FXList.cpp unit-link prerequisites (2026-10-31)

FXList.cpp (7 matched rows, 620B own bytes) does not link. Three prerequisites:
1. Two unresolved callees are retail overloads with no provider: 
   `?createParticleSystem@ParticleSystemManager@@QAEPAVParticleSystem@@PBVParticleSystemTemplate@@_N@Z`
   (pointer-return; the rowed 0x001F5A6A is the `BfmeParticleSystemHandle`-by-value overload) and
   `?getLayerForDestination@TerrainLogic@@QAE?AW4PathfindLayerEnum@@PBUCoord3D@@@Z`
   (coord-only; the rowed 0x002802FE is the `(Object*, const Coord3D*)` overload — the ZH header spells coord-only, the BFME2 rowed body takes the extra `Object*`).
   The matched 371B `doFXObj@ParticleSystemFXNugget` row calls both spellings, so the overloads are real retail symbols awaiting recovery.
2. The losing COMDATs `??0?$list@PAVFXNugget@@...` (copy ctor) and `??1?$_List_base@PAVFXNugget@@...` (dtor) are unrowed in every unit; the natural retail owner is FXList.cpp itself once its inline shape matches. Declaration-only suppression (the vector operator[] pattern) would only flip which unrowed copy wins.
3. `??_7ParticleSystemFXNugget@@6B@` differs from the first link-order copy.
Recorded `blocked` in reverse/re_attempts.log.

Update (2026-11-07, crash-triage seat2, P16): the ParticleSystemFXNugget COMDAT winner, and the lasting fix.
- Boot crash P16 (master receipts since 94595b3044, e.g. 2026-11-07T152032Z-boot_smoke-b58b3611388c on 420c2e6572):
  FXList.cpp's Zero Hour ParticleSystemFXNugget view emits an inline constructor and parse (MEMORY_POOL_GLUE pool lookup,
  new(0x50), initFromINI) under the same names as the rowed retail copies, ??0ParticleSystemFXNugget@@QAE@XZ (0x001E0AEF,
  ParticleSystemFXNuggetCtor.cpp) and ?parse@ParticleSystemFXNugget@@SAXPAVINI@@PAX1PBX@Z (0x001E264F,
  FXListNuggetParse.cpp). FXList.obj comes first, so the image runs Zero Hour's parse, whose pool glue reads a
  TheMemoryPoolFactory nothing writes. The unreferenced BfmeReferenceFXListFieldParse table keeps those inlines alive so the
  unit still emits the rowed inline doFXObj (0x001E24DC); its comment expects /OPT:REF to drop them, but COMDAT selection
  happens first.
- Tried (branch swarm/triage/p16-fxlist-nugget-comdats, 7f9494080d): declare the view's ctor and parse only and keep doFXObj
  through an anchor. Receipt 2026-11-07T155125Z-boot_smoke-512b0a77b4be gets past P16, but review refused the anchor
  (absent-from-retail is only for dead-stripped retail code). Moving doFXObj to ParticleSystemFXNuggetCtor.cpp breaks the TU
  map: tu_map approves FXList.cpp for doFXObj, the ctor 0x001E0AEF (and its funclets 0x00769C4F..0x00769C8F) and parse
  0x001E264F, so retail built ctor, parse, vtable and doFXObj in FXList.cpp.
- Interim retail-body copy (FXList.cpp emits byte-identical copies of the rowed ctor and parse): not reachable as the unit
  stands. FXList.cpp compiles through PreRTS.h against 84 Zero Hour headers; its Common/INI.h is Zero Hour's, whose
  MultiIniFieldParse has an inline loop ctor (retail parse calls the out-of-line 0x0042BAA0), and its
  GameClientRandomVariable is Zero Hour's (the retail ctor inlines the canonical setRange). header_adopt_lane adopt finds no
  private view to replace for INI, MultiIniFieldParse or GameClientRandomVariable in this unit.
Remaining / next check (lasting fix, consolidation lane): merge the ParticleSystemFXNugget rows (ctor 0x001E0AEF and its
funclets, parse 0x001E264F, with doFXObj already here) into FXList.cpp with tools/tu_skeleton.py once
`--merge Code/GameEngine/Source/GameClient/FXList.cpp --dry-run` stops reporting "TU path holds rows of another TU (split
it first)" and the Rva001DFEAABase and FXListStore header adoptions it asks for are done; the merged unit then constructs the
real class in parse, emits retail's vtable and doFXObj, and drops the Zero Hour view. Until then master keeps crashing at P16;
re_attempts.log 0x001E24DC records both refused routes.
