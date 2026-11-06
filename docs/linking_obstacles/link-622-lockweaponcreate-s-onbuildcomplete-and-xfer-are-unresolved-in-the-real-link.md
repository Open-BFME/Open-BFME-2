### LINK-622: LockWeaponCreate's onBuildComplete and xfer are unresolved in the real link

Status: Open (blocked on class reconciliation). Updated: 2026-11-06; ancalgonn-swarm-link; real link
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
