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
