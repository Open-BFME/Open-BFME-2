# RebuildHoleBehavior header adoption, 2026-11-05 (codexb5)

Inspected source revision: `0602a52962c393291cbdf8f5cc742c2604a62a15`.
Class/file scope was acquired by `next_work.py --claim` as
`yasinschroeder-codexb5`. This is header debt cleanup, not new code coverage.

## Retained repair

`RebuildHoleBehaviorPoolKey.cpp` includes the existing canonical
`RebuildHoleBehaviorClass.h` instead of its private primary-only view.
`newWorkerRespawnProcess` clears the now-enumerated worker ID using the existing
`INVALID_OBJECT_ID`. No method, data, pin or alias identity changes.
The owning `header_adopt_lane.py accept --class RebuildHoleBehavior` command
retires only this source's queue row; the other three queue rows remain.

The four existing pool-key/respawn/EH rows cover 206 bytes including EH;
the executable-byte preview scope is 182 bytes. No census gain is claimed.

## Rejected destructor trial (LINK-379)

The initial supported four-source adoption refused ModuleFactoryInit.cpp
(duplicate Module), RebuildHoleBehavior.cpp (explicit +0x20 interface pointer
has no canonical data field), RebuildHoleBehaviorDtor.cpp (int/float +0x40
field conflict), and RebuildHoleBehaviorPoolKey.cpp (integer zero to ObjectID).
Only the latter source's adoption is retained.

Target/header facts: the canonical tail is float at +0x40, consistent with the
existing transfer body's float slot. The old destructor unit copies an int
view at Object+0x324 to that field. A trial changed the local field declaration
to float and used a bit-preserving integer-view store before supported adoption.
All five existing destructor/startRebuildProcess/deleting-destructor/EH rows
(235 bytes including EH, 227 executable bytes) still matched.
The trial's link preview instead reported these unresolved canonical names:

- `?GetSnapshotName@RebuildHoleBehavior@@MBEPBDXZ`
- `?loadPostProcess@RebuildHoleBehavior@@MAEXXZ`
- `?onDie@RebuildHoleBehavior@@UAEXPBVDamageInfo@@@Z`

Current ledger leads, not approval to rename: native name getter 0x0048331C is
`?name@RebuildHoleBehavior@@QBEPBDXZ` in ModuleNameGetters.cpp; native slot-1
wrapper 0x00497805 is `?loadPostProcess@Rva00497805@@MAEXXZ` in
BattlePlanUpdate.cpp; die slot 0x004835FB is
`?rva004835FB@Rva004835FB@@QAEXH@Z` in VslotSmallBodiesW.cpp.
Shared/folded provider identities and all consumers must be established before
changing names. The real die method also needs its secondary-interface ABI.
No external donor path or spelling is asserted as original BFME2 source.

The rejected destructor adoption was restored from the original file, then
both restored destructor and retained pool-key units were byte-verified.
All four existing link-wide aliases remain unchanged, including their hatch rows.
No game link, runtime check or new census was run.

## Trial receipts

Supported two-source adoption after the local prerequisite fixes:

```text
  PASS Code/GameEngine/Source/GameLogic/Object/Behavior/RebuildHoleBehaviorDtor.cpp
  PASS Code/GameEngine/Source/GameLogic/Object/Behavior/RebuildHoleBehaviorPoolKey.cpp
```

Combined acceptance of the trial:

```text
  FAIL Code/GameEngine/Source/GameLogic/Object/Behavior/RebuildHoleBehaviorDtor.cpp: link_check predicts a loss of census-linked bytes
  PASS Code/GameEngine/Source/GameLogic/Object/Behavior/RebuildHoleBehaviorPoolKey.cpp
  retired 1 row(s) from reverse/header_queue.tsv; commit it with the adoption
```

Trial link preview:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/GameLogic/Object/Behavior/RebuildHoleBehaviorDtor.cpp: does not link  LINKED 227 -> 0 bytes (census 2026-11-04 22:40 at 3a95b274a2; file's own bytes 227)
  unresolved  ?GetSnapshotName@RebuildHoleBehavior@@MBEPBDXZ
  unresolved  ?loadPostProcess@RebuildHoleBehavior@@MAEXXZ
  unresolved  ?onDie@RebuildHoleBehavior@@UAEXPBVDamageInfo@@@Z
Code/GameEngine/Source/GameLogic/Object/Behavior/RebuildHoleBehaviorPoolKey.cpp: LINKS  LINKED 182 -> 182 bytes (census 2026-11-04 22:40 at 3a95b274a2; file's own bytes 182)
link_check: 1 of 2 link cleanly; LINKED 409 -> 182 bytes (34.7s)
```

Restored-state byte verification:

```text
Source claims: OK (2 sources, scoped byte-verified)
Compile: 1 of 2 TU(s) (deps-cache: 1 current)
Funclet pins: 2 row(s) verified past a renumbered $L label
    Unwind@00b8bc83 (Code/GameEngine/Source/GameLogic/Object/Behavior/RebuildHoleBehaviorDtor.cpp): $L454 was renumbered; verified parent EH data places $L1149 at 0x0078BC83
    $L562 (Code/GameEngine/Source/GameLogic/Object/Behavior/RebuildHoleBehaviorPoolKey.cpp): $L562 was renumbered; verified parent EH data places $L4532 at 0x0078BC40
Functions: OK 9/9 matched across 2 source file(s)
String-ref verify: OK (1 literals + 0 empty-string refs verified, 0 baselined, 0 unverified/skipped)
Float-ref verify: OK (0 compiler literals verified)
Import-ref verify: OK (0 named imports verified)
```

Rejected destructor patch (evidence only; not applied):

```diff
diff --git a/Code/GameEngine/Source/GameLogic/Object/Behavior/RebuildHoleBehaviorDtor.cpp b/Code/GameEngine/Source/GameLogic/Object/Behavior/RebuildHoleBehaviorDtor.cpp
index c65f6f87c7..807aa845ba 100644
--- a/Code/GameEngine/Source/GameLogic/Object/Behavior/RebuildHoleBehaviorDtor.cpp
+++ b/Code/GameEngine/Source/GameLogic/Object/Behavior/RebuildHoleBehaviorDtor.cpp
@@ -53,41 +53,9 @@ enum UpdateSleepTime
 #include "../../../../Include/GameLogic/Module/UpdateModule.h"


-class DieModuleInterface
-{
-public:
-   virtual void onDie();
-};
+#include "../../../../Include/GameLogic/Module/RebuildHoleBehaviorClass.h"

-class RebuildHoleBehaviorInterface
-{
-public:
-   virtual void startRebuildProcess(const ThingTemplate *rebuild, ObjectID spawnerID) = 0;
-   virtual ObjectID getSpawnerID();
-   virtual ObjectID getReconstructedBuildingID();
-   virtual const ThingTemplate *getRebuildTemplate() const;
-};

-class RebuildHoleBehavior : public UpdateModule,
-   public DieModuleInterface,
-   public RebuildHoleBehaviorInterface
-{
-public:
-   virtual UpdateSleepTime update();
-   virtual ~RebuildHoleBehavior();
-   virtual void startRebuildProcess(const ThingTemplate *rebuild, ObjectID spawnerID);
-   void newWorkerRespawnProcess(Object *existingWorker);
-
-private:
-   ObjectID m_workerID;
-   ObjectID m_reconstructingID;
-   ObjectID m_spawnerObjectID;
-   unsigned int m_workerWaitCounter;
-   const ThingTemplate *m_workerTemplate;
-   const ThingTemplate *m_rebuildTemplate;
-   int m_40;
-   bool m_44;
-};

 RebuildHoleBehavior::~RebuildHoleBehavior()
 {
@@ -108,7 +76,7 @@ void RebuildHoleBehavior::startRebuildProcess(const ThingTemplate *rebuild, Obje
 {
    Object *spawner = TheGameLogic->findObjectByID(spawnerID);
    if (spawner)
-       m_40 = spawner->m_324;
+       *(int *)&m_40 = spawner->m_324;
    m_rebuildTemplate = rebuild;
    m_spawnerObjectID = spawnerID;
    Object *worker = TheGameLogic->findObjectByID(m_workerID);
```

## Final retained-state receipts

Independent owning acceptance after restoring the destructor:

```text
  PASS Code/GameEngine/Source/GameLogic/Object/Behavior/RebuildHoleBehaviorPoolKey.cpp
```

Combined restored-state link preview:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/GameLogic/Object/Behavior/RebuildHoleBehaviorDtor.cpp: LINKS  LINKED 227 -> 227 bytes (census 2026-11-04 22:40 at 3a95b274a2; file's own bytes 227)
Code/GameEngine/Source/GameLogic/Object/Behavior/RebuildHoleBehaviorPoolKey.cpp: LINKS  LINKED 182 -> 182 bytes (census 2026-11-04 22:40 at 3a95b274a2; file's own bytes 182)
link_check: 2 of 2 link cleanly; LINKED 409 -> 409 bytes (46.0s)
```

`find_declared_unmatched.py` passes for both final sources; `git diff --check` passes.
The inspected local names (`modData`, `hole`, `existingWorker`, and the cached
pool key) already express their roles and are retained.
