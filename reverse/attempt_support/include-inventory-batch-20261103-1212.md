# 17 BFME2 include-inventory repairs

Base `4c68335a247a7bb4b0e03ebb87b8bc8378eb0231`. Each source independently removes only its redundant whole-checkout
`/I.` search root and anchors existing includes relative to the source. The
before/after compiler dependency sets resolve to the same physical paths and
hashes, normalizing Windows case and relative path aliases. No source body,
optimization or ABI switch, shared header, native name, pin, alias, ledger,
hatch or baseline changes. Every source has its own before-object, native
normal/frozen gate, external code/relocation comparison, named static comparison,
and complete non-debug-section comparison including data, EH and linker directives.

Preserved: 45 existing native function/EH rows, 5477 ledger-extent bytes,
207 retained external code instances and 9 named TU-local code
instances. No native coverage, runtime improvement or linked-byte gain is claimed.

- [Repair include inventory in Rva003BCADAForward](b2-01-include-inventory-20261103-1212.md): 1 rows, 1 external code instances.
- [Repair include inventory in ScriptGlueRva003BD062](b2-02-include-inventory-20261103-1212.md): 1 rows, 1 external code instances.
- [Repair include inventory in BfmeConv896](b2-03-include-inventory-20261103-1212.md): 1 rows, 2 external code instances.
- [Repair include inventory in GarrisonContainSiblingHelpers](b2-04-include-inventory-20261103-1212.md): 2 rows, 11 external code instances.
- [Repair include inventory in Rva0047D90CRva0047D90C](b2-05-include-inventory-20261103-1212.md): 3 rows, 15 external code instances.
- [Repair include inventory in ScriptEnginePositions](b2-06-include-inventory-20261103-1212.md): 2 rows, 18 external code instances.
- [Repair include inventory in NameKeyGeneratorLifetime](b2-07-include-inventory-20261103-1212.md): 10 rows, 18 external code instances.
- [Repair include inventory in FormationPreviewPoolLookup](b2-08-include-inventory-20261103-1212.md): 4 rows, 40 external code instances.
- [Repair include inventory in dxtracew](b2-09-include-inventory-20261103-1212.md): 1 rows, 9 external code instances.
- [Repair include inventory in dxtracea](b2-10-include-inventory-20261103-1212.md): 1 rows, 7 external code instances.
- [Repair include inventory in PathfinderIsValidHordeMemberRegularMovement](b2-11-include-inventory-20261103-1212.md): 1 rows, 4 external code instances.
- [Repair include inventory in fxpsemittercylindervolumemodule](b2-12-include-inventory-20261103-1212.md): 1 rows, 2 external code instances.
- [Repair include inventory in AIUpdateInterfaceLocomotorDistanceToGoal](b2-13-include-inventory-20261103-1212.md): 1 rows, 8 external code instances.
- [Repair include inventory in AIUpdateInterfaceNotifyPathHasInvalidPortals](b2-14-include-inventory-20261103-1212.md): 5 rows, 36 external code instances.
- [Repair include inventory in AIGateUpdateTrigger](b2-15-include-inventory-20261103-1212.md): 6 rows, 11 external code instances.
- [Repair include inventory in Rva0028E8D4Rva0028E8D4](b2-16-include-inventory-20261103-1212.md): 2 rows, 11 external code instances.
- [Repair include inventory in RousingSpeechUpdateTrigger](b2-17-include-inventory-20261103-1212.md): 3 rows, 13 external code instances.

## Selection and scope

The native link pickers were reviewed before choosing this bounded compiler-input
maintenance batch. Repeated unchanged failed body trials are not work credit.

BFME2's current native picker selected ExperienceLevelSystem consolidation,
forecasting up to14 removable donor files. The supported evidence planner,
merge dry-run and view planner accept zero donors. Existing recorded base,
vptr, node-size, class-key, template and canonical-header prerequisites remain.
The original source/ledger/path/register bytes are preserved. The previous
records were read after this dry-run and should have been consulted first;
this repeated review is not completed work or a new blocker discovery.
Handoff: [experience-level-merge-prerequisites-20261103-1212.md](experience-level-merge-prerequisites-20261103-1212.md). Its
home reservation is released. The17 completed source repairs are separate
from that uncompleted review. No file move or source-count reduction occurred.
The dated index remains a bounded preview, not a fresh global census.

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
Code/GameEngine/Source/GameLogic/ScriptEngine/Rva003BCADAForward.cpp: LINKS  LINKED 14 -> 14 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 14)
Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptGlueRva003BD062.cpp: LINKS  LINKED 102 -> 102 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 102)
Code/GameEngine/Source/Common/BfmeConv896.cpp: LINKS  LINKED 37 -> 37 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 37)
Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainSiblingHelpers.cpp: LINKS  LINKED 144 -> 144 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 144)
Code/GameEngine/Source/Common/Rva0047D90CRva0047D90C.cpp: LINKS  LINKED 252 -> 252 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 252)
Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptEnginePositions.cpp: LINKS  LINKED 130 -> 130 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 130)
Code/GameEngine/Source/Common/NameKeyGeneratorLifetime.cpp: LINKS  LINKED 268 -> 268 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 268)
Code/GameEngine/Source/GameClient/FormationPreviewPoolLookup.cpp: LINKS  LINKED 262 -> 262 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 262)
Code/Libraries/Source/DirectX/dxtracew.cpp: LINKS  LINKED 478 -> 478 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 478)
Code/Libraries/Source/DirectX/dxtracea.cpp: LINKS  LINKED 476 -> 476 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 476)
Code/GameEngine/Source/GameLogic/Pathfinder/PathfinderIsValidHordeMemberRegularMovement.cpp: LINKS  LINKED 337 -> 337 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 337)
Code/GameEngine/Source/GameClient/System/FXParticleSystem/fxpsemittercylindervolumemodule.cpp: LINKS  LINKED 212 -> 212 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 212)
Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfaceLocomotorDistanceToGoal.cpp: LINKS  LINKED 506 -> 506 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 506)
Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfaceNotifyPathHasInvalidPortals.cpp: LINKS  LINKED 671 -> 671 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 671)
Code/GameEngine/Source/GameLogic/Object/Update/AIGateUpdateTrigger.cpp: LINKS  LINKED 586 -> 586 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 586)
Code/GameEngine/Source/Common/Rva0028E8D4Rva0028E8D4.cpp: LINKS  LINKED 445 -> 445 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 445)
Code/GameEngine/Source/GameLogic/Object/Update/RousingSpeechUpdateTrigger.cpp: LINKS  LINKED 355 -> 355 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 355)
link_check: 17 of 17 link cleanly; LINKED 5,275 -> 5,275 bytes (3.1s)
```

## Execution and proof limits

The repositories use independent claims, source trees, ledgers and object caches,
so native work ran concurrently between projects. Within each repository, edits,
native cache writes, log writes and commits were sequential. BUILD_POOL=14 each,
up to28 build workers on28 logical CPUs. No local model was required. No measured
serial/parallel speedup is claimed. The already-corrected diagnostic controls are reused; project gates remain unchanged.

This batch repairs compiler include inventories. It does not establish RAM/leak,
crash, FPS or multicore improvements. Full engine linking/gameplay remain unproven.

Outgoing audit before this documentation-only amendment, exit 2:

```text
link batch audit: INCONCLUSIVE baseline: index at 984a4cdc4d, outgoing base 4c68335a247a7bb4b0e03ebb87b8bc8378eb0231; findings below are provisional since-index changes
link batch audit: INCONCLUSIVE: affected consumer lacks current receipt: Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp
```
