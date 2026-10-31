# Thing canonical-header prerequisites (2026-11-01)

Seat: `halilkkaya-codex`. No master push from this seat.

The initial full gate passed all 99,255 function rows. Current canonical
Thing storage remains 0x60 bytes and its eight-slot retail vftable remains
unchanged. The majority contract still contradicts that retail evidence; no
contract or storage expansion is made.

The attempted header extension declares the existing matched queries:

```cpp
template <unsigned int NUM_BITS> class BitFlags;
bool isAnyKindOf(const BitFlags<69> &mask) const; // 0x0030ADC7, 21 bytes
bool isKindOfMulti(const BitFlags<116> &mustBeSet,
                  const BitFlags<116> &mustBeClear) const; // 0x0030AD7D, 14 bytes
```

The header trial was restored. Its first 40-path dependent build failed
C3855 in ActionManagerSpecialPowerChecks and PlayerTeamCommands: their private
BitFlags declarations use signed int template parameters, whereas the real
Zero Hour BitFlags header uses size_t (unsigned int on this target). The
conservative header graph reaches 489 sources; current compile receipts
identify 167 actual includes, plus the two receipts removed by failed builds.

Eighteen unheld actual dependents now use unsigned int for the existing
BitFlags template parameter. Their storage, member bodies and template argument
values are unchanged. ./build.sh verifies 746/746 code rows and 10 data rows;
all frozen-file checks pass. A control rebuilt the original HEAD sources,
then restored and rebuilt the edits. For every unit, the before/after facts
below are identical: sorted COMDAT name/digest/size tuples (the digest covers
bytes and relocation destinations), external names/values/definition status
and weak aliases. SHA-256 hashes are of the sorted-key JSON facts.

| Source | Before = after SHA-256 |
| --- | --- |
| `Code/GameEngine/Source/Common/RTS/ActionManagerSpecialPowerChecks.cpp` | `69ecae564467ccdae3472f7348523c819cb505312000d2991446fcfbeb25ec8f` |
| `Code/GameEngine/Source/GameClient/Drawable.cpp` | `0c57c76027a5691882a8701506b8f8a1d8c8550ecf2af06abc3d41cd939e64b8` |
| `Code/GameEngine/Source/GameClient/DrawableXfer.cpp` | `4f3177a5d983f304d2754ac9dd1119766ef1174f2d812cdfd3e84c27ae6393b0` |
| `Code/GameEngine/Source/GameLogic/AI/AIGroup.cpp` | `46d94cff4d74a3da14149c5ae69545aa012dadfd4772776748abc31793ccf290` |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/GateOpenAndCloseBehavior.cpp` | `a45c0419e2f31dd2751a64e10388c644afe0120c3aeaa8172286bf92b0013095` |
| `Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain.cpp` | `4a66fc67b5487e290041443813b99eb9343d497573b1f76f45c6b954542d74c5` |
| `Code/GameEngine/Source/GameLogic/Object/Contain/OpenContainDtorRva00464692.cpp` | `93198995d8e89c8a674fbe4b02771f84dafd2d69cf7f9f84218f7245f61fb31b` |
| `Code/GameEngine/Source/GameLogic/Object/Contain/OpenContainXfer.cpp` | `7f945553f90c0278ad7bf66c84b44a2d70a4657c36dfa0d9ffac186998154c92` |
| `Code/GameEngine/Source/GameLogic/Object/Die/CreateCrateDieTestKillerType.cpp` | `baca4113a01735aecada5c4b91186e857e6ade033e5654fbd14ddbf24f3433f9` |
| `Code/GameEngine/Source/GameLogic/Object/ObjectConstructor.cpp` | `115acddef8d70449568583243df674bf61c0888208698e9058f75b6d044b78bf` |
| `Code/GameEngine/Source/GameLogic/Object/ObjectRva00291A8C.cpp` | `e63ff3375f2a686c4f0817ea868e6a2a4c9bc3a7d4840abbe82eaafb535d7b57` |
| `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdDoLocomotor.cpp` | `0ff0c2f5fedde596363e9c750de39e2d7aebde660966503ca684664aa98c893a` |
| `Code/GameEngine/Source/GameLogic/Object/Update/BannerCarrierUpdate.cpp` | `cae5e9ff53c5f14dca6a049a6b6d1085a520ae5707fb7aaa2babd574b07fa8c1` |
| `Code/GameEngine/Source/GameLogic/Object/Update/ProductionUpdateQueue.cpp` | `e6755fb86f2df9cfcac68f5139f703b7dfd6f474433e674ccf2aac03ae299843` |
| `Code/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdateRun.cpp` | `51e87369a4e07d016083c2006ecd6d1a03a70ff14b20263be3902a0172a44ca8` |
| `Code/GameEngine/Source/GameLogic/Object/Update/TeleportToCasterSpecialPower.cpp` | `904cfac2ac4129ae634b9c49bd7275b4a34d467c289641accc93983f8d21888d` |
| `Code/GameEngine/Source/GameLogic/System/GameLogic.cpp` | `5589a9811217d1836466540b84dc13f8a6da7f9d414dfe9ba091daee9aa24e42` |
| `Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DProjectedShadowDecalHelpers.cpp` | `406c5c51cd58755d2fb230305801a04454bbbb28966f5de6a2eb4e7b5252876a` |


The local published index is census 2026-10-31 11:57 at 5d4d38bfe1. Its
ordinary preview links 16/18 edited units. GateOpenAndCloseBehavior and
GameLogic report duplicate providers on both the original and changed sources;
the control reproduces exactly the same duplicate names. These are existing
selection obstacles, not losses introduced by parameter signedness. No census
gain or complete consumer-loss clearance is claimed.

The intended query declarations still require the following held sources to
standardize their existing BitFlags template parameters:

- PlayerTeamCommands.cpp: class:Player, hdr-player-2.
- BezierProjectileBehavior.cpp, BezierProjectileBehaviorCtor.cpp and
  BezierProjectileBehaviorDtor.cpp: qc-11 file claims.
- ElvenWoodSpecialPower.cpp: hdr-player-2 file footprint.
- CivilianSpawnUpdate.cpp: qc-11 file claim.

StealthUpdate.cpp is also covered by hdr-player-2 class:Player and was left
untouched; its non-template class BitFlags declaration still needs the real
Common/BitFlags.h include. MobMemberSlavedUpdate.cpp has that include now and
passes its row; the unchanged StealthUpdate pair passes 3/3 rows.

Do not add Object-only fields or explicit raw vtable fields to Thing to clear
field-rename refusals. The retail constructor and registered header give the
base boundary; derived fields at +0x74, +0x84, +0x94, +0x258 and beyond need
their real owner/view reconciled. Matrix and position subfield representations
also need source reconciliation, not an increased Thing extent.

After the claims are available, finish those prerequisites, apply the two
query declarations, rebuild every Thing dependent in batches <=40 paths, then
run the owning adoption lane. Restore header_queue.tsv after run --apply and
retire only through accept; revert every source without an owning link verdict.
