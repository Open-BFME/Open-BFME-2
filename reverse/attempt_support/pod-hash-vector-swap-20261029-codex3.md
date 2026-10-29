# Opaque hash vector emission repair, 2026-10-29

Base: `ac17ccda470cd2d463a66be605f5481491912f81`.
Source: `Code/Libraries/Source/WWVegas/WWLib/stlport_pod_hash_bodies.cpp`.
Claims: `0x00055612` and the source file, owner `yasinschroeder-codex3`.
Compiler flags and STLport 4.5.3 reference are unchanged.

The default link picker served the eight-row, 391-authored-byte unit.
LINK-103 already documented the failed generic-swap trial; this pass tests
the existing stateless allocator-proxy swap specialization in Armor.cpp.
The proxy's allocator has no state, so swapping its stored pointer preserves
the vector operation without copying the whole proxy. This is a structural
compiler-context repair, not evidence for any placeholder's native type.

Retained change: reveal the header's vector/base count constructors,
allocator allocation and vector swap; define the same pointer-only proxy
swap as Armor.cpp instead of revealing generic proxy swap. No pin, alias,
row, header, compiler flag or debt register is changed.

## Verification

- `./build.sh` verifies all eight source rows before and after the edit.
  Frozen-file checks pass before and after; EH verification has no applicable
  rows; shadow data check has zero findings.
- `link_check.py --prepare-current` verifies the edited source and writes
  its strict reusable receipt.
- Against index `85f6b7f40c` (2026-10-29 15:08), own ordinary preview moves
  from L3/S3 to L2/S2. The Pod72 resize copy changes from 211 bytes, wrong
  digest `e8c7c924f4ef`, to the retail 184-byte digest `ae54ad19b774` at
  the existing 0x0053F1EC fold. This does not add a row or fold pin.
- The generic proxy copy constructor that broke the prior trial is not
  newly emitted. The string-hash consumer still preview-links (188 bytes).
- Comparing old/new object facts finds 18 changed COMDAT names, no strong
  definition change, no new undefined name, and removal of the external
  vector count-constructor and swap references. Some newly emitted helper
  copies remain wrong or unknown; the comparison below checks selection
  rather than assuming those copies are safe.
- Build the 44-source cohort below: all 1,176 rows pass, as do 10 data rows,
  369 funclet pins, seven constructor folds, 301 nonempty/35 empty string
  references, 137 floating literals and 152 import references.
- Overlay those 44 objects on the downloaded index with
  `link_batch_audit.overlay`; compare `link_check.check_object` results for
  each source using the original target object and then the edited object,
  keeping the other 43 objects identical. Compare unresolved, duplicate,
  COMDAT, selected-copy and address findings. Results: 41 clean units both
  before and after, no regressions, and only the target's blocker set changes
  (Pod72 resize removed). This includes the earlier regressing string-hash
  consumer. The other 43 objects lack strict census receipts despite passing
  ordinary build checks: this is an ordinary preview, not census closure.

## Remaining prerequisites

The Pod44 placement-copy name targets 0x0041072F, a 45-byte nontrivial
AsciiString-keyed pair construction, whereas this source emits a 32-byte
trivial integer-keyed copy. The integer-table resize targets the 199-byte
AsciiString-keyed grower at 0x00212858. Neither can be fixed by further
visibility changes or by assigning a second name to the existing owner.
Reconcile the native key/element families with the existing owners first.

`repair_queue.py retire identity` was attempted through the supported path
and refused. In addition to two initially noncurrent providers, it finds the
unchanged hash-set constructor at 0x0005B505 calling the integer-hashtable
constructor pinned at 0x0005A112, with a wrong verdict outside the register.
The changed-name comparison excludes that constructor. Retain all identity
keys; this repair alone cannot retire the source's registered debt.

No census or linked-byte gain is claimed. Confirm provider closure in the
next scheduled census; retain LINK-103 and LINK-002 prerequisites.

## Affected ordinary-preview cohort

Selected from the index's touched-name intersection with the 18 changed
external COMDAT names, plus the edited source:

```text
Code/GameEngine/Source/Common/DamageFX_hashtableResize.cpp
Code/GameEngine/Source/Common/Rva0002C7FD.cpp
Code/GameEngine/Source/Common/Rva000E0322Rva000E0322.cpp
Code/GameEngine/Source/GameClient/FXListMapNodeEmit.cpp
Code/GameEngine/Source/GameClient/FXListStoreParse.cpp
Code/GameEngine/Source/GameClient/GUI/Rva00427157Ctor.cpp
Code/GameEngine/Source/GameClient/GUI/window_video_manager.cpp
Code/GameEngine/Source/GameClient/GameClientDrawableTOC.cpp
Code/GameEngine/Source/GameClient/InGameUISuperweapons.cpp
Code/GameEngine/Source/GameClient/LivingWorld/LivingWorldManagerCreateBeaconObject.cpp
Code/GameEngine/Source/GameClient/MessageStream/SelectionIDMap.cpp
Code/GameEngine/Source/GameClient/MessageStream/SelectionXlatTranslateGameMessage.cpp
Code/GameEngine/Source/GameClient/System/ParticleSys.cpp
Code/GameEngine/Source/GameLogic/AI/MoveToFormationGroupOrder.cpp
Code/GameEngine/Source/GameLogic/AI/MoveToGroupOrder.cpp
Code/GameEngine/Source/GameLogic/AI/MoveToGroupOrderXfer.cpp
Code/GameEngine/Source/GameLogic/Object/Armor.cpp
Code/GameEngine/Source/GameLogic/Object/ArmorStoreParse.cpp
Code/GameEngine/Source/GameLogic/Pathfinder/pathfinder.cpp
Code/GameEngine/Source/GameLogic/SkirmishAI/ArmyDefinitionManager.cpp
Code/GameEngine/Source/GameLogic/System/GameLogicDoXfer.cpp
Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThread.cpp
Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp
Code/Libraries/Source/WWVegas/WWLib/Rva000272A0Cluster.cpp
Code/Libraries/Source/WWVegas/WWLib/Rva00212858Resize.cpp
Code/Libraries/Source/WWVegas/WWLib/Rva00511CB4FillPointers.cpp
Code/Libraries/Source/WWVegas/WWLib/RvaHashIndex00928620.cpp
Code/Libraries/Source/WWVegas/WWLib/RvaHashResize00927DE0.cpp
Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva002A3FAF.cpp
Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva00056BFE.cpp
Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva003609F7.cpp
Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva0060CBAC.cpp
Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva0007E394.cpp
Code/Libraries/Source/WWVegas/WWLib/StlSweepW6Rva006200B0.cpp
Code/Libraries/Source/WWVegas/WWLib/stlport_hash_map_int.cpp
Code/Libraries/Source/WWVegas/WWLib/stlport_hash_map_int_list_pod264.cpp
Code/Libraries/Source/WWVegas/WWLib/stlport_hash_map_int_resize.cpp
Code/Libraries/Source/WWVegas/WWLib/stlport_hash_map_int_vector_sciencetype.cpp
Code/Libraries/Source/WWVegas/WWLib/stlport_hash_map_string_uint_resize.cpp
Code/Libraries/Source/WWVegas/WWLib/stlport_hashtable_asciistring.cpp
Code/Libraries/Source/WWVegas/WWLib/stlport_pod_hash_bodies.cpp
Code/Libraries/Source/WWVegas/WWLib/stlport_vector_voidptr.cpp
Code/Libraries/Source/WWVegas/WWLib/stlport_vector_voidptr_alloc.cpp
Code/Libraries/Source/WWVegas/WWLib/stlport_vector_voidptr_opt.cpp
```
