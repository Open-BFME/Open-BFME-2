# Thing canonical-header adoption (2026-11-01)

Ten private Thing views adopt the existing registered header. Five additional
queued units already using that header pass owning acceptance. Only accept
retires the fifteen queue rows (248 -> 233 at this base).

New adoptions:

- `Code/GameEngine/Source/Common/ClearanceTestingSlowDeathBehavior.cpp`
- `Code/GameEngine/Source/Common/System/Radar.cpp`
- `Code/GameEngine/Source/Common/TailJumpWrappers5B.cpp`
- `Code/GameEngine/Source/Common/Thing/UpgradeMuxData_getUpgradeActivationMasks.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Behavior/AimWeaponBehavior.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainUpdatePosition.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Contain/HordeGarrisonContain.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Contain/OpenContain_monitorConditionChanges.cpp`
- `Code/GameEngine/Source/GameLogic/Object/ObjectRva00291A8C_Rva00291A8C.cpp`
- `Code/GameEngine/Source/GameLogic/Object/ObjectScriptStatus.cpp`

Already using the header; existing queue entries accepted:

- `Code/GameEngine/Source/GameClient/Drawable.cpp`
- `Code/GameEngine/Source/GameLogic/AI/AIGroup.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Die/KeepObjectDie.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Update/AttributeModifierPoolUpdate.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DTankDraw.cpp`

The normal run tested 218 private-view units, all of which passed their
pre-edit frozen-file checks. Eleven byte-pass candidates produced ten applied
edits and one held skip (DOTManager). Immediately after run --apply, the
entire header_queue.tsv was restored from HEAD before owning acceptance.

The initial local index (2026-10-31 11:57 at 5d4d38bfe1) refused three
byte-exact candidates: ClearanceTestingSlowDeathBehavior, Radar and
HordeGarrisonContain. They were restored, retaining their queue rows. After
the supported --fetch-index loaded census 2026-10-31 21:33 at 5d5cf41adf,
all three originals linked. A claimed targeted adoption retry then passed
all three byte gates and owning acceptance. No candidate remains reverted.
The seven initial accepted units also preserve their linked counts against
the new index; all ten new adopters LINK in that scoped preview.

ObjectRva00291A8C_Rva00291A8C and ObjectScriptStatus also standardize their
existing BitFlags template parameter from int to unsigned int, matching the
real header. Control builds show identical sorted COMDAT name/digest/size
tuples, external names/values/definition status and weak aliases before and
after this parameter correction. No member body or storage change occurs.

Final ./build.sh over all ten adopted paths passes 175/175 code rows, two
data rows, nine string references, 44 floating-point references and one named
import. Sixteen renumbered funclets are verified through parent EH data. All
post-edit frozen-file checks pass. The same ten paths pass all 175 rows with
the proposed Thing query declarations temporarily present; that header trial
is restored and the actual committed header is rebuilt again.

The broader query-header trial ran thirteen sequential builds, each at most
40 paths, over the then-current 496 conservative dependents. Nine batches
passed and four reported BitFlags declaration failures. Two of those sources
are the corrected new adopters above, which now pass the query-header trial.
The remaining six are held by hdr-player-2 or qc-11: PlayerTeamCommands, the
three BezierProjectileBehavior units, ElvenWoodSpecialPower and
CivilianSpawnUpdate. StealthUpdate is separately held by class:Player and
still needs its non-template declaration replaced with Common/BitFlags.h.
Thing storage, vtable and header declarations remain unchanged in this stack.

The separate query extension and storage evidence are recorded in
thing-canonical-header-prerequisites-20261101.md. No new pin, hatch, compiler
flag, source path or function-ledger change is made by this adoption batch.
TransitionDamageFX and GameLogic already use the header but remain queued:
their ordinary previews retain existing duplicate-provider losses.

These are per-unit byte gates and published-index link guards, not a new
census measurement, full affected-consumer proof or runtime smoke result. The
lead publication audit and the scheduled census retain the broader provider
selection checks.
