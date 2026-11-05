# LockWeaponCreate.cpp real link: what a canonical CreateModule view needs (2026-11-05)

Pass test: `tools/link_check.py Code/GameEngine/Source/GameLogic/Object/Create/LockWeaponCreate.cpp`
still reports unresolved `?onBuildComplete@LockWeaponCreate@@UAEXXZ` and
`?xfer@LockWeaponCreate@@MAEXPAVXfer@@@Z` at `014495d707`. Nothing changed in Code/.

## Target facts (retail bytes, RVAs; tables are VAs)

- Ctor 0x004B8C0E calls 0x004B8CF7 (CreateModule ctor), then stores 0x00C592FC at +0,
  0x00BEF9C0 at +0x0C and 0x00C592EC at +0x10.
- Dtor 0x004B8C3E stores the same three tables, then `jmp 0x004B8CDE`. Deleting dtor 0x004B8CAD
  calls 0x004B8C3E, then 0x0042FD60.
- 0x00C592FC (12 slots): 0x004B8CAD, 0x00497805 (`jmp 0x0058B03E`), 0x004B8C38
  (`mov eax, 0x00BF4AA4 "LockWeaponCreate"; ret`), 0x004851E3 (xfer: Version1 plus
  0x004B8D4E), 0x004B8C57 (name key), then 0x000B3FD0 x4, 0x0050B238, 0x000D43D0 x2.
- 0x00C592EC: 0x000B3FD0 (onCreate `ret`), 0x004B8CC9 (onBuildComplete), 0x000B3FD0 (slot02),
  0x00098CBC (shouldDoOnBuildComplete).
- 0x004B8CC9 with `this` at the +0x10 interface: it reads m_moduleData (+4) and clears +0x14.
  Then it calls 0x00290B24 `Object::setWeaponLock(slot, 2)` on m_object (+8).
- **0x004B8CDE is CreateModule's destructor.** 0x004B8D32 is slot 0 of CreateModule's own
  primary table 0x00C59368, which the CreateModule ctor 0x004B8CF7 installs, and it calls
  0x004B8CDE. 0x004B8CDE keeps CreateModule's interface table 0x00C59358 at +0x10. It then
  stores BehaviorModule's 0x00BEEA7C/0x00BEE9C0, because the empty ~BehaviorModule is inlined
  and the dead derived stores are dropped. It ends with `jmp 0x0049B47C`.

## Why the canonical view does not link yet

With `CreateModuleClass.h`, a unit that defines the ctor emits the class's tables. Its
dtor and deleting dtor then reference these names, and no object defines any of them:

| name | retail | current row |
|---|---|---|
| `??1CreateModule@@UAE@XZ` | 0x004B8CDE | `??1Rva004B8CDE@@UAE@XZ` (CreateModule.cpp, ZH view, opaque MI model) |
| `?GetSnapshotName@LockWeaponCreate@@MBEPBDXZ` | 0x004B8C38 | `?Rva004B8C38Get@@YAHXZ` (ConstIntGetters4.cpp; approved C into LockWeaponCreate.cpp) |
| `?getModuleNameKey@LockWeaponCreate@@UBE?AW4NameKeyType@@XZ` | 0x004B8C57 | `?rva004B8C57@LockWeaponCreate@@SA...` (LockWeaponCreatePoolKey.cpp; approved S) |
| `?loadPostProcess@LockWeaponCreate@@MAEXXZ` | 0x00497805 fold | `Rva00497805` (60 tables) |
| `?onCreate@LockWeaponCreate@@UAEXXZ` | 0x000B3FD0 fold | Coord2D/Region2D dtors |
| `?xfer@LockWeaponCreate@@MAEXPAVXfer@@@Z` | 0x004851E3 fold | `Rva004851E3` (8 tables) |
| `?onBuildComplete@LockWeaponCreate@@UAEXXZ` | 0x004B8CC9 | `BfmeThing940G::bfmeGo940G` |

`rename.py class --fold Rva004B8CDE --into CreateModule --dry-run` refuses: "0x004B8CF7 installs
0x00C59368 as its own vftable, not 0x00BEEA7C". The tool takes the dtor's +0 store as the class's
own table. Under /O1 that store comes from the inlined base dtor, so the refusal is recorded as
a false reject in re_attempts.log.

## Order of work

1. Tooling: let `--fold` accept a destructor whose deleting destructor sits in slot 0 of the
   target class's own ctor-installed table (here 0x004B8D32 in 0x00C59368). Alternatively,
   accept the retained interface store 0x00C59358 that both the ctor and the dtor make.
2. Fold Rva004B8CDE into CreateModule. This touches CreateModule.cpp, Rva004B8CDEDerived.cpp,
   W3DAptComponentView3D.cpp and both TailJumpWrappers5B files. Rewrite CreateModule.cpp on
   `CreateModuleClass.h` in the same move. It still holds the ZH view with present-unmatched
   dtor, crc and loadPostProcess.
3. In LockWeaponCreate.cpp, move the approved rows 0x004B8C38, 0x004B8C3E and 0x004B8C57 in
   under their real names, through the TU merge. Then rewrite the unit on
   `CreateModuleClass.h` + `ModuleData.h`.
4. Then `function --to-class LockWeaponCreate` for 0x004B8CC9 can see a matching 0x00C592EC.
   The three folds need fold-proof pins from that unit.
