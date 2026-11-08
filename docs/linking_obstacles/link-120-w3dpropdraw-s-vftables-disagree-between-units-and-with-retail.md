### LINK-120: W3DPropDraw's vftables disagree between units and with retail

**Status: Cleared for `W3DPropDraw.cpp` by current-object preview (census confirmation pending). Updated: 2026-11-01; inspected revision: `f489df5a8b`.**

- **2026-11-01 repair (halilkkaya-rq-o1, base `f489df5a8b`, index `dae306bc9d`):** the
  ModuleData destructor conflict was already gone; the current object lost only
  `??_7DrawModule@@6B@` and `??_GDrawModule@@MAEPAXI@Z`. Cause: Zero Hour's
  `Common/DrawModule.h` ends with `inline DrawModule::DrawModule(...)` and
  `inline DrawModule::~DrawModule()`. The W3DPropDraw ctor (0x000CEEC0) calls the
  DrawModule ctor out of line, so the inline body was emitted as a COMDAT and,
  with it, this unit's 32-slot ZH `??_7DrawModule@@6B@` and `??_GDrawModule`. The
  kept copies (first in link order, `W3DBoatWakeModelDrawDtor.cpp`, eight units
  agree) are one-slot. Retail runs both functions out of line and other units
  already own them with retail verdicts: `??0DrawModule` is rowed at 0x000B19A1
  (`GameClient/Drawable/Update/DrawModule.cpp`), `??1DrawModule@@MAE@XZ` at
  0x000CEB6F (`W3DBoatWakeModelDrawDtor.cpp`). Fix: `W3DPropDraw.cpp` declares Zero
  Hour's DrawModule class itself (same virtual list, so its own ZH-shaped
  `??_7W3DPropDraw@@6B@` is unchanged) and leaves out the two inline
  definitions. The ctor and dtor calls now bind to those owners and the unit
  emits no DrawModule table. Verified: `./build.sh` 7/7 exact; `link_check`
  `W3DPropDraw.cpp` 0 -> 157 B LINKS; all 84 DrawModule-family and W3DPropDraw*
  units still link (29,376 -> 29,533 B); `--new-variants` clean; scoped DIR32 OK.
  Remaining for the family: retail's own DrawModule table (VA 0x00BC9690, at
  least 48 slots: `??_G`, `GetSnapshotName`, `xfer`, `__purecall` and folded
  stubs) is still not what any unit emits. The kept one-slot copy is not
  retail's. Proving a family-wide table needs `class:DrawModule`, which other
  workers hold.

- **2026-11-08 header-lane data point (dave-cons4-header, index `eba83a23be`
  2026-11-08 14:08):** the family problem bites header adoption too, from the
  derived side. `header_adopt_lane.py adopt --class DrawModule --header
  Code/GameEngine/Include/GameLogic/Module/DrawModule.h` **passes** on
  `W3DDevice/GameClient/Drawable/Draw/W3DStreakDraw.cpp` and `./build.sh` is
  25/25 exact, but `accept` refuses on the link guard and `link_check` shows why:

      pristine   LINKS       LINKED 1,497 -> 1,497 bytes
      adopted    does not link  LINKED 1,497 -> 0 bytes
        comdat  ??_7W3DStreakDraw@@6B@  (first: differs from the first copy in link order)

  So the lost COMDAT is the **derived** class's own vftable, not
  `??_7DrawModule@@6B@`. Adopting the canonical header gives `W3DStreakDraw` a
  base with a different virtual list from the one its table was built against,
  and its own table changes shape with it. That is the mirror image of the
  2026-11-01 repair above, which fixed `W3DPropDraw.cpp` by declaring the ZH
  `DrawModule` locally *precisely so* its derived table stayed unchanged.
  The adoption was reverted; nothing was retained.

  **Consequence for the header lane:** `DrawModule.h` should not be adopted in a
  `W3D*Draw` unit until this entry's remaining prerequisite -- a family-wide
  `DrawModule` table proven against retail (VA 0x00BC9690, at least 48 slots) --
  is settled. A byte-exact adoption is not evidence here; the byte gate cannot
  see a COMDAT selection change, which is what the link guard is for. The
  `DrawModule` queue rows are blocked on this entry, not on a layout
  disagreement. Measured yield for the class was 1 pass in 29 units
  (`reverse/attempt_support/header-bulk-probe-yield-20261108.md`), and that one
  pass is this unit.

- **Earlier recheck (2026-10-28, revision `e1b88db116ad`):** all five rows in `W3DPropDraw.cpp`
  byte-verify, but its current object still previews blocked for all 124 authored
  bytes against index `14dc3d2467`: the same ModuleData destructor, DrawModule
  vftable and DrawModule deleting-destructor conflicts below. No source trial
  or clearance; the shared-interface prerequisites remain.
  [Recheck evidence](../../reverse/attempt_support/propdraw-link-recheck-20261028-codex.md).
  The original 2026-10-26 inspection at `60d0fc0a50` follows.

- **Evidence / affected units:**
  - `W3DPropDrawModuleDataCtor.cpp` (33 B) has one blocker: `??_7W3DPropDrawModuleData@@6B@`
    differs from the first copy in link order.
  - That first copy is `W3DPropDraw.cpp`'s (124 B). That unit also loses
    `??_7DrawModule@@6B@`, `??_GDrawModule@@MAEPAXI@Z` and `??1ModuleData@@UAE@XZ`
    (unproven, differs from the kept retail copy).
- **Target facts:** retail's table 0x00BCD420 (VA) is the shared 31-slot BFME 2 ModuleData
  table (`Code/GameEngine/Include/Common/BfmeModuleData.h`) with three own slots:
  - slot 0 is `??_G` 0x000CF058;
  - slot 14 is 0x000CED14, `return m_modelName` by value, folded with
    `W3DTreeDrawModuleData`'s rowed `rva000CED14`;
  - slot 17 is 0x0047A6A9, `mov eax,ecx; ret`.
  - Slots 1-3, 4-13, 15-16 and 18-30 are the base bodies the header lists.
- **Current copies:**
  - The ctor unit's Snapshot view emits 4 slots: `??_E` and three `__purecall`.
  - `W3DPropDraw.cpp` emits 9 ZH-shaped slots from
    `reference/shims/update_modules_bfme2/Common/Module.h`.
  - Neither copy is retail's. Copying the ZH view into the ctor unit (the LINK-028 recipe)
    would link the 33 B but install a vftable whose slots 5-8 run the wrong bodies.
- **Family context:** the other W3D*Draw units (BoatWakeModelDrawDtor, LaserDrawDestructor,
  LightDrawDestructor, RopeDraw ctor/dtor, ScriptedModelDrawDestructor,
  ProjectileStreamDrawDtor, `Code/GameEngine/Source/GameClient/Drawable/Update/DrawModule.cpp`)
  agree on a one-slot `??_7DrawModule` (only `??_E`). `W3DPropDraw.cpp` emits the full
  32-slot ZH DrawModule table, so it loses there too.
- **Remaining / next check:** give `W3DPropDraw.cpp` BFME 2 views instead of the ZH Module.h
  family. Two pieces are needed:
  - a BfmeModuleData.h-based `W3DPropDrawModuleData` declaring the slot-14 and slot-17
    overrides;
  - a DrawModule view that agrees with the family's kept copy, or a family-wide DrawModule
    table proven against retail.
  Then give the ctor unit the same W3DPropDrawModuleData declaration. The ZH Module.h
  include chain in `W3DPropDraw.cpp` already defines `ModuleData`, so this means
  replacing that chain, not adding a header. No source was changed.
- **2026-10-28 verification:** all five seed rows and all eight rows in the three
  clean donors still byte-match. The ordinary preview against census index
  `14dc3d2467` (2026-10-28 02:44) retains the three seed blockers above. A fresh
  Draw-directory naming report and the current in-memory TU map produce a
  15-row plan; ordinary `tu_skeleton.py --merge ... --dry-run` accepts no donor.
  LinkGuard refuses the otherwise compiling PoolKey donor because it currently
  links and the composition would not. The module-data ctor also still lacks
  `m_distanceFog` in the seed view; React still collides on `Coord3D`. Those
  declaration prerequisites do not clear the provider conflicts. No merge or
  source edit was retained. Handoff:
  `reverse/attempt_support/propdraw-link-contracts-20261028.md`.
- **Clearance:** none.
- **Census confirmation:** not claimed.
