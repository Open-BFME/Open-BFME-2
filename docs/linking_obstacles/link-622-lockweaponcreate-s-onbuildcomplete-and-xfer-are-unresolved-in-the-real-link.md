### LINK-622: LockWeaponCreate's onBuildComplete and xfer are unresolved in the real link

Status: Repaired in source (a2fc5f3de7); awaiting the next real link to confirm. Updated: 2026-11-06; ancalgonn-swarm-link; real link
`12de5b58b2` (run 42296273754, 261 unresolved, 0 duplicates). Related: LINK-584 (the rest of the
unresolved names).

**Symptom.** `LockWeaponCreate.cpp` references `?onBuildComplete@LockWeaponCreate@@UAEXXZ` and
`?xfer@LockWeaponCreate@@MAEXPAVXfer@@@Z` through its vtables, and nothing defines them. The file already
binds its other placeholder virtuals (`onCreate`, `crc`, `loadPostProcess`) with `/alternatename`
hatches.

**Target facts.**
- Retail `??_7LockWeaponCreate@@6B@` (0x008592EC, the CreateModuleInterface table) slot 1 is 0x004B8CC9,
  and that is its only reference in the image. The body is Zero Hour's `LockWeaponCreate::onBuildComplete`:
  clear `m_needToRunOnBuildComplete` (the inline `CreateModule::onBuildComplete`), then
  `getObject()->setWeaponLock(getLockWeaponCreateModuleData()->m_slotToLock, LOCKED_PERMANENTLY)`. It is
  matched today under the placeholder `?bfmeGo940G@BfmeThing940G@@QAEXXZ` in `BfmeConv940.cpp`; tu_map
  proposes it for `BfmeThing940G.cpp` (N, from that name), not for `LockWeaponCreate.cpp`.
- Retail `??_7LockWeaponCreate@@6BObjectModule@@@` (0x008592FC) slot 3 is 0x004851E3, matched as
  `?xfer@Rva004851E3@@MAEXPAVXfer@@@Z` (`Rva004851E3Xfer.cpp`, no TU). Eight image words point at it, so
  it is an identical-code fold of several modules' `xfer` (xferVersion, then the base xfer). A second
  real name there needs a fold-proven pin, not a definition.

**Why it is not done.**
- `rename.py function --rva 0x004B8CC9 --new onBuildComplete --to-class LockWeaponCreate` refuses: the
  unit that installs the vtable, `Rva004B8CDEDerived.cpp` (the destructor 0x004B8C3E and `??_G`
  0x004B8CAD), compiles a private LockWeaponCreate view (`MiBase1`, `Rva004B8C3E_B2` bases) whose vtables
  match no retail slot.
- `tu_skeleton.py --merge .../Create/LockWeaponCreate.cpp --dry-run`: 7 approved rows across mixed donors
  (`ConstIntGetters4.cpp` 253 rows, `Rva004B8CDEDerived.cpp` 12, `ModuleDataBuildFieldParse.cpp` 79); the
  pool-key donor `LockWeaponCreatePoolKey.cpp` is rejected (`SubsystemInterface` class redefinition); no
  verified merge.

**Next.** Reconcile `Rva004B8CDEDerived.cpp`'s private view onto the Zero Hour `LockWeaponCreate.h`, in
its own verified commit. Then the vftable proves slot 1, the rename lands, and the map can approve
0x004B8CC9 into `LockWeaponCreate.cpp`. `xfer` follows the ICF-fold rules once its sibling classes are
known.

**2026-11-08 (Burachi-3D, claude-opus-5-5).** Steps 1-2 of the lk41 order
(`reverse/attempt_support/lockweaponcreate-createmodule-fold-20261107-lk41.md`) are done:
- `~BehaviorModule` has its row. `??1BehaviorModule@@MAE@XZ` 0x004607E1 and `??_GBehaviorModule@@MAEPAXI@Z`
  0x0025335A are ICF folds onto `??1/??_GRva004607E1` (FXListDie.cpp, ae2bc4d6eb). This took the fold-row
  route, not the class fold (whose 0x00BEEA7C third names are still there).
- `Rva004B8CDE` is folded into `CreateModule` (acc0d98cc9, landed d88c3448da): `??1CreateModule@@MAE@XZ`
  0x004B8CDE and `??_GCreateModule@@MAEPAXI@Z` 0x004B8D32. The five lk41 units were rebuilt and prepared
  on CreateModuleClass.h; 112/112 rows exact; 8 alternatenames retired. data_ledger.csv was regenerated
  (aa3afb41ca).
- Rva004B8CDEDerived.cpp's LockWeaponCreate is now `class LockWeaponCreate : public CreateModule`
  (destructor 0x004B8C3E, `??_G` 0x004B8CAD). Remaining: step 3, LockWeaponCreate.cpp on
  CreateModuleClass.h with one LockWeaponCreate view shared with Rva004B8CDEDerived.cpp
  (tu_map approves the destructor 0x004B8C3E into LockWeaponCreate.cpp, `??_G` is only proposed),
  then onBuildComplete/xfer/GetSnapshotName as the lk41 note lists.

**2026-11-08, step 3 done (a2fc5f3de7).** LockWeaponCreate.cpp is on CreateModuleClass.h. One
shared view, `Code/GameEngine/Include/GameLogic/Module/LockWeaponCreate.h`, is included by
LockWeaponCreate.cpp and Rva004B8CDEDerived.cpp. 0x004B8CC9 is renamed to
`?onBuildComplete@LockWeaponCreate@@UAEXXZ` (rename.py --to-class; the slot proof needed one other
resolved slot of 0xC592EC, so onCreate is now an ICF fold onto 0x000B3FD0). GetSnapshotName
(0x004B8C38) and xfer (0x004851E3) are ICF folds. 20/20 rows; link_check LINKS all three units
(LockWeaponCreate.cpp 0 -> 89 B); the pre-push audit is expected INCONCLUSIVE for missing receipts.
Left: slot 4 stays __purecall because getModuleNameKey's row is the static
`?rva004B8C57@LockWeaponCreate`. Slot 1 inherits CreateModule's loadPostProcess (retail 0x00497805
jumps to the same body). Verify with the next `reverse/exit_link_blockers.tsv`: LockWeaponCreate.cpp
should be gone.
