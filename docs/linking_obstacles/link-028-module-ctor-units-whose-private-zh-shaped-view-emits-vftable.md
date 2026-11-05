### LINK-028: module ctor units whose private ZH-shaped view emits vftable COMDATs a ZH port also emits

**Status: Open (one unit repaired). Updated: 2026-10-26; inspected revision: `9f93879fe9`.**

- **Evidence / affected units:** `StealthUpdateCtor.cpp` (208 B) declared a ZH-shaped
  `ObjectModule`/`BehaviorModule`/`UpdateModule` chain, so its `??_7StealthUpdate@@6B@`,
  `6BObjectModule@@@` and `6BBehaviorModuleInterface@@@` copies (one slot each) lost to
  `StealthUpdate.cpp`'s full ZH copies (no retail address, first in link order). Its dtor
  `??1StealthUpdate` was unresolved because the retail dtor 0x00373CB1 was rowed as the
  placeholder `Rva00373CB1` in `Code/GameEngine/Source/Common/Rva0024A797Derived.cpp`, the
  flattened `UpdateModule, MiBase1, <X>_B2` family of opaque module destructors.
- **Completed (`895c0f21ef`):** renamed `Rva00373CB1` to `StealthUpdate` (ctor and dtor store
  the same vftables 0x00817F20/0x007EFF90/0x00817F14; slot 0 is the deleting dtor 0x00373F3D),
  and gave the ctor unit the Derived unit's flattened hierarchy with the two interface bases
  `__declspec(novtable)` (retail stores only the three StealthUpdate vftables). `./build.sh`
  2/2 and 60/60; current-object `link_check` 0 -> 208 B, with Derived, FriendNew, Xfer and
  Logic still linking. Census confirmation pending.
- **Remaining / next check:** other classes in `Rva0024A797Derived.cpp` (placeholder dtors
  whose `f2` alternatename names the module's `update`, e.g. LifetimeUpdate, FloatUpdate,
  HijackerUpdate) may have ctor units with the same split; a scan of the 08:28 index found no
  such unresolved `??1<Name>` blocker for those names, so check each ctor unit's blockers
  before working it. The vftable copies stay one-slot views of retail's full tables.
- **Clearance:** scope `StealthUpdateCtor.cpp` only, current-object preview at `895c0f21ef`.
- **Census confirmation:** awaiting.
- **2026-10-29 recheck:** `link_check.py` against the fetched index `85f6b7f40c`
  reports `Rva0024A797Derived.cpp` blocked by duplicate
  `??1DemoTrapUpdate@@UAE@XZ`, with 0 of its 1,590 own bytes linking. The
  rowed destructor is 0x00495916 in that unit. `DemoTrapUpdate.cpp` has an
  implicit destructor. The index identifies its object as a competing COMDAT
  provider, marked `wrong` against retail; the Derived object has the strong
  definition. The `DemoTrapUpdate.cpp` claim is held by another worker.
  Reconcile the providers when that claim is available, then recheck the
  affected units and census before claiming a repair.
  **2026-10-29 provider resolution, seat dd-14 (index `85f6b7f40c`):** the fetched index
  names both providers. Object 6549 (`Rva0024A797Derived.cpp`, the rowed owner at
  0x00495916, digest `0f190583f67a`, verdict `unknown`) defines
  `??1DemoTrapUpdate@@UAE@XZ` strongly; object 14273 (`DemoTrapUpdate.cpp`, digest
  `a2ae069b4628`, verdict `wrong`) emits the implicit-destructor COMDAT, so link.exe
  reports the pair and the Derived unit links 0 of its 1,590 own bytes. The competing
  unit still declares no destructor and is held by another seat
  (`yasinschroeder-claudeb2`, checked 2026-10-29), so no trial was made.
  **Repair, for that unit's claim holder:** declare the rowed owner instead of
  emitting an implicit body, `virtual ~DemoTrapUpdate();` in `class DemoTrapUpdate`
  (the LINK-110 `SubObjectsUpgrade.cpp` and LINK-145 RebuildHoleExposeDie pattern);
  it stops the COMDAT without changing any matched body. Then `./build.sh`
  `DemoTrapUpdate.cpp`, `link_check.py` on `DemoTrapUpdate.cpp` and
  `Rva0024A797Derived.cpp` (expect LINKS, 0 -> 1,590 B for the Derived unit), and
  confirm on the next census. No repair, clearance or census gain is claimed here.

- **2026-11-03 HijackerUpdate recheck:** all five scoped units link in current-object prediction (672/672 B); consolidation instead requires reconciling the seed header environment and ctor/update base clauses. Banked the unreferenced unverified seed xfer; batch audit is inconclusive (older baseline and stale affected-consumer receipt), requiring the next census; [evidence and next checks](../../reverse/attempt_support/hijackerupdate-xfer-cleanup-20261103.md). Census confirmation remains pending.

- **2026-11-05 HijackerUpdate prerequisite repair:** canonical TU-local declarations preserve all six seed byte matches and the five-unit 672/672-byte link prediction; merge dry-run now accepts Xfer and PoolKey, while opaque ctor stores and Update interface reconciliation remain; [evidence and next check](../../reverse/attempt_support/hijackerupdate-header-reconcile-20261105.md). Census confirmation remains pending.
