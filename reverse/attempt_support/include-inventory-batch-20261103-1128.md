# 18 BFME2 include-inventory repairs

Base `af2bef90c6786c7cd2deffa60594a0bcdda519ae`. Each source independently removes only its redundant whole-checkout
`/I.` search root and anchors existing includes relative to the source. The
before/after compiler dependency sets resolve to the same physical paths and
hashes, normalizing Windows case and relative path aliases. No source body,
optimization or ABI switch, shared header, native name, pin, alias, ledger,
hatch or baseline changes. Every source has its own before-object, native
normal/frozen gate, external code/relocation comparison, named static comparison,
and complete non-debug-section comparison including data, EH and linker directives.

Preserved: 40 existing native function/EH rows, 3351 ledger-extent bytes,
117 retained external code instances and 1 named TU-local code
instances. No native coverage, runtime improvement or linked-byte gain is claimed.

- [Repair include inventory in Rva0036CA3BGoalValidation](b2-01-include-inventory-20261103-1128.md): 5 rows, 5 external code instances.
- [Repair include inventory in Rva003BD01FSetter](b2-02-include-inventory-20261103-1128.md): 1 rows, 1 external code instances.
- [Repair include inventory in ScriptPositionRecord](b2-03-include-inventory-20261103-1128.md): 1 rows, 1 external code instances.
- [Repair include inventory in ScriptGlueRva003BECCD](b2-04-include-inventory-20261103-1128.md): 1 rows, 3 external code instances.
- [Repair include inventory in ScriptActions_doNamedEnableCameraFading](b2-05-include-inventory-20261103-1128.md): 1 rows, 2 external code instances.
- [Repair include inventory in Rva0043979DUpdate](b2-06-include-inventory-20261103-1128.md): 1 rows, 3 external code instances.
- [Repair include inventory in AIUpdateInterfaceRva0026C0D6](b2-07-include-inventory-20261103-1128.md): 1 rows, 2 external code instances.
- [Repair include inventory in MathCoord2DClosestPoint](b2-08-include-inventory-20261103-1128.md): 1 rows, 5 external code instances.
- [Repair include inventory in strsafe](b2-09-include-inventory-20261103-1128.md): 12 rows, 13 external code instances.
- [Repair include inventory in AICombineStateInternalUpdate](b2-10-include-inventory-20261103-1128.md): 1 rows, 4 external code instances.
- [Repair include inventory in ScoreKeeperUnhookAll](b2-11-include-inventory-20261103-1128.md): 3 rows, 27 external code instances.
- [Repair include inventory in MovieBlockingPlayback](b2-12-include-inventory-20261103-1128.md): 1 rows, 3 external code instances.
- [Repair include inventory in ScriptGlueRva003BD270](b2-13-include-inventory-20261103-1128.md): 2 rows, 2 external code instances.
- [Repair include inventory in ScriptActions_rva003BFFEC](b2-14-include-inventory-20261103-1128.md): 1 rows, 3 external code instances.
- [Repair include inventory in ObjectPlanarBorderVector](b2-15-include-inventory-20261103-1128.md): 2 rows, 6 external code instances.
- [Repair include inventory in ScriptGlueRva003C35AA](b2-16-include-inventory-20261103-1128.md): 2 rows, 4 external code instances.
- [Repair include inventory in SquadFromContainedMembers](b2-17-include-inventory-20261103-1128.md): 3 rows, 28 external code instances.
- [Repair include inventory in PlayerProductionCostChange](b2-18-include-inventory-20261103-1128.md): 1 rows, 5 external code instances.

## Selection and scope

The native link pickers were reviewed before choosing this bounded compiler-input
maintenance batch. Repeated unchanged failed body trials are not work credit.

BFME2's native picker serves AutoPickUpUpdate, already covered by the shared
obstacle register's repair history. Its current preview cannot prove selection:
67 units changed since the index hold no ledger row now, so their old definitions
cannot be retracted by this preview. The native fetch retains the same Nov2
08:35 index at 984a4cdc4d. No old repair is repeated or credited, and no fresh
census, full link or runtime pass is claimed. Strict preparation/new-variant
checks for the explicit changed sources are separate from global link closure.

Bounded dated preview (UNKNOWN/INCONCLUSIVE stays unverified):

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/Rva0036CA3BGoalValidation.cpp: LINKS  LINKED 271 -> 271 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 271)
Code/GameEngine/Source/GameLogic/ScriptEngine/Rva003BD01FSetter.cpp: LINKS  LINKED 19 -> 19 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 19)
Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptPositionRecord.cpp: LINKS  LINKED 0 -> 0 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 0)
Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptGlueRva003BECCD.cpp: LINKS  LINKED 51 -> 51 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 51)
Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doNamedEnableCameraFading.cpp: LINKS  LINKED 55 -> 55 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 55)
Code/GameEngine/Source/GameLogic/Object/Update/Rva0043979DUpdate.cpp: LINKS  LINKED 190 -> 190 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 190)
Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfaceRva0026C0D6.cpp: LINKS  LINKED 122 -> 122 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 122)
Code/Libraries/Source/Math/MathCoord2DClosestPoint.cpp: LINKS  LINKED 256 -> 256 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 256)
Code/Libraries/Source/DirectX/strsafe.cpp: LINKS  LINKED 604 -> 604 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 604)
Code/GameEngine/Source/GameLogic/AI/AICombineStateInternalUpdate.cpp: LINKS  LINKED 232 -> 232 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 232)
Code/GameEngine/Source/Common/RTS/ScoreKeeperUnhookAll.cpp: LINKS  LINKED 98 -> 98 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 98)
  diagnostic  ?deallocate@?$_STLP_alloc_proxy@PAIIV?$allocator@I@_STL@@@_STL@@QAEXPAII@Z  (relocations differ from the majority copy, bytes equal; unreferenced, not a blocker)
Code/GameEngine/Source/GameClient/MovieBlockingPlayback.cpp: LINKS  LINKED 525 -> 525 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 525)
Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptGlueRva003BD270.cpp: LINKS  LINKED 69 -> 69 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 69)
Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_rva003BFFEC.cpp: LINKS  LINKED 96 -> 96 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 96)
Code/GameEngine/Source/GameLogic/Object/ObjectPlanarBorderVector.cpp: LINKS  LINKED 249 -> 249 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 249)
Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptGlueRva003C35AA.cpp: LINKS  LINKED 94 -> 94 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 94)
Code/GameEngine/Source/GameLogic/AI/SquadFromContainedMembers.cpp: LINKS  LINKED 162 -> 162 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 162)
Code/GameEngine/Source/Common/RTS/PlayerProductionCostChange.cpp: LINKS  LINKED 192 -> 192 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 192)
link_check: 18 of 18 link cleanly; LINKED 3,285 -> 3,285 bytes (8.6s)
```

## Execution and proof limits

The repositories use independent claims, source trees, ledgers and object caches,
so native work ran concurrently between projects. Within each repository, edits,
native cache writes, log writes and commits were sequential. BUILD_POOL=14 each,
up to28 build workers on28 logical CPUs. No local model was required. No measured
serial/parallel speedup is claimed. The diagnostic first pass corrected its own
cross-project command assumption and Windows path-alias comparison; project
gates were never weakened and original sources were restored before the corrected run.

This batch repairs compiler include inventories. It does not establish RAM/leak,
crash, FPS or multicore improvements. Full engine linking/gameplay remain unproven.

Outgoing audit before this documentation-only amendment, exit 2:

```text
link batch audit: INCONCLUSIVE baseline: index at 984a4cdc4d, outgoing base af2bef90c6786c7cd2deffa60594a0bcdda519ae; findings below are provisional since-index changes
link batch audit: INCONCLUSIVE: affected consumer lacks current receipt: Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp
```
