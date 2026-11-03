### LINK-024: `LivingWorldBuildingCtor.cpp` needs placeholder `Rva004E0D67` named `LivingWorldBuilding`
Status: Open. Updated: 2026-10-26; inspected revision: 896af21680.
Evidence / affected units: `Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldBuildingCtor.cpp`
(298 B) initially had three unresolved names on the earlier inputs (`link_check.py`, index 47e030bafc):
`??1LivingWorldBuilding@@UAE@XZ`, `?LoadPostProcess@LivingWorldBuilding@@UAEXXZ`, `??1Rva004E0790@@QAE@XZ`.
Target facts: retail ctor 0x004E119C stores vptrs 0x00C61618 (Snapshot) and 0x00C61610 (RegionTurnObserverView).
0x00C61618 slots: 0 = 0x004E0E5C (rowed `??_GRva004E0D67` in `OpaqueScalarDeletingDtorsB11.cpp`, which calls the
dtor 0x004E0D67, rowed `??1Rva004E0D67` in `Rva004E0D67Dtor.cpp`), 1 = 0x000B3FD0 (the shared empty `ret`),
2 = 0x004E0777 `GetSnapshotName`, 3 = 0x004E0E78 `DoXfer`. The ctor's +0x3C unwind funclet (0x0079198E) jumps to
0x002B2E8E, the ICF-folded holder dtor already rowed as `??1ArmySummaryEntryRef@@QAE@XZ` (fold-proof in
`Rva002B4076Dispatch.cpp`).
Completed: the constructor now stores the army holder as `ArmySummaryEntryRef`, whose existing 18-byte destructor at `0x002B2E8E` is defined by `Rva002B4076Dispatch.cpp`. Its setter keeps the existing `Rva004E0790` call view. All six constructor-unit rows remain exact, the complete EH graph is EXACT, and the current six-unit preview drops `??1Rva004E0790@@QAE@XZ` with no new finding. Raw before/after and gate outputs: `build/link-report.md` and `build/link-worker-20261026/`.
Remaining / next check: rename/reconcile the `Rva004E0D67` destructor and deleting-destructor owners to `LivingWorldBuilding` while preserving their full vtable bindings; admit the empty `LoadPostProcess` override at `0x000B3FD0` through the normal folded-row path. Both remaining names stay unresolved in the current preview. No row rename, new body or pin was attempted in this seat.
Clearance: holder destructor binding cleared in ordinary-preview scope; census confirmation pending. The complete constructor unit remains blocked on the two names above.
Census confirmation: not claimed.

Path update (2026-10-29): `tu_skeleton --merge` moved the constructor unit into its approved TU `Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldBuilding.cpp` with `DoXfer`, both on the constructor's class view; all 14 rows stay exact. The two unresolved names above are unchanged; no clearance is claimed.

Current destructor-side inspection (2026-10-26, revision `896af216804e1f1e34de28bd318285fbbbfcc536`; index `d1f046749a`): `Rva004E0D67Dtor.cpp` still has four unresolved virtual names. Its table at RVA 0x00861618 puts the name getter `LivingWorldBuilding::GetSnapshotName` (0x004E0777) where the private view spells `crc`, and `LivingWorldBuilding::DoXfer` (0x004E0E78) where it spells `xfer`. `Gen_uwm_004edfff::s0` also conflates the derived listener slot at 0x004E06B8 (`LivingWorldBuilding::BeginTurn`) and its base slot at 0x0050B238. These are signature/type conflicts, not requests for one same-signature alias. No source trial was made. Raw table-slot witnesses and row homes are in `build/link-worker-w1/native-witnesses.log`; the unchanged destructor unit passes the combined byte gate. The class/observer reconciliation above remains the prerequisite; no clearance or census change is claimed.

Current preview (2026-10-29, revision `ac5cb21684`, index `85f6b7f40c`):
`Rva004E0D67Dtor.cpp` remains at 0 linked bytes, with the same four unresolved
`crc`, `loadPostProcess`, `xfer` and `Gen_uwm_004edfff::s0` symbols. The
constructor view now uses the named Snapshot slots and `RegionTurnObserverView`,
but the destructor's placeholder class and listener view still need identity
reconciliation. A `rename.py class` dry run with canonical WorldBuilder evidence
was refused: the lead at 0x004E0D67 does not name the class. The shared vtables
and constructor establish the structural relationship, but that lead is not an
accepted canonical naming basis. No source changes or clearance are claimed;
resolve the identity through the supported evidence/reconciliation path, then
verify both vtables and affected consumers against a current index.

Current checkpoint (2026-10-30, revision `50472e739d`, index `12b9e7a7c0`):
ordinary preview still reports the same four unresolved private virtual names
and 0 linked bytes for `Rva004E0D67Dtor.cpp`. The current Snapshot header
already provides selectable named slots, and the constructor uses the existing
`RegionTurnObserverView`; neither resolves the placeholder class identity.
No source or rename trial was repeated. Class/observer reconciliation remains
the prerequisite; no clearance or census gain is claimed.

Update (2026-11-01, base `b8bcae39502`+pull, ordinary preview against census
2026-10-31 22:25 at `4a490aa2e4`): `LivingWorldBuilding.cpp` now defines the
empty `LivingWorldBuilding::LoadPostProcess` override and its folded row
`?LoadPostProcess@LivingWorldBuilding@@UAEXXZ` at 0x000B3FD0 (1 B, `add_match`
verified, fold-proof `region.cpp`). The preview drops that name; the unit still
reports one unresolved, `??1LivingWorldBuilding@@UAE@XZ` (0 linked bytes).
Remaining prerequisite unchanged: the destructor 0x004E0D67 (and `??_G`
0x004E0E5C in `OpaqueScalarDeletingDtorsB11.cpp`) sit in no approved TU
(`tu_map.csv` rows blank), so they cannot be moved into this unit, and
`rename.py class Rva004E0D67 -> LivingWorldBuilding` refuses both `canonical:wb`
(no `wb_name_leads.csv` row at 0x004E0D67) and any basis on collision
(`LivingWorldBuilding already appears`, `rename.py` collision check). This is
the same maintainer decision as LINK-063: admit a placeholder-into-existing-class
rename for a placeholder whose rows are that class's own table entries, or TU-approve
0x004E0D67/0x004E0E5C into `LivingWorldBuilding.cpp` and reconcile the view.
Clearance: `LoadPostProcess` name only (preview scope); census not claimed.

**2026-11-01 owner-fold checkpoint (GPT-6, base f878d8a980):** a fresh
0156fc269e current-object preview retains only the missing real-named
LivingWorldBuilding destructor in the approved constructor/transfer TU
(1,124 own bytes; zero linked). The newly supported class --fold path is
worth testing for Rva004E0D67 once the class is available, preserving the
Snapshot and RegionTurnObserverView slots described above. The origin-backed
class:LivingWorldBuilding reservation was refused; all three partial scope
claims were released immediately. No source edit, fold trial, clearance or
census gain. [Current checkpoint and claim result](../../reverse/attempt_support/render-task-record-name-20261101/readme.md).

**Repaired (2026-11-02, seat halilkkaya-lk15, base `1765dc430d`):** `rename.py class --fold Rva004E0D67
--into LivingWorldBuilding` (evidence: dtor 0x004E0D67's first +0 store is 0x00C61618, which
LivingWorldBuilding.cpp's DIR32 binding already names `??_7LivingWorldBuilding@@6BSnapshot@@@`;
`??_G` 0x004E0E5C is its slot 0) renamed the three rows (`??1`, `??_G`, `__ehhandler$`) with
tombstones and rewrote OpaqueScalarDeletingDtorsB11.cpp and Rva004E0D67Dtor.cpp. That alone moved the
blocker: Rva004E0D67Dtor.cpp (first in link order at 0x004E0D67) then emitted a differing
`??_7LivingWorldBuilding@@6BSnapshot@@@` (Zero Hour crc/xfer/loadPostProcess slots). Its view now
matches LivingWorldBuilding.cpp's: Snapshot with `BFME_SNAPSHOT_CAPITALIZED_SLOTS`, `_NAME_SLOT` and
`_NONCONST_NAME_SLOT` (LoadPostProcess, GetSnapshotName, DoXfer) and the +4 listener as
`RegionTurnObserverView` with the `BeginTurn` override, in place of `Gen_uwm_004edfff::s0`; its
non-polymorphic +8 buffer base, members and body are unchanged. `./build.sh` 40/40 rows for the fold
and 7/7 after the view change (funclet labels renumbered, parent EH data verified); scoped DIR32 OK
(11 symbols, three units); `rename.py check` clean; `link_check` LivingWorldBuilding.cpp 0 -> 1,124 B,
Rva004E0D67Dtor.cpp 0 -> 245 B, OpaqueScalarDeletingDtorsB11 964 B unchanged; other units touching the
affected names (VslotSmallBodiesAE 570, SubsystemNameGetters 263, Rva004FC4D1Dtor 194) unchanged;
`??1Gen_uwm_004edfff@@QAE@XZ`, whose only COMDAT the old dtor view emitted, keeps its symbols.csv pin
(0x004EDFFF) and its one consumer, the already unlinked `uw_gen_013.cpp`, keeps 184 unresolved names.
Remaining: Rva004E0D67Dtor.cpp's file name still spells the placeholder (consolidation into
`LivingWorldBuilding.cpp` once 0x004E0D67/0x004E0E5C are TU-approved). Census confirmation: pending.
