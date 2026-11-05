# ObjectCreationList.cpp merge: AttackNuggetCtor donor trial (2026-11-05, claude2)

Target facts:
- `??0AttackNugget` 0x001F05C1 stores 0.0f at +0x38, 1 at +0x3C and clears +0x40.
- Canonical `Code/GameEngine/Include/GameClient/RadiusDecalTemplate.h` documents sizeof(RadiusDecalTemplate) = 0x34
  (ctor 0x00330E5D, W3DTornadoDrawModuleData ctor 0x000D16B4).

Completed: AttackNuggetCtor.cpp now uses the seed's member names
(m_deliveryDecalTemplate, m_deliveryDecalRadius, m_numberOfShots, m_weaponSlot), commit 219cc679db;
build.sh 3/3, link_check LINKS 79 -> 79. The earlier C2065 (m_float38/m_int3C) reject is gone.

Trial: seed + AttackNuggetCtor only (tu_skeleton.merge restricted to the two files, claim off).
The donor composes and compiles; the byte check misses `??0AttackNugget`, then `$L339`
("scoped funclet lacks an exact same-source parent EH location") follows from the miss.

Probe diff of the composed text, 0x001F05C1:

    ours ... 0f 57 c0 83 66 28 00 8b 4d f4 f3 0f 11 46 20 c7 46 24 01 00 00 00 ...
    tgt  ... 0f 57 c0 83 66 40 00 8b 4d f4 f3 0f 11 46 38 c7 46 3c 01 00 00 00 ...

The only difference is the member offsets: the seed gets RadiusDecalTemplate from the Zero Hour
`GameClient/RadiusDecal.h` (via `GameLogic/Module/RadiusDecalUpdate.h`), which is 0x1C bytes;
BFME 2's is 0x34. The out-of-line `~ObjectCreationNugget()` shim change was tried and does not
affect the result (reverted).

Next step: give the seed BFME 2's RadiusDecalTemplate (the canonical header, or a seed-only
shim that shadows the ZH RadiusDecal.h while keeping RadiusDecal for the seed's other users);
the seed must stay 58/58. Then retry the AttackNuggetCtor donor. Do not pad AttackNugget instead.
Inferences: the 0x18-byte shift equals 0x34 - 0x1C exactly; no other member differs.
